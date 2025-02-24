from argparse import ArgumentParser
import re
import os
import parse_enums
import parse_funcs
from config import Config

IMPORT_RE = re.compile(r'# \d+ "(?P<file>[^"]+)"( .*)?')
ENUM_RE = re.compile(r"enum (?P<name>\w+)( *: \w+)?")
FUNC_RE = re.compile(
    r'[\w\s&*_]* (?P<name>[\w\d]+)\((?P<args>[\w\d*& =\-,.()]*)\);'
)
STRUCT_RE = re.compile(r"struct (?P<name>[a-zA-Z_0-9]+) *(?P<bracket>\{)?")


def logWarn(msg: str):
    print(f"\033[33m{msg}\033[0m")


def main():
    parser = ArgumentParser()
    parser.add_argument("config")
    parser.add_argument("input_header")
    parser.add_argument("--header-out")
    parser.add_argument("--enum-out")
    parser.add_argument("--func-out")
    parser.add_argument("--preproc-out")

    args = parser.parse_args()

    configFile = args.config
    inputHeaderFile = args.input_header
    outputHeaderFile = os.path.abspath(args.header_out)
    enumFile = args.enum_out
    funcFile = args.func_out

    if outputHeaderFile is None:
        if enumFile is not None:
            raise RuntimeError(
                "Please specify --header-out if using the code outputs"
            )

    config = Config(configFile)

    with open(inputHeaderFile, mode="r") as f:
        rawLines = [line.strip() for line in f]

    baseHeaderName: str = os.path.basename(inputHeaderFile)
    prefix = "preprocessed_"
    if baseHeaderName.startswith(prefix):
        baseHeaderName = baseHeaderName[len(prefix):]

    # Preprocess file
    # strip comments and empty lines
    idx = -1
    lines: list[str] = []
    while idx + 1 < len(rawLines):
        idx += 1
        line = rawLines[idx]
        if len(line) == 0:
            continue

        # Skip over imported files
        m = IMPORT_RE.match(line)
        if m is not None:
            name = m.group("file")
            # TODO make this based off the input file
            if name.find(baseHeaderName) == -1:
                while True:
                    idx += 1
                    line = rawLines[idx]
                    m = IMPORT_RE.match(line)
                    if m is None:
                        continue
                    name = m.group("file")
                    if name.find(baseHeaderName) >= 0:
                        break
            # append whatever is next to the end of the previous line if it doesn't end with
            # a semicolon. Jank to get around function defs getting split over multiple lines
            if len(lines) > 0 and not lines[-1].endswith(";"):
                idx += 1
                lines[-1] += rawLines[idx]
            continue

        if line.startswith(("//", "#")):
            continue
        if line.startswith("/*"):
            while line.find("*/") == -1:
                idx += 1
                line = rawLines[idx]
            continue
        commentStart = line.find("//")
        # strip out comments
        if commentStart >= 0:
            line = line[:commentStart].strip()
        lines.append(line)

    if args.preproc_out is not None:
        with open(args.preproc_out, mode='w') as f:
            for line in lines:
                f.write(line)
                f.write("\n")

    if outputHeaderFile is None:
        return

    enums: list[parse_enums.ParsedEnum] = []
    funcs: list[parse_funcs.ParsedFunc] = []

    idx = -1
    while idx + 1 < len(lines):
        idx += 1
        line = lines[idx]
        m = ENUM_RE.fullmatch(line)
        if m is not None:
            idx += 2
            name = m.group("name")
            if name in config.blockedEnums:
                while not line.endswith(";"):
                    idx += 1
                    line = lines[idx]
                continue
            try:
                mappedName = config.enumMap[name]
            except KeyError:
                logWarn(f"Missing enum name mapping: {name}")
                mappedName = name
            idx, enum = parse_enums.parse(name, mappedName, lines, idx)
            enums.append(enum)
            continue
        m = STRUCT_RE.fullmatch(line)
        if m is not None:
            # skip over structs for now
            if m.group("bracket") is None:
                while not line.startswith("{"):
                    idx += 1
                    line = lines[idx]
            openBrackets = line.count("{") - line.count("}")
            while openBrackets > 0:
                idx += 1
                line = lines[idx]
                openBrackets += line.count("{") - line.count("}")
            continue
        m = FUNC_RE.match(line)
        if m is not None:
            if line.find("operator") != -1:
                continue
            if funcFile is not None:
                name = m.group("name")
                if name not in config.blockedFuncs:
                    funcArgs = m.group("args")
                    try:
                        func = parse_funcs.parse(name, funcArgs)
                    except Exception as err:
                        raise Exception(
                            "Error parsing function '" + line + "'"
                        )
                    funcs.append(func)
            continue

    outHeaderF = open(outputHeaderFile, mode='w')

    outHeaderF.write(
        "// WARNING AUTOGENERATED DO NOT EDIT\n"
        "#pragma once\n"
        "#include <pybind11/pybind11.h>\n"
        "namespace py = pybind11;\n"
        "using namespace py::literals;\n"
    )

    for inc in config.includes:
        outHeaderF.write(f"#include {inc}\n")

    if enumFile is not None:
        parse_enums.writeEnumFile(
            config, outHeaderF, outputHeaderFile, enumFile, enums
        )

    if funcFile is not None:
        parse_funcs.writeFuncFile(
            config, outHeaderF, outputHeaderFile, funcFile, funcs
        )

    outHeaderF.close()


if __name__ == '__main__':
    main()

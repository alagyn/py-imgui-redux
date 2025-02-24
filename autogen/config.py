class Config:

    def __init__(self, filename: str) -> None:
        self.enumMap: dict[str, str] = {}
        self.prefix = ""
        self.namespace = ""
        self.includes: list[str] = []
        self.blockedFuncs: set[str] = set()
        self.blockedEnums: set[str] = set()

        with open(filename, mode='r') as f:
            for line in f:
                args = line.strip().split()
                if line.startswith("#"):
                    continue
                if len(args) == 0:
                    continue

                keyword = args[0]
                if keyword == "enum":
                    if args[2] == ">":
                        self.enumMap[args[1]] = args[3]
                    elif args[2] == "block":
                        self.blockedEnums.add(args[1])
                    else:
                        raise RuntimeError(line)
                elif keyword == "prefix":
                    if len(args) > 2:
                        raise RuntimeError(line)
                    if self.prefix !="":
                        raise RuntimeError("Prefix already defined:" + line)
                    self.prefix = args[1]
                elif keyword == "include":
                    self.includes.append(args[1])
                elif keyword == "func":
                    if args[1] == "block":
                        self.blockedFuncs.add(args[2])
                    else:
                        raise RuntimeError(line)
                elif keyword == "namespace":
                    if len(args) > 2:
                        raise RuntimeError(line)
                    if self.namespace !="":
                        raise RuntimeError("Namespace already defined:" + line)
                    self.namespace = args[1]
                else:
                    raise RuntimeError("Invalid keyword " + line)

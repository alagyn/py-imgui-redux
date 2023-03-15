import sys

sys.path.append("../build/test")
sys.path.append("../build/test/Release")

import bdd  # type: ignore

YEL = "\x1B[1;4;33m"
OFF = "\x1B[0m"

x = bdd.Wrap(5)

t = type(x)
print(t)
print(t.__mro__)

print("Initial:", x)

print(f"\n{YEL}{'NORMAL':^40s}{OFF}\n")
try:
    bdd.normal(x)
except TypeError as e:
    print(e)
print("After normal:", x)

print(f"\n{YEL}{'POINTER':^40s}{OFF}\n")

try:
    bdd.ptr(x)
except TypeError as e:
    print(e)
print("After ptr:", x)

print(f"\n{YEL}{'WRAP':^40s}{OFF}\n")

try:
    bdd.wrap(x)
except TypeError as e:
    print(e)
print("After Wrap ptr:", x)

print(f"\n{YEL}{'INTY':^40s}{OFF}\n")

try:
    bdd.inty(x)
except TypeError as e:
    print(e)
print("After inty:", x)
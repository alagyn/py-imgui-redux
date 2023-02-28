import sys
sys.path.append("../build/test/Release")

import bdd  # type: ignore

x = bdd.Test(25)
print(x.inc())
print(x.dec(5))

print("static", bdd.Test.stat)

try:
    print(bdd.arrint([0, 1, 2]))
except TypeError:
    print("Failed == bad")

try:
    print(bdd.arrint([0, 1.5, 2.3]))
except TypeError:
    print("Failed == good")

try:
    print(bdd.arrflt([0.0, 1.5, 2.3]))
except TypeError:
    print("Failed == bad")

try:
    print(bdd.arrflt([0.0, 1, 2.3]))
except TypeError:
    print("Failed == bad")

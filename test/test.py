import sys

sys.path.append("../build/test")
sys.path.append("../build/test/Release")

import bdd  # type: ignore

x = bdd.Wrap(5)

print(x)
x.val += 1
print(x)

print(x + 5)
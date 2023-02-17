import sys
sys.path.append("../build/test/Release")

import bdd  # type: ignore

x = bdd.Test(25)
print(x.inc())
print(x.dec(5))

print("static", bdd.Test.stat)

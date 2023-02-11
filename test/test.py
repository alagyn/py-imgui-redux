import sys
sys.path.append("../build/test/Release")

import bdd  # type: ignore

x = "bbbb"
out = bdd.test(x, len(x))
print(x)
print(out)

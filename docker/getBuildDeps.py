import tomli

with open("pyproject.toml", mode='rb') as f:
    root = tomli.load(f)

for x in root['build-system']['requires']:
    print(x, end=" ")

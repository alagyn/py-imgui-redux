# PyImGui-Redux
DearImGui wrapper for python made with PyBind11

Read below for adjustments made to the standard APIs.
Otherwise, all documentation from the original libraries remains 100% valid.
Check out the examples folder for some concrete code.

## Install

Install the latest version with pip
```
pip install py-imgui-redux
```

## Modules:

`imgui` - [Core DearImGUI](https://github.com/ocornut/imgui)  
`imgui.implot` - [ImPlot library](https://github.com/epezent/implot)  
`imgui.imnodes` - [ImNodes library](https://github.com/Nelarius/imnodes)


## Backends:

`imgui.glfw` - GLFW

---

## API Adjustments

I am writing this library with the primary goal of keeping the original Dear ImGui functional
API as intact as possible. This is because:
1. I want to keep all C++ examples and documentation as relevant as possible since I am lazy and don't want to rewrite everything.
2. I have a love-hate relationship with snake-case.

However, there are some minor compromises that have to be made in order to make this happen, primarily in the case of pointers and lists.

Take for instance the function:
```c++
bool DragIntRange2(const char* label, int* v_current_min, int* v_current_max, /* other args... */);
```
1. This function returns true if the state changed
2. `v_current_min` and `v_current_max` are pointers to state, and will be read and updated if a change is made

Typical C++ usage
```c++
int min = 0;
int max = 5;
// Code ...
if(imgui::DragIntRange2("Label", &min, &max))
{
    // Code that happens if a change was made
}
```

Python, however, will not let you pass an integer by reference normally, let alone across the C API.
Therefore, the PyImgui-Redux method of accomplishing this:
```python
min_val = imgui.IntRef(0)
max_val = imgui.IntRef(5)
# Code ...
if imgui.DragIntRange2("Label", min_val, max_val):
    # Code that happens if a change was made
    pass
```

These are thin wrappers around a single value.
```python
imgui.IntRef
imgui.FloatRef
imgui.BoolRef
# The value can be accessed like so
myNum = imgui.IntRef(25)
myNum.val += 2
```

---

The second concession is with lists.  
Take for instance the function
```c++
bool DragInt3(const char* label, int v[3], /* args ... */);
```

A standard python list is stored sequentially in memory, but the raw *values* themselves are wrapped in a python object. Therefore, we cannot easily iterate over *just* the ints/floats, let alone get a pointer to give to ImGui. PyBind11 will happily take a python list and turn it into a vector for us, but in doing so requires making a copy of the list (not ideal for large lists)

This is solved in one of two ways.  

Method 1: PyImgui-Redux Wrappers
```python
vals = imgui.IntList([0, 5, 10])
if imgui.DragInt3("Label", vals):
    # updating code
    pass
```

These are thin wrappers around a C++ vector. They have standard
python list access functions and iteration capabilities.
```python
imgui.IntList
imgui.FloatList
imgui.DoubleList

x = imgui.IntList()
x.append(25)
x.append(36)

print(len(x))

for val in x:
    print(x)

x[0] = 12

```
See their docs for more information and all functions.
  
Functions that mutate the data, such as vanilla ImGui widgets will
use this method. 

Method 2: Numpy Arrays
```python
import numpy as np
xs = np.array([0, 5, 10])
ys = np.array([0, 5, 10])
# Code...
implot.PlotScatter("Scatter", xs, ys, len(xs))
```
The implot submodule uses these, as they prevent the need to copy potentially large arrays, and implot functions will not need to change the data as it reads it. Numpy
is also easier to use for data manipulations as is typical with plotting.

---
Thirdly, references to strings are handled similarily to lists (it's actually a subclass of the List wrappers).

Take for instance the function
```c++
bool InputText(const char* label, char* buf, size_t buf_size, /* args ... */);
```
Which takes a pointer to the IO buffer, and also and argument for its size.

In Python:
```python
myStr = imgui.StrRef("This is a string", maxSize=20)
# Code ...
if imgui.InputText("Label", myStr):
    # code if the text changes
    pass
```
Notice that you don't need to pass the size, this is baked into the StrRef.
Note: `maxSize` automatically takes into account string terminators, i.e. `maxSize=20` means
your string can hold 20 chars.

To change the maxSize:
```python
myStr.resize(25)
```
Changing the size lower will drop any extra chars.

To get your string back
```python
# make a copy
x = str(myStr)
# or
x = myStr.copy()

# get a temporary/unsafe pointer
# useful for printing large strings without copying
# only use said pointer while the object exists
# lest ye summon the dreaded seg-fault
print(myStr.view())
```
See the docs for more info


---

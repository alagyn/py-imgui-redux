# PyImGui-Redux
DearImGui wrapper for python made with PyBind11

Read below for adjustments made to the standard APIs.
Otherwise, all documentation from the original libraries remains 100% valid.
Check out the examples folder for some concrete code.

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

However, there are some minor comprimises that have to be made in order to make this happen, primarily in the case of pointers.

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

A standard python list is stored sequentially in memory, but the raw *values* themselves are wrapped in a python object. Therefore, we cannot easily iterate over *just* the ints/floats, let alone get a pointer to give to ImGui.

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

x = imgui.IntList()
x.append(25)
x.append(36)

print(len(x))

for val in x:
    print(x)

x[0] = 12

```
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
The implot submodule uses these, as they prevent the need to copy potentially large arrays, and will not need to change the data as it reads it. Numpy
is also easier to use for data manipulations as is typical with plotting.


---

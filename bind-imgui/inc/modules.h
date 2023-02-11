#pragma once
#include <utilityDefines.h>

#define MODULE(x) void init_##x(py::module& m)

MODULE(context);
MODULE(cursor_and_layout);
MODULE(demos);
MODULE(windows);
MODULE(stacks);
MODULE(structs);
MODULE(styles);
MODULE(widgets_text);
MODULE(widgets_main);
MODULE(widgets_drags);
MODULE(widgets_slide);
MODULE(widgets_input);
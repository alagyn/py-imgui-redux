#pragma once

#include <pybind11/functional.h>

#include <binder/wraps.h>

using FormatterCallback =
    std::function<int(double, EditableStrWrapper, py::object)>;

struct FormatterCallbackData
{
    FormatterCallback callback;
    py::object userdata;

    FormatterCallbackData(FormatterCallback cb, py::object ud)
        : callback(cb)
        , userdata(ud)
    {
    }
};

int plotFormatterCallback(double value, char* buff, int size, void* user_data);
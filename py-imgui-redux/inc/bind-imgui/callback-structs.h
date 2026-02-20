#pragma once

#include <binder/wraps.h>

#include <imgui.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>

using InputTextCallback = std::function<int(ImGuiInputTextCallbackData*)>;

struct InputTextCallbackData
{
    StrRefPtr value;
    InputTextCallback callback;
    pybind11::object userData;
};

using SizeCallback = std::function<void(ImGuiSizeCallbackData*)>;

struct SizeCallbackData
{
    SizeCallback callback;
    pybind11::object userData;
};
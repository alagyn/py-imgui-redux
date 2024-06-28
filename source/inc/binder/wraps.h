#pragma once
#include <pybind11/pybind11.h>
#include <sstream>
#include <vector>

#include <imgui.h>

// Forward declares of wrapper types
// These are used to wrap arguments that are supposed to be pointers to output variables

template<class T> class Wrapper
{
public:
    T val;

    explicit Wrapper(T val)
        : val(val)
    {
    }

    const char* toStr()
    {
        std::stringstream ss;
        ss << "Wrapper=" << val;
        return ss.str().c_str();
    }
};

using BoolRef_ = Wrapper<bool>;
using BoolRef = BoolRef_*;

using FloatRef_ = Wrapper<float>;
using FloatRef = FloatRef_*;

using DoubleRef_ = Wrapper<double>;
using DoubleRef = DoubleRef_*;

using IntRef_ = Wrapper<int>;
using IntRef = IntRef_*;

template<class T> class ImList
{
protected:
    std::vector<T> vals;

public:
    ImList(std::vector<T> vals)
        : vals(vals)
    {
    }

    ImList()
        : vals()
    {
    }

    void append(T val)
    {
        vals.push_back(val);
    }

    T pop()
    {
        T out = vals.back();
        vals.pop_back();
        return out;
    }

    size_t size()
    {
        return vals.size();
    }

    pybind11::iterator makeIter()
    {
        return pybind11::make_iterator(vals.begin(), vals.end());
    }

    T getItem(int index)
    {
        return vals[index];
    }

    void setItem(int index, T val)
    {
        vals[index] = val;
    }

    T* data()
    {
        return vals.data();
    }

    virtual void resize(size_t size)
    {
        vals.resize(size);
    }

    void clear()
    {
        vals.clear();
    }
};

using IntList = ImList<int>;
using IntListPtr = IntList*;

using FloatList = ImList<float>;
using FloatListPtr = FloatList*;

using DoubleList = ImList<double>;
using DoubleListPtr = DoubleList*;

using StrList = ImList<const char*>;
using StrListPtr = StrList*;

using Vec2List = ImList<ImVec2>;
using Vec2ListPtr = Vec2List*;

class StrRef_ : public ImList<char>
{
public:
    StrRef_(size_t maxSize);
    StrRef_(const char* val, size_t maxSize = 0);
    void set(const char* newVal, size_t maxSize = 0);
    virtual void resize(size_t size) override;
    size_t strSize();
};

using StrRef = StrRef_*;

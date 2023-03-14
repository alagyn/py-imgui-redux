#pragma once
#include <pybind11/stl.h>
#include <sstream>
#include <vector>

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

using BoolRef = Wrapper<bool>;
using FloatRef = Wrapper<float>;
using IntRef = Wrapper<int>;

template<class T> class ImList
{
private:
    std::vector<T> vals;

public:
    ImList(std::vector<T> vals)
        : vals(vals)
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
        return pybind11::make_iterator(vals);
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
};

using IntList = ImList<int>;
using FloatList = ImList<float>;
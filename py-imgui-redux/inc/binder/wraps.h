#pragma once
#include <pybind11/pybind11.h>
#include <sstream>
#include <vector>

#include <imgui.h>

#include <cmath>

// Forward declares of wrapper types
// These are used to wrap arguments that are supposed to be pointers to output variables

template<typename T> class Wrapper
{
public:
    T val;

    explicit Wrapper(T val)
        : val(val)
    {
    }

    const std::string toStr()
    {
        std::stringstream ss;
        ss << "Wrapper=" << val;
        return ss.str();
    }
};

template<typename T> class MathWrapper : public Wrapper<T>
{
public:
    explicit MathWrapper(T val)
        : Wrapper<T>(val)
    {
    }

    // Addition
    MathWrapper<T>& operator+=(T o)
    {
        this->val += o;
        return *this;
    }

    MathWrapper<T>& operator+=(const MathWrapper<T>& o)
    {
        this->val += o.val;
        return *this;
    }

    friend MathWrapper<T> operator+(MathWrapper<T> self, T o)
    {
        // Self is passed by value
        self += o;
        return self;
    }

    friend MathWrapper<T> operator+(MathWrapper<T> self, const MathWrapper<T>& o)
    {
        self += o;
        return self;
    }

    friend T operator+(T o, MathWrapper<T> self)
    {
        return o + self.val;
    }

    // Subtraction
    MathWrapper<T>& operator-=(T o)
    {
        this->val -= o;
        return *this;
    }

    MathWrapper<T>& operator-=(const MathWrapper<T>& o)
    {
        this->val -= o.val;
        return *this;
    }

    friend MathWrapper<T> operator-(MathWrapper<T> self, T o)
    {
        // Self is passed by value
        self -= o;
        return self;
    }

    friend MathWrapper<T> operator-(MathWrapper<T> self, const MathWrapper<T>& o)
    {
        self -= o;
        return self;
    }

    friend T operator-(T o, MathWrapper<T> self)
    {
        return o - self.val;
    }

    // Multiplication
    MathWrapper<T>& operator*=(T o)
    {
        this->val *= o;
        return *this;
    }

    MathWrapper<T>& operator*=(const MathWrapper<T>& o)
    {
        this->val *= o.val;
        return *this;
    }

    friend MathWrapper<T> operator*(MathWrapper<T> self, T o)
    {
        // Self is passed by value
        self *= o;
        return self;
    }

    friend MathWrapper<T> operator*(MathWrapper<T> self, const MathWrapper<T>& o)
    {
        self *= o;
        return self;
    }

    friend T operator*(T o, MathWrapper<T> self)
    {
        return o * self.val;
    }

    // Division
    MathWrapper<T>& operator/=(T o)
    {
        this->val /= o;
        return *this;
    }

    MathWrapper<T>& operator/=(const MathWrapper<T>& o)
    {
        this->val /= o.val;
        return *this;
    }

    friend MathWrapper<T> operator/(MathWrapper<T> self, T o)
    {
        // Self is passed by value
        self /= o;
        return self;
    }

    friend MathWrapper<T> operator/(MathWrapper<T> self, const MathWrapper<T>& o)
    {
        self /= o;
        return self;
    }

    friend T operator/(T o, MathWrapper<T> self)
    {
        return o / self.val;
    }

    // Equality
    friend bool operator==(const MathWrapper<T>& a, const MathWrapper<T>& b)
    {
        return a.val == b.val;
    }

    friend bool operator==(const MathWrapper<T>& a, T b)
    {
        return a.val == b;
    }

    friend bool operator==(T a, const MathWrapper<T>& b)
    {
        return a == b.val;
    }

    // Inequality
    friend bool operator!=(const MathWrapper<T>& a, const MathWrapper<T>& b)
    {
        return a.val != b.val;
    }

    friend bool operator!=(const MathWrapper<T>& a, T b)
    {
        return a.val != b;
    }

    friend bool operator!=(T a, const MathWrapper<T>& b)
    {
        return a != b.val;
    }

    // Comparison <
    friend bool operator<(const MathWrapper<T>& a, const MathWrapper<T>& b)
    {
        return a.val < b.val;
    }

    friend bool operator<=(const MathWrapper<T>& a, const MathWrapper<T>& b)
    {
        return a.val <= b.val;
    }

    friend bool operator<(const MathWrapper<T>& a, T b)
    {
        return a.val < b;
    }

    friend bool operator<=(const MathWrapper<T>& a, T b)
    {
        return a.val <= b;
    }

    friend bool operator<(T a, const MathWrapper<T>& b)
    {
        return a < b.val;
    }

    friend bool operator<=(T a, const MathWrapper<T>& b)
    {
        return a <= b.val;
    }

    // Comparison >
    friend bool operator>(const MathWrapper<T>& a, const MathWrapper<T>& b)
    {
        return a.val > b.val;
    }

    friend bool operator>=(const MathWrapper<T>& a, const MathWrapper<T>& b)
    {
        return a.val >= b.val;
    }

    friend bool operator>(const MathWrapper<T>& a, T b)
    {
        return a.val > b;
    }

    friend bool operator>=(const MathWrapper<T>& a, T b)
    {
        return a.val >= b;
    }

    friend bool operator>(T a, const MathWrapper<T>& b)
    {
        return a > b.val;
    }

    friend bool operator>=(T a, const MathWrapper<T>& b)
    {
        return a >= b.val;
    }
};

MathWrapper<int>& operator%=(MathWrapper<int>& self, int o);
MathWrapper<int>& operator%=(MathWrapper<int>& self, const MathWrapper<int>& o);
MathWrapper<int> operator%(MathWrapper<int> self, int o);
MathWrapper<int> operator%(MathWrapper<int> self, const MathWrapper<int>& o);
int operator%(int o, MathWrapper<int> self);

MathWrapper<float>& operator%=(MathWrapper<float>& self, float o);
MathWrapper<float>&
operator%=(MathWrapper<float>& self, const MathWrapper<float>& o);
MathWrapper<float> operator%(MathWrapper<float> self, float o);
MathWrapper<float>
operator%(MathWrapper<float> self, const MathWrapper<float>& o);
float operator%(float o, MathWrapper<float> self);

MathWrapper<double>& operator%=(MathWrapper<double>& self, double o);
MathWrapper<double>&
operator%=(MathWrapper<double>& self, const MathWrapper<double>& o);
MathWrapper<double> operator%(MathWrapper<double> self, double o);
MathWrapper<double>
operator%(MathWrapper<double> self, const MathWrapper<double>& o);
double operator%(double o, MathWrapper<double> self);

using FloatRef_ = MathWrapper<float>;
using FloatRef = FloatRef_*;

using DoubleRef_ = MathWrapper<double>;
using DoubleRef = DoubleRef_*;

using IntRef_ = MathWrapper<int>;
using IntRef = IntRef_*;

class BoolRef_ : public Wrapper<bool>
{
public:
    BoolRef_(bool val)
        : Wrapper(val)
    {
    }

    inline bool toBool()
    {
        return val;
    }
};

using BoolRef = BoolRef_*;

template<class T> class ImList
{
public:
    std::vector<T> vals;

    ImList(std::vector<T> vals)
        : vals(vals)
    {
    }

    ImList(pybind11::typing::Iterable<T> pvals)
    {
        vals.reserve(pybind11::len(pvals));
        pybind11::iterator iter = pvals.begin();
        for(pybind11::iterator end = pvals.end(); iter != end; ++iter)
        {
            vals.push_back(iter->cast<T>());
        }
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

    T getItem(int index) const
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

using WCharList = ImList<ImWchar>;
using WCharListPtr = WCharList*;

using FloatList = ImList<float>;
using FloatListPtr = FloatList*;

using DoubleList = ImList<double>;
using DoubleListPtr = DoubleList*;

using Vec2List = ImList<ImVec2>;
using Vec2ListPtr = Vec2List*;

using Vec4List = ImList<ImVec4>;
using Vec4ListPtr = Vec4List*;

using ImU32List = ImList<ImU32>;
using ImU32ListPtr = ImU32List*;

class StrRef : public ImList<char>
{
public:
    StrRef(size_t maxSize);
    StrRef(const char* val, size_t maxSize = 0);
    void set(const char* newVal, size_t maxSize = 0);
    virtual void resize(size_t size) override;
    size_t strSize();
    size_t strLen;
    void calcLen();
};

using StrRefPtr = StrRef*;

class EditableStrWrapper
{
public:
    EditableStrWrapper(char* data, size_t size);
    void set(const std::string& val);

    char* buff;
    size_t maxSize;
};

// Separate wrapper so we can maintain a list
// of std::string to handle the memory management,
// and also a vector of ptrs to the start of each string
class StrList
{
public:
    StrList()
    {
    }

    size_t size();
    const char** data();

    void append(const std::string& val);
    void pop();
    std::string getItem(size_t idx);
    void setItem(size_t idx, const std::string& val);
    void clear();

    pybind11::iterator makeIter();

    void reserve(size_t size);

private:
    std::vector<std::string> strs;
    // Pointers to the beginning of each string
    std::vector<const char*> str_ptrs;
};

using StrListPtr = StrList*;

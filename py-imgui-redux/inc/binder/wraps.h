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

    friend MathWrapper<T> operator+(T o, MathWrapper<T> self)
    {
        self.val += o;
        return self;
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

    friend MathWrapper<T> operator-(T o, MathWrapper<T> self)
    {
        self.val = o - self.val;
        return self;
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

    friend MathWrapper<T> operator*(T o, MathWrapper<T> self)
    {
        self.val *= o;
        return self;
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

    friend MathWrapper<T> operator/(T o, MathWrapper<T> self)
    {
        self.val = o / self.val;
        return self;
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
MathWrapper<int> operator%(int o, MathWrapper<int> self);

MathWrapper<float>& operator%=(MathWrapper<float>& self, float o);
MathWrapper<float>&
operator%=(MathWrapper<float>& self, const MathWrapper<float>& o);
MathWrapper<float> operator%(MathWrapper<float> self, float o);
MathWrapper<float>
operator%(MathWrapper<float> self, const MathWrapper<float>& o);
MathWrapper<float> operator%(float o, MathWrapper<float> self);

MathWrapper<double>& operator%=(MathWrapper<double>& self, double o);
MathWrapper<double>&
operator%=(MathWrapper<double>& self, const MathWrapper<double>& o);
MathWrapper<double> operator%(MathWrapper<double> self, double o);
MathWrapper<double>
operator%(MathWrapper<double> self, const MathWrapper<double>& o);
MathWrapper<double> operator%(double o, MathWrapper<double> self);

using BoolRef_ = Wrapper<bool>;
using BoolRef = BoolRef_*;

using FloatRef_ = MathWrapper<float>;
using FloatRef = FloatRef_*;

using DoubleRef_ = MathWrapper<double>;
using DoubleRef = DoubleRef_*;

using IntRef_ = MathWrapper<int>;
using IntRef = IntRef_*;

template<class T> class ImList
{
public:
    std::vector<T> vals;

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

using StrList = ImList<const char*>;
using StrListPtr = StrList*;

using Vec2List = ImList<ImVec2>;
using Vec2ListPtr = Vec2List*;

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

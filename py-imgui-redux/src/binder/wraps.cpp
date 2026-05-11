#include <binder/bind-modules.h>
#include <binder/list-wrapper.h>
#include <binder/wraps.h>

#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <sstream>

namespace py = pybind11;

StrRef::StrRef(size_t maxSize)
    : ImList<char>(std::vector<char>(maxSize + 1))
    , strLen(0)
{
    // Set first char to zero to terminate string
    vals[0] = 0;
}

StrRef::StrRef(const char* val, size_t maxSize)
    : ImList<char>(std::vector<char>())
{
    if(maxSize == 0)
    {
        maxSize = std::strlen(val);
    }
    vals.resize(maxSize + 1);
    std::strncpy(vals.data(), val, maxSize);
}

void StrRef::set(const char* newVal, size_t maxSize)
{
    if(maxSize != 0)
    {
        vals.resize(maxSize + 1);
    }
    std::strncpy(vals.data(), newVal, vals.size());
    strLen = strlen(vals.data());
}

void StrRef::resize(size_t maxSize)
{
    size_t oldSize = vals.size() - 1;
    vals.resize(maxSize + 1);

    // If we shrunk
    if(maxSize < oldSize)
    {
        // Make sure the str is null terminated
        vals[maxSize] = '\0';
    }
}

size_t StrRef::strSize()
{
    return strLen;
}

void StrRef::calcLen()
{
    this->strLen = strnlen(vals.data(), vals.size());
}

size_t StrList::size()
{
    return strs.size();
}

const char** StrList::data()
{
    return str_ptrs.data();
}

void StrList::append(const std::string& val)
{
    strs.push_back(val);
    str_ptrs.push_back(strs.back().data());
}

void StrList::pop()
{
    strs.pop_back();
    str_ptrs.pop_back();
}

std::string StrList::getItem(size_t idx)
{
    return strs[idx];
}

void StrList::setItem(size_t idx, const std::string& val)
{
    strs[idx] = val;
    str_ptrs[idx] = strs[idx].data();
}

void StrList::clear()
{
    strs.clear();
    str_ptrs.clear();
}

void StrList::reserve(size_t size)
{
    strs.reserve(size);
    str_ptrs.reserve(size);
}

pybind11::iterator StrList::makeIter()
{
    return pybind11::make_iterator(str_ptrs.begin(), str_ptrs.end());
}

template<class T, class U>
void initRef(py::module& m, const char* name, const char* desc, U defaultVal)
{
    py::class_<T>(m, name, desc)
        .def(py::init<U>(), "val"_a = defaultVal)
        .def_readwrite("val", &T::val, "The wrapped value")
        .def("__str__", &T::toStr);
}

template<class T, class U>
void initMathRef(py::module& m, const char* name, const char* desc, U defaultVal)
{
    py::class_<T>(m, name, desc)
        .def(py::init<U>(), "val"_a = defaultVal)
        .def_readwrite("val", &T::val, "The wrapped value")
        .def("__str__", &T::toStr)
        // Addition
        .def(py::self += U())
        .def(py::self += py::self)
        .def(py::self + U())
        .def(py::self + py::self)
        .def(U() + py::self)
        // Subtraction
        .def(py::self -= U())
        .def(py::self -= py::self)
        .def(py::self - U())
        .def(py::self - py::self)
        .def(U() - py::self)
        // Multiplication
        .def(py::self *= U())
        .def(py::self *= py::self)
        .def(py::self * U())
        .def(py::self * py::self)
        .def(U() * py::self)
        // Division
        .def(py::self /= U())
        .def(py::self /= py::self)
        .def(py::self / U())
        .def(py::self / py::self)
        .def(U() / py::self)
        // Modulus
        .def(py::self %= U())
        .def(py::self %= py::self)
        .def(py::self % U())
        .def(py::self % py::self)
        .def(U() % py::self)
        // Equality
        .def(py::self == py::self)
        .def(py::self == U())
        .def(U() == py::self)
        // Inequality
        .def(py::self != py::self)
        .def(py::self != U())
        .def(U() != py::self)
        // Comparison <
        .def(py::self < py::self)
        .def(py::self <= py::self)
        .def(py::self < U())
        .def(py::self <= U())
        .def(U() < py::self)
        .def(U() <= py::self)
        // Comparison >
        .def(py::self > py::self)
        .def(py::self >= py::self)
        .def(py::self > U())
        .def(py::self >= U())
        .def(U() > py::self)
        .def(U() >= py::self);
}

template<class T, class U>
py::class_<T> initList(py::module& m, const char* name, const char* desc)
{
    return py::class_<T>(m, name, desc)
        .def(py::init<>())
        .def(py::init<py::typing::Iterable<U>>(), "vals"_a)
        .def("append", &T::append, "val"_a, "Append a value to the end")
        .def("pop", &T::pop, "Pop a value from the end")
        .def(
            "resize",
            &T::resize,
            "size"_a,
            "Resize the vector, dropping any lost values"
        )
        .def("clear", &T::clear)
        .def("__len__", &T::size)
        .def("__iter__", &T::makeIter)
        .def("__getitem__", &T::getItem, "index"_a)
        .def("__setitem__", &T::setItem, "index"_a, "val"_a);
}

EditableStrWrapper::EditableStrWrapper(char* data, size_t maxSize)
    : buff(data)
    , maxSize(maxSize - 1) // minus one for zero char
{
}

void EditableStrWrapper::set(const std::string& val)
{
    size_t toCopy = std::min(maxSize, val.size());
    for(size_t i = 0; i < toCopy; ++i)
    {
        buff[i] = val[i];
    }
    buff[toCopy] = 0;
}

void init_wraps(py::module& m)
{
    initMathRef<IntRef_>(m, "IntRef", "A pass-by-ref wrapper for an int", 0);
    initMathRef<FloatRef_>(
        m,
        "FloatRef",
        "A pass-by-ref wrapper for a float",
        0.0f
    );
    initMathRef<DoubleRef_>(
        m,
        "DoubleRef",
        "A pass-by-ref wrapper for a double",
        0.0
    );

    py::class_<BoolRef_>(m, "BoolRef", "A pass-by-ref wrapper for a bool")
        .def(py::init<bool>(), "val"_a = false)
        .def_readwrite("val", &BoolRef_::val, "The wrapped value")
        .def("__str__", &BoolRef_::toStr)
        .def("__bool__", &BoolRef_::toBool);

    initList<IntList, int>(m, "IntList", "Thin wrapper over a std::vector<int>");
    auto u32list = initList<ImU32List, ImU32>(
        m,
        "ImU32List",
        "Thin wrapper over a std::vector<ImU32>"
    );
    m.add_object("WCharList", u32list);

    initList<FloatList, float>(
        m,
        "FloatList",
        "Thin wrapper over a std::vector<float>"
    );
    initList<DoubleList, double>(
        m,
        "DoubleList",
        "Thin wrapper over a std::vector<double>"
    );
    initList<Vec2List, ImVec2>(
        m,
        "Vec2List",
        "Thin wrapper over a std::vector<ImVec2>"
    );
    initList<Vec4List, ImVec4>(
        m,
        "Vec4List",
        "Thin wrapper over a std::vector<ImVec4>"
    );

    py::class_<StrRef>(m, "StrRef", "Thin wrapper over a std::vector<char>")
        .def(
            py::init<size_t>(),
            "maxSize"_a,
            "Initialize an empty string with reserved size"
        )
        .def(
            py::init<const char*, size_t>(),
            "value"_a,
            "maxSize"_a = 0,
            "Initialize with an input string. If maxSize=0, then "
            "maxSize=len(val)"
        )
        .def("append", &StrRef::append, "val"_a, "Append a value to the end")
        .def("pop", &StrRef::pop, "Pop a value from the end")
        .def(
            "resize",
            &StrRef::resize,
            "size"_a,
            "Resize the vector, dropping any lost values"
        )
        .def("__len__", &StrRef::strSize)
        .def("__str__", &StrRef::data, py::return_value_policy::copy)
        .def(
            "copy",
            &StrRef::data,
            py::return_value_policy::copy,
            "Get a copy of the string"
        )
        .def(
            "set",
            &StrRef::set,
            "newVal"_a,
            "maxSize"_a = 0,
            "Assign a new value to the string. If maxSize=0,"
            "the maxSize will remain unchanged and extra chars will be "
            "dropped"
        );

    py::class_<StrList>(
        m,
        "StrList",
        "A thin wrapper around std::vector<const char*>"
    )
        .def(py::init<>())
        .def(
            py::init(
                [](py::typing::Iterable<std::string> vals)
                {
                    StrList out;
                    out.reserve(py::len(vals));
                    for(auto val : vals)
                    {
                        out.append(val.cast<std::string>());
                    }
                    return out;
                }
            ),
            "vals"_a
        )
        .def("append", &StrList::append, "val"_a, "Append a value to the end")
        .def("pop", &StrList::pop, "Pop a value from the end")
        .def("clear", &StrList::clear)
        .def("__len__", &StrList::size)
        .def("__iter__", &StrList::makeIter)
        .def("__getitem__", &StrList::getItem, "index"_a)
        .def("__setitem__", &StrList::setItem, "index"_a, "val"_a);

    initListWrapper<unsigned char>(m, "ListWrapperUC");
    initListWrapper<unsigned short>(m, "ListWrapperUS");
    initListWrapper<unsigned int>(m, "ListWrapperUInt");
    initListWrapper<float>(m, "ListWrapperF");
    initListWrapper<const char*>(m, "ListWrapperStr");
    initConstListWrapper<bool>(m, "ConstListWrapperBool");
    initConstListWrapper<unsigned char>(m, "ConstListWrapperUChar");
    initConstListWrapper<unsigned short>(m, "ConstListWrapperUShort");
    initConstListWrapper<double>(m, "ConstListWrapperDouble");
    initConstListWrapper<float>(m, "ConstListWrapperFloat");

    py::class_<EditableStrWrapper>(m, "EditableStrWrapper")
        .def("set", &EditableStrWrapper::set, "val"_a)
        .def_readonly("size", &EditableStrWrapper::maxSize);
}

// Modulus Int
MathWrapper<int>& operator%=(MathWrapper<int>& self, int o)
{
    self.val %= o;
    return self;
}

MathWrapper<int>& operator%=(MathWrapper<int>& self, const MathWrapper<int>& o)
{
    self.val %= o.val;
    return self;
}

MathWrapper<int> operator%(MathWrapper<int> self, int o)
{
    self %= o;
    return self;
}

MathWrapper<int> operator%(MathWrapper<int> self, const MathWrapper<int>& o)
{
    self %= o;
    return self;
}

int operator%(int o, MathWrapper<int> self)
{
    return o % self.val;
}

// Modulus float
MathWrapper<float>& operator%=(MathWrapper<float>& self, float o)
{
    self.val = std::fmod(self.val, o);
    return self;
}

MathWrapper<float>&
operator%=(MathWrapper<float>& self, const MathWrapper<float>& o)
{
    self.val = std::fmod(self.val, o.val);
    return self;
}

MathWrapper<float> operator%(MathWrapper<float> self, float o)
{
    self %= o;
    return self;
}

MathWrapper<float> operator%(MathWrapper<float> self, const MathWrapper<float>& o)
{
    self %= o;
    return self;
}

float operator%(float o, MathWrapper<float> self)
{
    return std::fmod(o, self.val);
}

// Modulus double
MathWrapper<double>& operator%=(MathWrapper<double>& self, double o)
{
    self.val = std::fmod(self.val, o);
    return self;
}

MathWrapper<double>&
operator%=(MathWrapper<double>& self, const MathWrapper<double>& o)
{
    self.val = std::fmod(self.val, o.val);
    return self;
}

MathWrapper<double> operator%(MathWrapper<double> self, double o)
{
    self.val = std::fmod(self.val, o);
    return self;
}

MathWrapper<double>
operator%(MathWrapper<double> self, const MathWrapper<double>& o)
{
    self %= o;
    return self;
}

double operator%(double o, MathWrapper<double> self)
{
    return std::fmod(o, self.val);
}

#ifndef UWUTILS_ABS_HPP
#define UWUTILS_ABS_HPP

#include "concepts.hpp"

namespace uwutils {

// class to hold an value and guarantee to not change it
template<typename _Tp>
class Abs {
    const _Tp data;
public:
    Abs() = delete;
    Abs(Abs&&) = delete;
    Abs(const Abs&) = delete;
    Abs(const _Tp& c) {
        data = c;
    }

    Abs& operator=(Abs&&) = delete;
    Abs& operator=(const Abs&) = delete;
    Abs& operator=(_Tp) = delete;

    operator const _Tp&() { return data; }
    const _Tp& unwrap() { return data; }
};

}

#endif
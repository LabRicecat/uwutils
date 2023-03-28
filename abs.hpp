#ifndef UWUTILS_ABS_HPP
#define UWUTILS_ABS_HPP

#include "concepts.hpp"
#include "interface.hpp"

namespace uwutils {

// class to hold an value and guarantee to not change it
template<typename _Tp>
class Abs : public IContainer<_Tp> {
    _Tp data;
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

    template<ConvertableTo<_Tp> _Tpr>
    operator const _Tpr() const { return data; }
    template<ConvertableTo<_Tp> _Tpr>
    operator const _Tpr&() { return data; }
    const _Tp& view() const override { return data; }
};

}

#endif
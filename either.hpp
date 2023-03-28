#ifndef UWUTILS_EITHER_HPP
#define UWUTILS_EITHER_HPP

#include "error.hpp"
#include "dynamic.hpp"

namespace uwutils {

// class able to hold two different values
template<typename _Tp1, typename _Tp2>
class Either {
    size_t _idx = 0;
    Dynamic dyn;
public:
    Either() = delete;
    Either(const Either<_Tp1,_Tp2>& c) {
        _idx = c._idx;
        if(c._idx == 0) 
            dyn.set(c.dyn.as<_Tp1>());
        else dyn.set(c.dyn.as<_Tp2>());
    }
    Either(Either<_Tp1,_Tp2>&& c) {
        _idx = c._idx;
        if(c._idx == 0) 
            dyn.set(c.dyn.as<_Tp1>());
        else dyn.set(c.dyn.as<_Tp2>());
    }
    Either(const _Tp1& t) 
    : dyn(t) {
        _idx = 0;
    }
    Either(const _Tp2& t) 
    : dyn(t) {
        _idx = 1;
    }

    template<ThisType<_Tp1> _Tpr>
    _Tp1& get() uwunsafe {
        if(_idx == 0) return dyn.as<_Tp1>();
        else throw MessageException("Not set!");
    }
    template<ThisType<_Tp2> _Tpr>
    _Tp2& get() uwunsafe {
        if(_idx == 1) return dyn.as<_Tp2>();
        else throw MessageException("Not set!");
    }

    template<EitherType<_Tp1,_Tp2> _Tpr>
    bool is() {
        return (typeid(_Tpr) == typeid(_Tp1) && _idx == 0) || (typeid(_Tpr) == typeid(_Tp2) && _idx == 1);
    }

    ~Either() {
        if(_idx == 0)
            dyn.clear<_Tp1>();
        else dyn.clear<_Tp2>();
    }

    Either& operator=(const Either<_Tp1,_Tp2>& c) {
        _idx = c._idx;
        if(c._idx == 0) 
            dyn.set(c.dyn.as<_Tp1>());
        else dyn.set(c.dyn.as<_Tp2>());

        return *this;
    }

    Either& operator=(const _Tp1& t) {
        if(_idx == 0)
            dyn.clear<_Tp1>();
        else dyn.clear<_Tp2>();
        _idx = 0;
        dyn = t;
        return *this;
    }
    Either& operator=(const _Tp2& t) {
        if(_idx == 0)
            dyn.clear<_Tp1>();
        else dyn.clear<_Tp2>();
        _idx = 1;
        dyn = t;
        return *this;
    }
};

}

#endif
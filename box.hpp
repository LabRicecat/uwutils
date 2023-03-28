#ifndef UWUTILS_BOX_HPP
#define UWUTILS_BOX_HPP

#include "dynamic.hpp"
#include "interface.hpp"

namespace uwutils {

// class to add a "NULL" option to it's value
template<typename _Tp>
class Box : public IMutContainer<_Tp> {
    Dynamic dyn;
    bool has_dyn = false;
public:
    bool has() const { return has_dyn; }

    Box(const Box<_Tp>& b) {
        if(b.has_dyn) {
            dyn = b.dyn.copy<_Tp>();
            has_dyn = true;
        } 
    }

    Box(const _Tp& t): dyn(t) { has_dyn = true; }
    Box():dyn() {}

    template<Not<Box<_Tp>> _Tpr>
    Box(const _Tpr& t) requires Not<_Tp,_Tpr> && AssignAble_w<_Tp,_Tpr>
    : dyn(new _Tp(t)) {
        dyn.as<_Tp>() = t;
        has_dyn = true;
    }

    template<Not<_Tp> _Tpr>
    Box<_Tp>& operator=(const _Tpr& t) requires AssignAble_w<_Tp,_Tpr> {
        if(!has()) {
            clear();
            dyn = t;
        }
        else dyn.as<_Tp>() = t;
        has_dyn = true;
        return *this;
    }

    Box<_Tp>& operator=(const _Tp& t) {
        clear();
        dyn = t;
        has_dyn = true;
        return *this;
    }

    template<Not<_Tp> _Tpr>
    Box<_Tp>& operator=(const Box<_Tp>& b) {
        clear();
        if(b.has()) {
            dyn = b.dyn.copy<_Tp>();
            has_dyn = true;
        }
        return *this;
    }

    Box<_Tp>& clear() {
        dyn.clear<_Tp>();
        has_dyn = false;
        return *this;
    }
    
    ~Box() {
        dyn.clear<_Tp>();
        has_dyn = false;
    }

    const _Tp& view() const override { return dyn.as<_Tp>(); }
    _Tp& unwrap() override {
        return dyn.as<_Tp>();
    }

    operator _Tp&() override { return dyn.as<_Tp>(); }
    operator const _Tp() const override { return dyn.as<_Tp>(); }
};

}

#endif
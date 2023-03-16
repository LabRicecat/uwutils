#ifndef UWUTILS_BOX_HPP
#define UWUTILS_BOX_HPP

#include "dynamic.hpp"

namespace uwutils {

// class to add a "NULL" option to it's value
template<typename _Tp>
class Box {
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

    Box<_Tp>& operator=(const _Tp& t) {
        clear();
        dyn = t;
        has_dyn = true;
        return *this;
    }

    template<Not<_Tp> _Tpr>
    Box<_Tp>& operator=(const Box<_Tp>& b) {
        std::cout << "bxcpy\n";
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

    _Tp& unwrap() {
        return dyn.as<_Tp>();
    }

    operator _Tp&() {
        return dyn.as<_Tp>();
    }
};

}

#endif
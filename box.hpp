#ifndef UWUTILS_BOX_HPP
#define UWUTILS_BOX_HPP

#include "dynamic.hpp"

namespace uwutils {

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

    Box<_Tp>& operator=(const _Tp& t) {
        clear();
        dyn = t;
        has_dyn = true;
        return *this;
    }

    template<typename _Tpr>
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

    _Tp& unwrap() {
        return dyn.as<_Tp>();
    }

    operator _Tp&() {
        return dyn.as<_Tp>();
    }
};

}

#endif
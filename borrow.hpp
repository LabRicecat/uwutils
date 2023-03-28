#ifndef UWUTILS_BORROW_HPP
#define UWUTILS_BORROW_HPP

#include "concepts.hpp"
#include "throw.hpp"
#include "interface.hpp"

namespace uwutils {

// class that loses permission to change it's value once it gets passed
template<CopyAble _Tp>
class Borrow : public IContainer<_Tp> {
    _Tp source;
    bool assignable = false;
public:
    Borrow(Borrow&& p) 
    : source(p) {
        assignable = false;
    }

    Borrow(const _Tp& p) 
    : source(p) {
        assignable = true;
    }

    Borrow(const Borrow<_Tp>& b) 
    : source(_Tp(b.source)) {
        assignable = false;
    }

    template<Not<Borrow<_Tp>> _Tpr>
    Borrow(const _Tpr& p) requires AssignAble_w<_Tp,_Tpr> 
    : source(p) {
        assignable = true;
    }

    template<Not<Borrow<_Tp>> _Tpr>
    Borrow<_Tp>& operator=(const _Tpr& p) requires AssignAble_w<_Tp,_Tpr> {
        if(assignable) source = p;
        else throw MessageException("Assign to unowned object");
        return *this;
    }

    Borrow<_Tp>& operator=(const _Tp& p) {
        if(assignable) source = p;
        else throw MessageException("Assign to unowned object");
        return *this;
    }

    Borrow<_Tp>& operator=(const Borrow<_Tp>& b) {
        assignable = false;
        source = b;
        return *this;
    } 

    Borrow<_Tp>& operator=(Borrow<_Tp>&& b) {
        assignable = false;
        source = b;
        return *this;
    } 

    operator const _Tp&() { return source; }

    _Tp& ref() uwunsafe {
        if(assignable) return source;
        throw MessageException("Reference request to unowned object");
    }

    const _Tp& view() const override { return source; }

    Borrow<int>& lose() {
        assignable = false;
        return *this;
    }
};

}

#endif
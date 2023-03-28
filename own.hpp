#ifndef UWUTILS_OWN_HPP
#define UWUTILS_OWN_HPP

#include "borrow.hpp"

namespace uwutils {

// class that stores data and which can give up it's access when passed
template<CopyAble _Tp>
class Own {
    _Tp source;
    bool assignable = false;
public:
    Own() = delete;
    Own(const _Tp& p) 
    : source(p) {
        assignable = true;
    }
    
    Own(const Own<_Tp>&) = delete;
    Own(Own<_Tp>& b) 
    : source(_Tp(b.source)) {
        assignable = true;
        b.assignable = false;
    }

    template<Not<Own<_Tp>> _Tpr>
    Own(const _Tpr& p) requires AssignAble_w<_Tp,_Tpr> 
    : source(p) {
        assignable = true;
    }

    template<Not<Own<_Tp>> _Tpr>
    Own<_Tp>& operator=(const _Tpr& p) requires AssignAble_w<_Tp,_Tpr> {
        if(assignable) source = p;
        else throw MessageException("Assign to unowned object");
        return *this;
    }

    Own<_Tp>& operator=(const _Tp& p) {
        if(assignable) source = p;
        else throw MessageException("Assign to unowned object");
        return *this;
    }

    Own<_Tp>& operator=(const Own<_Tp>&) = delete;
    Own<_Tp>& operator=(Own<_Tp>& b) {
        assignable = true;
        b.assignable = false;
        source = b.source;
        return *this;
    } 

    operator const _Tp&() { return source; }

    _Tp& ref() uwunsafe {
        if(assignable) return source;
        throw MessageException("Reference request to unowned object");
    }

    const _Tp& view() { return source; }

    Borrow<_Tp> borrow() {
        if(assignable) return Borrow<_Tp>(source);
        throw MessageException("Borrow request to unowned object");
    }
};

}

#endif
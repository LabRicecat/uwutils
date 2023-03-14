#ifndef UWUTILS_BORROW_HPP
#define UWUTILS_BORROW_HPP

#include "concepts.hpp"
#include "throw.hpp"

namespace uwutils {

template<CopyAble _Tp>
class Borrow {
    _Tp source;
    bool assignable = false;
public:
    Borrow(const _Tp& p) {
        source = p;
        assignable = true;
    }

    Borrow(const Borrow<_Tp>& b) {
        assignable = false;
        source = _Tp(b.source);
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

    operator const _Tp() { return source; }

    _Tp& ref() {
        if(assignable) return source;
        throw MessageException("Reference request to unowned object");
    }
};

}

/*

foo(Borrow<int> b) {
    b = 3; // error
}

Borrow<int> b;
b = 4; // valid
foo(b); // error
b = 2; // valid

*/

#endif
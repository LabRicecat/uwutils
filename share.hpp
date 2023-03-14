#ifndef UWUTILS_SHARE_HPP
#define UWUTILS_SHARE_HPP

#include "keeper.hpp"

namespace uwutils {

template<CopyAble _Tp>
class Share {
    Keeper<_Tp> keeper;
public:
    Share() = delete;
    Share(const Share& s) 
    : keeper(s.keeper) {}
    Share(const _Tp& c) 
    : keeper(new _Tp(c)) {}

    Share& operator=(const _Tp& c) {
        keeper.unwrap() = c;
        return *this;
    }

    operator _Tp&() {
        return keeper.unwrap();
    }

    _Tp& unwrap() { return keeper.unwrap(); }
};

}

#endif
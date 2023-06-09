#ifndef UWUTILS_SHARE_HPP
#define UWUTILS_SHARE_HPP

#include "keeper.hpp"

namespace uwutils {

// class where every copy can access the main stored data
template<CopyAble _Tp>
class Share : IContainer<_Tp> {
    Keeper<_Tp> keeper;
public:
    Share() = delete;
    Share(const Share& s) 
    : keeper(s.keeper) {}
    Share(const _Tp& c) 
    : keeper(new _Tp(c)) {}
    template<Not<_Tp> _Tpr>
    Share(const _Tpr& c) requires AssignAble_w<_Tp,_Tpr> && requires { new _Tp(c); }
    :keeper(new _Tp(c)) {}
    template<Not<_Tp> _Tpr>
    Share(_Tp& c) 
    :keeper(std::addressof(c),false) {}

    Share& operator=(const _Tp& c) {
        keeper.unwrap() = c;
        return *this;
    }

    operator _Tp&() {
        return keeper.unwrap();
    }

    operator _Tp() const {
        return keeper.unwrap();
    }

    template<Not<_Tp> _Tpr>
    Share& operator=(const _Tpr& c) requires AssignAble_w<_Tp,_Tpr> {
        keeper.unwrap() = c;
        return *this;
    }

    const _Tp& view() const override { return keeper.unwrap(); }
    _Tp& unwrap() { return keeper.unwrap(); }
    const _Tp& unwrap() const { return keeper.unwrap(); }
};

}

#endif
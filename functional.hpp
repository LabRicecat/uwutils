#ifndef UWUTILS_FUNCTIONAL_HPP
#define UWUTILS_FUNCTIONAL_HPP

#include "concepts.hpp"
#include <tuple>

namespace uwutils {

template<CallAble... _Tpl>
auto cross(_Tpl... _Tlist) {
    return std::make_tuple((_Tlist)()...);
};

template<typename _Tp, CallAble_w<_Tp> _Tpf>
auto markov(const _Tpf& f, const _Tp& s) {
    _Tp state = s;
    auto nextstate = f(state);
    while(nextstate != state) {
        state = nextstate;
        nextstate = f(state);
    } 
    return state;
}

template<IteratAble _Tpl, CallAble_w<ElementOf<_Tpl>&> _Tpf>
_Tpl map(_Tpl l, const _Tpf& f) {
    for(auto& _i : l)
        f(_i);
    return l;
}

}

#endif
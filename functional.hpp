#ifndef UWUTILS_FUNCTIONAL_HPP
#define UWUTILS_FUNCTIONAL_HPP

#include "concepts.hpp"
#include <tuple>

namespace uwutils {

template<IteratAble _Tpl>
class FnRes;

namespace fn {

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
FnRes<_Tpl> map(_Tpl l, const _Tpf& f) {
    for(auto& _i : l)
        f(_i);
    return FnRes<_Tpl>(l);
}

template<IteratAble _Tpl, CallAble_wt<const ElementOf<_Tpl>&,const ElementOf<_Tpl>&, const ElementOf<_Tpl>&> _Tpf>
ElementOf<_Tpl> reduce(const _Tpl& l, const _Tpf& f) requires requires(_Tpl l, _Tpf f, ElementOf<_Tpl> e, int x) { e = f(e,*l.begin()); } {
    ElementOf<_Tpl> r = *l.begin();
    for(auto _i = l.begin()+1; _i != l.end(); ++_i)
        r = f(r,*_i);
    return r;
}

template<IteratAble _Tpl, CallAble_w<ElementOf<_Tpl>&> _Tpf>
FnRes<_Tpl> oneach(_Tpl l, const ElementOf<_Tpl>& eq, const _Tpf& f) requires Eq<ElementOf<_Tpl>> {
    for(auto& _i : l) {
        if(_i == eq)
            f(_i);
    }
    return FnRes<_Tpl>(l);
}

template<IteratAble _Tpl>
FnRes<_Tpl> wipe(_Tpl l, const ElementOf<_Tpl>& eq) requires Eq<ElementOf<_Tpl>> && EraseAble<_Tpl> {
    size_t c = 0;
    for(auto& i : l) {
        if(i == eq)
            l.erase(l.begin() + c);
        ++c;
    }
    return FnRes<_Tpl>(l);
}

template<IteratAble _Tpl, CallAble_wt<bool,const ElementOf<_Tpl>&> _Tpf>
FnRes<_Tpl> wipe_if(const _Tpl& l, const _Tpf& f) requires EraseAble<_Tpl> {
    long c = 0;
    _Tpl lc = l;
    for(auto& i : l) {
        if(f(i)) {
            lc.erase(lc.begin() + c);
            if(c != 0) --c;
        }
        else ++c;
    }
    return FnRes<_Tpl>(lc);
}

}

template<IteratAble _Tpl>
class FnRes {
    _Tpl _d;
    using elemT = ElementOf<_Tpl>;
public:
    FnRes(const _Tpl& d): _d(d) {}

    template<CallAble_w<elemT&> _Tpf>
    FnRes& map(const _Tpf& f) {
        *this = uwutils::fn::map(_d,f);
        return *this;
    }
    template<CallAble_wt<const ElementOf<_Tpl>&,const ElementOf<_Tpl>&, const ElementOf<_Tpl>&> _Tpf>
    const ElementOf<_Tpl> reduce(const _Tpf& f) requires requires(_Tpl l, _Tpf f, ElementOf<_Tpl> e, int x) { e = f(e,l[x]); } {
        return uwutils::fn::reduce(_d,f);
    }
    template<CallAble_wt<elemT> _Tpf>
    FnRes& oneach(const elemT& eq, const _Tpf& f) requires Eq<elemT> {
        *this = uwutils::fn::oneach(_d,eq,f);
        return *this;
    }
    FnRes& wipe(const elemT& eq) requires Eq<elemT> && EraseAble<_Tpl> {
        *this = uwutils::fn::wipe(_d,eq);
        return *this;
    }
    template<CallAble_wt<bool,const ElementOf<_Tpl>&> _Tpf>
    FnRes& wipe_if(const _Tpf& f) requires EraseAble<_Tpl> {
        *this = uwutils::fn::wipe_if(_d,f);
        return *this;
    }

    _Tpl origin() const { return _d; }

    operator const _Tpl&() { return _d; }
};

}

#endif
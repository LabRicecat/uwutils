#ifndef UWUTILS_KEEPER_HPP
#define UWUTILS_KEEPER_HPP

#include "dynamic.hpp"
#include <unordered_map>

namespace uwutils {

// class that keeps its data alive as long as one reference exists
template<typename _Tp>
class Keeper : IContainer<_Tp*> {
    bool delme = true;
    _Tp* _p = nullptr;
    inline static std::unordered_map<_Tp*, long long> _s;

    void lose_ref() {
        --_s[_p];
        if(_s[_p] <= 0) {
            _s.erase(_p);
            if(delme) delete _p;
            _p = nullptr;
        }
    }
    void add_ref() {
        ++_s[_p];
    }
public:
    Keeper() = delete;
    Keeper(_Tp* p) {
        _p = p;
        add_ref();
    }
    Keeper(_Tp* p, bool delme) {
        _p = p;
        add_ref();
        this->delme = delme;
    }
    Keeper(Keeper&& keeper) {
        if(_p == keeper._p) return;
        _p = keeper._p;
        add_ref();
        delme = keeper.delme;
    }
    Keeper(const Keeper& keeper) {
        if(keeper._p == _p) return;
        _p = keeper._p;
        add_ref();
        delme = keeper.delme;
    }

    Keeper& operator=(const Keeper& keeper) {
        if(_p == keeper._p) return *this;
        lose_ref();
        _p = keeper._p;
        add_ref();
        delme = keeper.delme;
        return *this;
    }
    Keeper& operator=(Keeper&& keeper) {
        if(_p == keeper._p) return *this;
        lose_ref();
        _p = keeper._p;
        add_ref();
        delme = keeper.delme;
        return *this;
    }

    Keeper& operator=(_Tp* t) {
        if(_p == t) return *this;
        lose_ref();
        _p = t;
        add_ref();
        return *this;
    }

    ~Keeper() {
        lose_ref();
    }

    _Tp& unwrap() {
        return *_p;
    }
    const _Tp& unwrap() const {
        return *_p;
    }

    virtual _Tp* const& view() uwunsafe const override { return _p; }
};


}

#endif
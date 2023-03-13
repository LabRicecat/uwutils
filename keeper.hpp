#ifndef UWUTILS_KEEPER_HPP
#define UWUTILS_KEEPER_HPP

#include "dynamic.hpp"
#include <unordered_map>

namespace uwutils {

template<typename _Tp>
class Keeper {
    _Tp* _p;
    inline static std::unordered_map<_Tp*, long long> _s;
public:
    Keeper() = delete;
    Keeper(_Tp* p) {
        _p = p;
        ++_s[_p];
    }

    Keeper(const Keeper& keeper) {
        _p = keeper._p;
        ++_s[_p];
    }

    ~Keeper() {
        --_s[_p];
        if(_s[_p] == 0) {
            _s.erase(_p);
            delete _p;
            _p = nullptr;
        }
    }

    _Tp& unwrap() {
        return *_p;
    }
};


}

#endif
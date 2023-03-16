#ifndef UWUTILS_LIFETIME_HPP
#define UWUTILS_LIFETIME_HPP

#include "concepts.hpp"
#include "keeper.hpp"

#include <vector>
#include <functional>

namespace uwutils {

template<CopyAble _Tp>
class Living;

// class that defines the lifetime of `Living` objects
class Lifetime {
    std::vector<std::function<void()>> _dels;
    bool _dead = false;
public:
    Lifetime() {}
    Lifetime(const Lifetime&) = delete;
    Lifetime(Lifetime&&) = delete;

    bool dead() const { return _dead; }

    void die() {
        if(_dead) return; 
        for(auto i : _dels)
            i();
        _dels = {};
        _dead = true; 
    }

    ~Lifetime() {
        die();
    }

    template<CopyAble _Tp>
    friend class Living;
};

// class with a defined `Lifetime` at which end it gets deleted
template<CopyAble _Tp>
class Living {
    _Tp* data;
    bool _dead = false;
public:
    Living() = delete;
    Living(const Living& l) {
        data = l.data;
    }
    Living(Living&& l) = delete;
    Living(Lifetime& lt, const _Tp& d) {
        lt._dels.push_back([&]() { delete data; data = nullptr; _dead = true; });
        data = new _Tp(d);
    }

    template<AssignAble_w<_Tp> _Tpr>
    Living<_Tp>& operator=(const _Tpr& t) {
        data = new _Tpr(t);
        return *this;
    }

    bool dead() const { return _dead; }

    void die() { 
        _dead = true;
    }

    Living<_Tp>& revive(Lifetime& lt) {
        lt._dels.push_back([&]() { delete data; data = nullptr; _dead = true; });
        _dead = false;
        return *this;
    }

    operator _Tp&() { 
        if(_dead) { 
            throw MessageException("Usage of dead object");
        }
        return *data;
    }
};

}

#endif
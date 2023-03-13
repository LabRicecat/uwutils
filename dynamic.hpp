#ifndef UWUTILS_DYNAMIC_HPP
#define UWUTILS_DYNAMIC_HPP

#include "concepts.hpp"

namespace uwutils {

class Dynamic {
    void* _v = nullptr;
public:
    Dynamic() {}
    Dynamic(const Dynamic&) = delete;
    template<SelfAsignable _Tp>
    Dynamic(const _Tp& v) requires CopyAble<_Tp> {
        _v = new _Tp(v);
    }

    template<SelfAsignable _Tp>
    Dynamic& operator=(const _Tp& v) requires CopyAble<_Tp> {
        clear();
        _v = new _Tp(v);
        return *this;
    }

    void* _data() { return _v; }

    template<typename _Tp>
    _Tp& as() const {
        return *(_Tp*)_v;
    }

    template<typename _Tp>
    Dynamic& set(const _Tp& v) {
        clear();
        _v = new _Tp(v);
        return *this;
    }

    template<typename _Tp>
    Dynamic& clear() {
        if(_v != nullptr) {
            delete (_Tp*)_v;
            _v = nullptr;
        }
        return *this;
    }

    Dynamic& clear() {
        if(_v != nullptr) {
            delete _v;
            _v = nullptr;
        }
        return *this;
    }

    ~Dynamic() {
        clear();
    }

    bool null() const { return _v == nullptr; }
};

}

#endif
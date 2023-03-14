#ifndef UWUTILS_DYNAMIC_HPP
#define UWUTILS_DYNAMIC_HPP

#include "concepts.hpp"
#include <memory>

namespace uwutils {

class Dynamic {
    void* _v = nullptr;
    unsigned long long _size = sizeof(char);
public:
    Dynamic() {}
    Dynamic(const Dynamic& v) {
        clear();
        _v = v._v;
    }
    template<Not<Dynamic> _Tp>
    Dynamic(const _Tp& v) requires SelfAsignable<_Tp> && CopyAble<_Tp> {
        _v = new _Tp(v);
        _size = sizeof(_Tp);
    }

    Dynamic& operator=(const Dynamic& v)  {
        clear();
        _v = v._v;
        return *this;
    }

    template<Not<Dynamic> _Tp>
    Dynamic& operator=(const _Tp& v) requires SelfAsignable<_Tp> && CopyAble<_Tp> {
        clear();
        _v = new _Tp(v);
        _size = sizeof(_Tp);
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
        _size = sizeof(_Tp);
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

    template<typename _Tp>
    _Tp copy() const {
        return _Tp(*(_Tp*)_v);
    }

    ~Dynamic() {
        clear();
    }

    bool null() const { return _v == nullptr; }
};

}

#endif
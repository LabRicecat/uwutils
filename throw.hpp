#ifndef UWUTILS_THROW_HPP
#define UWUTILS_THROW_HPP

#include <exception>

namespace uwutils {

class BaseException : public std::exception {};

class MessageException : public BaseException {
protected:
    const char* _msg;
public:
    MessageException(const char* msg) {
        _msg = msg;
    }

    virtual const char* what() const noexcept override {
        return _msg;
    }
};

template<typename _Tinfo>
class DataException : public BaseException {
public:
    _Tinfo data;

    DataException(const _Tinfo& _data) {
        data = _data;
    }
};

}

#endif
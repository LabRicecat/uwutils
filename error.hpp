#ifndef UWUTILS_ERROR_HPP
#define UWUTILS_ERROR_HPP

#include "concepts.hpp"
#include "throw.hpp"
#include "box.hpp"

namespace uwutils {

template<ErrorEnum _Terr>
class ErrorExecption : public DataException<_Terr>, public MessageException {
public:
    ErrorExecption(_Terr err, const char* msg) 
    :MessageException(msg), DataException<_Terr>(err) {}
};

template<typename _Tp, ErrorEnum _Terr>
class Error {
    Box<_Tp> val;
    mutable _Terr err;
public:
    Error(_Tp& val) {
        this->val = val;
        err = _Terr::OK;
    }
    Error(_Terr err) {
        this->err = err;
    }
    bool ok() const {
        return err == _Terr::OK;
    }
    _Tp expect(const char* msg) {
        if(!ok())
            throw ErrorExecption(err, msg);
        return val;
    }

    _Tp& unwrap() { return val; }

    operator _Terr() const {
        return err;
    }
};

enum class Status { OK, ERR };

}

#endif
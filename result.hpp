#ifndef UWUTILS_RESULT_HPP
#define UWUTILS_RESULT_HPP

#include <algorithm>

#include "error.hpp"
#include "box.hpp"

namespace uwutils {

template<typename _Tp>
class Result {
    Box<_Tp> val;
    bool unset = true;
public:
    const static Result<_Tp> fail;
    
    Result() {}
    Result(const _Tp& v) { 
        val = v; 
        unset = false; 
    }

    Error<_Tp,Status> unwrap() {
        if(unset)
            return Status::ERR;
        return val.unwrap();
    }
    _Tp get_or(const _Tp& v) {
        if(unset) return v;
        return val;
    }
};

}

#endif
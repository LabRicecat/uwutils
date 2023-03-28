#ifndef UWUTILS_INTERFACE_HPP
#define UWUTILS_INTERFACE_HPP

#include "concepts.hpp"

namespace uwutils {

template<typename _Tp>
class IContainer {
public:
    virtual const _Tp& view() const = 0;
};

template<typename _Tp>
class IMutContainer : public IContainer<_Tp> {
public:
    //template<Not<IMutContainer<_Tp>> _Tpr>
    //IMutContainer(const _Tpr&) requires Not<_Tp,_Tpr> && AssignAble_w<_Tp,_Tpr>;
    template<Not<_Tp> _Tpr>
    IMutContainer& operator=(const _Tpr&) requires AssignAble_w<_Tp,_Tpr>;

    virtual _Tp& unwrap() = 0;

    virtual operator _Tp&() = 0;
    virtual operator const _Tp() const = 0;
};

}

#endif
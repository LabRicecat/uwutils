#ifndef UWUTILS_CONCEPTS_HPP
#define UWUTILS_CONCEPTS_HPP

#include <concepts>
#include <typeinfo>

#define uwunsafe

namespace uwutils {

template<typename _Tp>
concept Enum = std::is_enum<_Tp>::value;

template<typename _Tp> 
concept ErrorEnum = requires { 
    std::is_enum<_Tp>::value; 
    _Tp::OK == _Tp::OK && _Tp::OK == (_Tp)0; 
    _Tp() == _Tp::OK;
    _Tp(_Tp::OK) == _Tp::OK;
};

template<typename _Tp>
concept SelfAsignable = requires(_Tp t) {
    t = t;
};

template<typename _Tp,typename _Tpr>
concept AssignAble_w = requires(_Tp t, _Tpr tr) {
    t = tr;
};

template<typename _Tp, typename _Tpr>
concept ConvertableTo = requires(_Tp t) {
    static_cast<_Tpr>(t);
};

template<typename _Tp>
concept CopyAble = requires(_Tp t) {
    _Tp(t);
};

template<typename _Tp, typename _Tpr>
concept ThisType = std::is_same<_Tp,_Tpr>::value;

template<typename _Tp, typename _Tpr>
concept Not = std::negation<std::is_same<_Tp,_Tpr>>::value && std::negation<std::is_base_of<_Tp,_Tpr>>::value;

template<typename _Tpr, typename _Tp1, typename _Tp2>
concept EitherType = requires {
    typeid(_Tpr) == typeid(_Tp1) || typeid(_Tpr) == typeid(_Tp2);
};

template<typename _Tp>
concept Eq = requires(_Tp t) {
    (t == t) == true;
    (t != t) == false;
};
template<typename _Tp>
concept Ord = requires(_Tp t) {
    t > t;
    t < t;
    t == t;
    t >= t;
    t <= t;
    t != t;
};
template<typename _Tp, typename _Tpr>
concept Eq_w = requires(_Tp t, _Tpr tr) {
    (t == tr);
    (t != tr);
    (tr == t);
    (tr != t);
};
template<typename _Tp, typename _Tpr>
concept Ord_w = requires(_Tp t, _Tpr tr) {
    t > tr;
    t < tr;
    t == tr;
    t >= tr;
    t <= tr;
    t != tr;
    tr > t;
    tr < t;
    tr == t;
    tr >= t;
    tr <= t;
    tr != t;
};

template<typename _Tp>
concept CallAble = requires(_Tp t) {
    t();
};

template<typename _Tp, typename ..._Tpr>
concept CallAble_w = requires(_Tp t, _Tpr... r) {
    t(r...);
};

template<typename _Tp, typename _Tpr, typename ..._Tpl>
concept CallAble_wt = requires(_Tp t, _Tpl... r) {
    { t(r...) } -> std::convertible_to<const _Tpr>;
};

template<typename _Tp>
concept IteratAble = requires(_Tp t, int n) {
    t.begin() + n;
    t.end() + n;
};

template<typename _Tp>
concept IndexAble = requires(_Tp t, int n) {
    t[n];
};

template<typename _Tp>
concept EraseAble = requires(_Tp t, int n) {
    t.erase(t.begin() + n);
    t.erase(t.end() - n);
};

template<typename _Tp>
using ElementOf = std::remove_reference_t<decltype(_Tp()[0])>;

}

#endif
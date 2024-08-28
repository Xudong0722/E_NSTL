/*
 * @Author: Xudong0722 
 * @Date: 2024-08-14 21:05:55 
 * @Last Modified by: Xudong0722
 * @Last Modified time: 2024-08-28 17:22:56
 */
#pragma once 

#include <type_traits>

namespace ENSTL{

template<class T, T v>
struct e_integral_constant{
    static constexpr T value = v;
};

template<bool b>
using e_bool_constant = e_integral_constant<bool, b>;

typedef e_bool_constant<true> e_true_type;
typedef e_bool_constant<false> e_false_type;

template<class T1, class T2>
struct pair{};

template<class T>
struct is_pair : e_false_type{};

template<class T1, class T2>
struct is_pair<pair<T1, T2>> : e_true_type{};

//Remove reference
template<class T>
struct remove_reference{
    using type = T;
};

template<class T>
struct remove_reference<T&>{
    using type = T;
};

template<class T>
struct remove_reference<T&&>{
    using type = T;
};

#ifdef ENSTL_CPP14 //TODO
template<class Tp>
using remove_reference_t = remove_reference<Tp>::type;
#endif

} // namespace ENSTL
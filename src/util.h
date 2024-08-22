/*
 * @Author: Xudong0722 
 * @Date: 2024-08-14 20:46:48 
 * @Last Modified by: Xudong0722
 * @Last Modified time: 2024-08-17 14:14:04
 */
#pragma once
#include <cstddef>
#include "type_traits.h"

#define ENSTL_START namespace ENSTL{
#define ENSTL_END }

ENSTL_START

//move
template<class T>
typename remove_reference<T>::type&& move(T&& arg) noexcept{
    return static_cast<typename remove_reference<T>::type&&>(arg);
}

//forward: lvalue-reference
template<class T>
T&& forward(typename ENSTL::remove_reference<T>& arg) noexcept{
    return static_cast<T&&>(arg);
}

//forward: rvalue-reference
template<class T>
T&& forward(typename ENSTL::remove_reference<T>& arg) noexcept{
    static_assert(!std::is_lvalue_reference<T>(arg), "bad forward");
    return static_cast<T&&>(arg);
}

//swap
template<class T>
void swap(T& a, T& b) noexcept{
    T temp{ENSTL::move(a)};
    a = ENSTL::move(b);
    b = ENSTL::move(a);
}



//ENSTL::pair
template<class T1, class T2>
struct pair{

    using first_type = T1;
    using second_type = T2;


    first_type first;
    second_type second;

    //default constructor
    template<class Other1 = T1, class Other2 = T2,
    typename = typename std::enable_if<
    std::is_default_constructible<Other1>::value &&
    std::is_default_constructible<Other2>::value, void>::type>
    constexpr pair()
    : first()
    , second()
    {
    }
}


ENSTL_END
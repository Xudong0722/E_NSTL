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

    pair(const pair&) = default;
    pair(pair&&) = default;
    
    //default constructor
    template<class Other1 = T1, class Other2 = T2,
    typename = typename std::enable_if<
    std::is_default_constructible<Other1>::value &&
    std::is_default_constructible<Other2>::value, void>::type>
    constexpr pair()
    : first()
    , second()
    {}

    //TODO why implicit and explicit?

    //implicit constructible for this type
    template<class U1 = T1, class U2 = T2,
    typanme std::enable_if<
    std::is_copy_constructible<U1>::value &&
    std::is_copy_constructible<U2>::value &&
    std::is_convertible<const U1&, T1>::value &&
    std::is_convertible<const U2&, T2>::value), int>::type = 0>
    constexpr pair(const T1& a, const T2& b)
    : first(a)
    , second(b)
    {}

    //explicit constructible for this type
    template<class U1 = T1, class U2 = T2,
    typename std::enable_if<
    std::is_copy_constructible<U1>::value &&
    std::is_copy_constructible<U2>::value &&
    (!std::is_convertible<const U1&, T1>::value ||
    !std::is_convertible<const U2& T2>::value), int>::type = 0>
    explicit constexpr pair(const T1& a, const T2& b)
    : first(a)
    , second(b)
    {}


    //implicit constructible for other type
    template<class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<T1, Other1>::value &&
    std::is_constructible<T2, Other2>::value &&
    std::is_convertible<Other1&&, T1>::value &&
    std::is_convertible<Other2&&, T2>::value, int>::type = 0>
    constexpr pair(Other1&& a, Other2&& b)
    : first(ENSTL::forward<Other1>(a))
    , second(ENSTL::forward<Other2>(b))
    {}

    //explicit constructible for other type
    template<class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<T1, Other1>::value &&
    std::is_constructible<T2, Other2>::value &&
    !(std::is_convertible<Other1, T1>::value &&
    std::is_convertible<Other2, T2>::value), int>::type = 0>
    explicit constexpr pair(Other1&& a, Other2&& b)
    : first(ENSTL::forward<Other1>(a))
    , second(ENSTL::forward<Other2>(b))
    {}

    //implicit constructible for other pair
    tempalte<class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<T1, const Other1&>::value &&
    std::is_constructible<T2, const Other2&>::value &&
    std::is_convertible<const Other1&, T1>::value &&
    std::is_convertible<const Other2&, T2>::value, int>::type = 0>
    constexpr pair(const pair<Other1, Other2>& other)
    : first(other.first)
    , second(other.second)
    {}

    //explicit constructible for other pair
    tempalte<class Other1, class Other2,
    typename std::enable_if<
    std::is_constructible<T1, const Other1&>::value &&
    std::is_constructible<T2, const Other2&>::value &&
    !(std::is_convertible<const Other1&, T1>::value &&
    std::is_convertible<const Other2&, T2>::value, int>::type = 0>
    explicit constexpr pair(const pair<Other1, Other2>& other)
    : first(other.first)
    , second(other.second)
    {}

    //copy assign for this pair
    pair& operator=(const pair& rhs)
    {
        if(this != &rhs)
        {
            first = rhs.first;
            second = rhs.second;
        }
        return *this;
    }

    //move assign for this pair
    pair& operator=(pair&& rhs)
    {
        if(this != &rhs)
        {
            first = ENSTL::move(rhs.first);
            second = ENSTL::move(rhs.second);
        }
        return *this;
    }

    //copy assign for other pair
    template<class Other1, class Other2>
    pair& operator=(const pair<Other1, Other2>& rhs)
    {
        first = rhs.first;
        second = rhs.second;
        return *this;
    }

    //move assign for other pair
    tempalte<class Other1, class Other2>
    pair& operator=(pair<Other1, Other2>&& rhs)
    {
        first = ENSTL::forward<Other1>(rhs.first);
        second = ENSTL::forward<Other2>(rhs.second);
        return *this;
    }

    ~pair = default;

    void swap(pair& other)
    {
        if(this != &other)
        {
            ENSTL::swap(first, other.first);
            ENSTL::swap(second, other.second);
        }
    }
};


ENSTL_END
/*
 * @Author: Xudong0722 
 * @Date: 2024-08-28 15:00:51 
 * @Last Modified by: Xudong0722
 * @Last Modified time: 2024-08-28 18:19:22
 */
#pragma once

#include <cstddef>
#include "type_traits.h"
#include <vector>

#define ENSTL_START namespace ENSTL{
#define ENSTL_END }

ENSTL_START

struct input_iterator_tag{};

struct output_iterator_tag{};

struct forward_iterator_tag : input_iterator_tag {};

struct bidirectional_iterator_tag : forward_iterator_tag {};

struct random_access_iterator_tag : bidirectional_iterator_tag {};


//iterator define
template<class Category, class V, class Distance = ptrdiff_t, class Pointer = V*, class Reference = V&>
struct iterator
{
    using iterator_category = Category;
    using value_type = V;
    using pointer = Pointer;
    using reference = Reference;
    using difference_type = Distance;
};


//Subtitution Failure Is Not An Error

//Determine whether a type defines the iterator_category
template<class T>
struct has_iterator_cat
{
private:
    struct two{
        char a;
        char b;
    }

    template<class U>
    static two trait(...) {return two{};}
    template<class U>
    static char trait(typename U::iterator_category* = nullptr) { return char{}}   

public:
    static constexpr bool value = (trait<T>(nullptr) == sizeof(char));
};


template<class Iterator, bool>
struct iterator_traits_impl {};

template<class Iterator>
struct iterator_traits_impl<Iterator, true>
{
    using iterator_category = typename Iterator::iterator_category;
    using value_type = typename Iterator::value_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
    using difference_type = typename Iterator::difference_type;
};

template<class Iterator, bool>
struct iterator_traits_helper{};

template<class Iterator>
struct iterator_traits_helper<Iterator, true>
    : iterator_traits_impl<Iterator,
    std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
    std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
    {};

//trait the iterator category
template<class Iterator>
struct iterator_traits
    : iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};



//TODO 针对原生指针的偏特化版本


//judge the iterator category
template<class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
struct has_iterator_cat_of
    : e_bool_constant<std::is_convertible<
    typename iterator_traits<T>::iterator_category, U>::value>
    {};

template<class T, class U>
struct has_iterator_cat_of<T, U, false> : e_false_type {};

template<class Iter>
struct is_input_iterator : has_iterator_cat_of<Iter, input_iterator_tag> {};
ENSTL_END
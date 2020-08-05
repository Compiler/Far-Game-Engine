#pragma once
#include <iostream>
#include <type_traits>
#include <tuple>

namespace far{


    ////NOT DONE////


    //this is the thing that does the stuff. all the shit below just makes it work.
    template<typename... Types>
    struct Typelist{
        static const size_t size{sizeof...(Types)};
    };

    //just a type wrapper. needed for classes that can be instantiated
    template<typename T>
    struct FType{
        using type = T;
    };

    //// TYPE RENAMER ////

    template <template<typename...> class N, typename T>
    struct renamer;

    template<template<typename...>class N, template<typename...>class O, typename... Types>
    struct renamer<N, O<Types...>>
    {
        using type = N<Types...>;
    };

    template<template<typename...>class N, typename T>
    using Rename = typename renamer<N, T>::type;

    //// Merger ////

    //recursive base case no list
    template<typename...>
    struct unroller{
        using type = TypeList<>;
    };

    template<typename... TList>
    using Merge = typename unroller<TList...>::type;

    //recursive base case 1 list
    template<typename... Types>
    struct unroller<TypeList<Types...>>{
        using type = TypeList<Types...>;
    };

    //template recursion
    template<typename... t1,typename... t2,typename... t_cont>
    struct unroller<TypeList<t1...>, TypeList<t2...>, t_cont...>{
        using type = Merge<TypeList<t1...,t2...>,t_cont...>;
    };

    //// Merge Mapper ////

    template<template<typename>class Tmpl, typename>
    struct Cartographer{
        using type = TypeList<>;
    };

    template<template<typename>class Tmpl, typename TList>
    using Map = typename Cartographer<Tmpl,TList>::type;

    template<template<typename>class Tmpl, typename T, typename TList>
    struct Cartographer<Tmpl, TypeList<T, TList...>>{
        using type = Merge<TypeList<Tmpl<T>>, Map<Tmpl, TypeList<TList...>>>;
    };


    template<typename TList>
    using tuple = Rename<std::tuple, TList>;

    template<typename TList>
    using t_tuple = Tuple<Map<FType, TList>>;

    template<size_t index, typename TList>
    using Nth = std::tuple_element_t<index, Tuple<TList>>;

    template<typename TList, typename T>
    using PushBack_T = Merge<TList, TypeList<T>>;

    //incase u wanna put them in a certain order
    template<typename TList, typename T>
    using PushFront_T = Merge<TypeList<T>,TList>;

    template<typename TList>
    constexpr auto size() noexcept{
        return TList::size;
    }



}
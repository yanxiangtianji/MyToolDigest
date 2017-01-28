#pragma once
#include <type_traits>
#include <tuple>

template <class T, class = void>
struct is_tuple :public std::false_type {};

template<class T>
struct is_tuple<T, typename std::enable_if<std::tuple_size<T>::value != 0>::type> :
	public std::true_type {};

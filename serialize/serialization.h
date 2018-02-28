#pragma once
#include <cstdint>
#include "serialize_general.hpp"
#include "tuple3_ps.h"

/*
Two ways to support customize type:
1, (recommanded) add partial specialization struct for _Serializer.
	Put it in a separated .hpp file and include it here.
	A reference can be found at "serializer_basic.hpp" and you should include it.
2, (using existing functions) use existing methods together with partial specialization functions.
	Put existing methods' declarations in a .h file and include it here.
	Then write parial specilization version for estimateSize, serial, deserial functions in this header file.
	The partial spec. versions should directly call the existing function.
	A reference can be found in Part III.
*/

/***********************************
	Part I, single item
************************************/

/*
Give an upper bound for about number of bytes needed to serialize the item
*/
template <class T>
inline int estimateSize(const T& item);

/*
Serialize an item of type T into a buffer with given size, if the size is large enough.
Input: pointer to the buffer $res$, buffer size: $bufSize$, item to serialize: $item$
Output:
If the buffer is large enough for $item$, return the pointer one over the end of the used buffer.
Otherwise, return nullptr.
*/
template <class T>
inline char* serialize(char* res, int bufSize, const T& item);

/*
Serialize an item of type T into a buffer without checking size.
Input: pointer to the buffer $res$, buffer size: $bufSize$, item to serialize: $item$
Output: the pointer one over the end of the used buffer.
*/
template <class T>
inline char* serialize(char* res, const T& item);

/*
Serialize an item to a string
*/
template <class T>
inline std::string serialize(const T& item);

/*
Deserialize an item of type T from a buffer.
Input: pointer to the buffer $p$
Output: the item and a point one byte over last byte of the item in the buffer
*/
template <class T>
inline std::pair<T, const char*> deserialize(const char* p);

/*
Deserialize an item of type T from a string
*/
template <class T>
inline T deserialize(const std::string& str);


/***********************************
Part II, serialize container using iterator
************************************/


template <class Cont>
inline std::pair<char*, typename Cont::const_iterator> serializeCont(char* res, int bufSize,
	typename Cont::const_iterator first, typename Cont::const_iterator last);

template <class Cont>
inline std::pair<char*, typename Cont::const_iterator> serializeCont(char* res,
	typename Cont::const_iterator first, typename Cont::const_iterator last);

template <class Cont>
inline std::string serializeCont(typename Cont::const_iterator first, typename Cont::const_iterator last);

/***********************************
Part III, partial specialaizations
************************************/

// for customize type AAA
//template<>
//char* serialize<AAA>(char* res, int bufSize, const AAA& item) {
//	return serialize_function_for_AAA(res, bufSize, item);
//}
//
//template<>
//char* serialize(char* res, const AAA& item) {
//	return serialize_function_for_AAA(res, item);
//}
//
//template <>
//inline std::pair<AAA, const char*> deserialize<AAA>(const char* p) {
//	return deserialize_function_for_AAA(p);
//}


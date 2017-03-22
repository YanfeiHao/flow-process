#pragma once

struct true_type { static constexpr bool value = true; };
struct false_type { static constexpr bool value = false; };

/// determines if a type is const
template <typename T> struct IsConst : false_type { };
template <typename T> struct IsConst<const T> : true_type { };

/// determines if it is a R value
template <class T> struct IsRvalueReference : false_type { };
template <class T> struct IsRvalueReference<T&&> : true_type { };

/// determines if it is a L value
template <class T> struct IsLvalueReference : false_type { };
template <class T> struct IsLvalueReference<T&> : true_type { };

/// returns reference removed type
template< class T > struct RemoveReference      {typedef T type;};
template< class T > struct RemoveReference<T&>  {typedef T type;};
template< class T > struct RemoveReference<T&&> {typedef T type;};

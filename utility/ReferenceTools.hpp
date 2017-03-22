#pragma once
#include "utility/typeTrait.hpp"

namespace utility {

template<typename T>
constexpr typename RemoveReference<T>::type&& move (T& param) noexcept
{
    static_assert (!IsConst<T>::value, "cannot apply move to const values");

    using return_type = typename RemoveReference<T>::type;
    return static_cast<return_type&&> (param);
}

template<typename T>
constexpr typename RemoveReference<T&&>::type&& move (T&& param) noexcept
{
    static_assert (IsRvalueReference<T>::value, "r-value is not neccisary");

    using return_type = typename RemoveReference<T>::type;
    return static_cast<return_type&&> (param);
}

template<typename T>
constexpr T&& forward(typename RemoveReference<T>::type& __t) noexcept
{
    return static_cast<T&&>(__t);
}

template<typename T>
constexpr T&& forward(typename RemoveReference<T>::type&& __t) noexcept
{
    static_assert(!IsLvalueReference<T>::value, " substituting _Tp is an lvalue reference type");
    return static_cast<T&&>(__t);
}

}

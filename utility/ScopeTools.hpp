#pragma once
#include "utility/ReferenceTools.hpp"

namespace utility {

namespace detail {
enum class __ScopeGuardOnExit__ {};


template<typename Callable>
struct __ScopeGuard__
{
    Callable c_;
    __ScopeGuard__ (Callable&& c) : c_ (forward<Callable> (c)) {}
    ~__ScopeGuard__ ()
    {
        c_ ();
    }
};

template<typename fun>
__ScopeGuard__<fun> operator + (__ScopeGuardOnExit__, fun&& fn)
{
    return __ScopeGuard__<fun> (forward<fun> (fn));
}

} /// namespace detail
} /// namespace utility

#define __CONCAT_IMPL__(str1,str2) str1##str2
#define CONCAT(str1,str2) __CONCAT_IMPL__(str1,str2)

#define __ANONYMOUS_VAR__(str) CONCAT(str,__LINE__)

/// 注册作用域退出时的代码 例如
/// {
///     auto fp = fopen ("123.txt", "ab+");
///     SCOPE_EXIT { fclose (fp); };
///     ....
///     // fclose会被自动在退出作用域调用
/// }
#define SCOPE_EXIT \
    auto __ANONYMOUS_VAR__(HELPER_SCOPE_EXIT_STATE) \
    = ::utility::detail::__ScopeGuardOnExit__ () + [&]()

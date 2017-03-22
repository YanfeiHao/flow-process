#pragma once
#include <utility/ReferenceTools.hpp>
#include <memory>


template<typename T>
struct DefaultDeleter
{
    void operator () (T* ptr) { delete ptr; }
};

template<typename T>
struct DefaultDeleter<T[]>
{
    void operator () (T* ptr) { delete [] ptr; }
};

template <typename ValueType, typename DeleterType = DefaultDeleter<ValueType>>
class UniquePtr
{
    using PtrType = ValueType*;
public:
    constexpr UniquePtr () noexcept : ptr_ (nullptr){ }
    explicit UniquePtr (PtrType p) noexcept : ptr_ (p) { }

    template<typename ... Args>
    static UniquePtr make (Args && ... args)
    {
        return UniquePtr (new ValueType (forward<Args> (args)...));
    }

    UniquePtr (const UniquePtr&) = delete;
    void operator () (const UniquePtr & )  = delete;

    UniquePtr (UniquePtr && that) : ptr_ (that.ptr_) { that.ptr_ = nullptr; }
    void operator= (UniquePtr && that) noexcept { ptr_ = that.ptr_; that.ptr_ = nullptr; }

    ~UniquePtr () { if (ptr_.value != nullptr) { ptr_ (ptr_.value); } }

    PtrType get () const noexcept { return ptr_.value; }
    PtrType release () noexcept { auto tmp = ptr_.value; ptr_ = nullptr; return tmp; }
    void reset (PtrType p) noexcept { ptr_ = p; }

    explicit operator bool () noexcept { return ptr_ != nullptr; }
    PtrType operator * () const noexcept { return *ptr_.value; }
    PtrType operator -> () const noexcept { return *ptr_.value; }
private:
    struct ImplUniquePtr : DeleterType
    {
        constexpr ImplUniquePtr (PtrType v) : value (v) { }
        constexpr operator PtrType () { return value; }
        PtrType value;
    };

private:
    ImplUniquePtr ptr_;
};

template <typename ValueType, typename DeleterType>
class UniquePtr<ValueType[], DeleterType>
{
    using PtrType = ValueType*;
public:
    constexpr UniquePtr () noexcept : ptr_ (nullptr){ }
    explicit UniquePtr (PtrType p) noexcept : ptr_ (p) { }
    static UniquePtr make (size_t size)
    {
        return UniquePtr (new ValueType[size]);
    }

    UniquePtr (const UniquePtr&) = delete;
    void operator () (const UniquePtr & )  = delete;

    UniquePtr (UniquePtr && that) noexcept : ptr_ (that.ptr_){ that.ptr_ = nullptr; }
    void operator= (UniquePtr && that) noexcept { ptr_ = that.ptr_; that.ptr_ = nullptr; }

    ~UniquePtr () { if (ptr_.value != nullptr) { ptr_ (ptr_.value); } }

    PtrType get () const noexcept { return ptr_.value; }
    PtrType release () noexcept { auto tmp = ptr_.value; ptr_ = nullptr; return tmp; }
    void reset (PtrType p) noexcept { ptr_ = p; }

    explicit operator bool () noexcept { return ptr_ != nullptr; }
    ValueType & operator [] (size_t i) const noexcept { return get () [i]; }
private:
    struct ImplUniquePtr : DeleterType
    {
        constexpr ImplUniquePtr (PtrType v) : value (v) { }
        constexpr operator PtrType () { return value; }
        PtrType value;
    };
private:
    ImplUniquePtr ptr_;
};

template <typename T, typename ... Args>
decltype (auto) makeUnique (Args && ... args)
{
    return UniquePtr<T>::make (forward<Args> (args)...);
}

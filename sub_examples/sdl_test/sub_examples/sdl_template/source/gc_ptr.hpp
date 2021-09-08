#ifndef GC_SDL_BASICS_GC_PTR_HPP
#define GC_SDL_BASICS_GC_PTR_HPP

namespace core
{
template <typename T>
class gc_ptr final
{
	T* ptr = nullptr;

public:
	gc_ptr() noexcept
		: ptr(nullptr)
	{
	}
	explicit gc_ptr(T& in) noexcept
		: ptr(&in)
	{
	}
	gc_ptr(T* in) noexcept
		: ptr(in)
	{
	}
	gc_ptr(decltype(nullptr)) noexcept
		: ptr(nullptr)
	{
	}
	explicit gc_ptr(gc_ptr<T> const& other) noexcept
		: ptr(other.ptr)
	{
	}
	explicit gc_ptr(gc_ptr<T>&& other) noexcept
		: ptr(other.ptr)
	{
		other.ptr = nullptr;
	}

	T& operator*() noexcept
	{
		return *ptr;
	}
	T const& operator*() const noexcept
	{
		return *ptr;
	}
	gc_ptr<T>& operator=(gc_ptr<T> const& other) noexcept
	{
		ptr = other.ptr;
		return *this;
	}
	gc_ptr<T>& operator=(gc_ptr<T>&& other) noexcept
	{
		ptr = other.ptr;
		other.ptr = nullptr;
		return *this;
	}
	gc_ptr<T>& operator=(decltype(nullptr)) noexcept
	{
		ptr = nullptr;
		return *this;
	}
	T* operator->() noexcept
	{
		return ptr;
	}
	T const* operator->() const noexcept
	{
		return ptr;
	}
	bool operator!=(gc_ptr<T> const& other) const noexcept
	{
		return other.ptr != ptr;
	}
	bool operator!=(decltype(nullptr)) const noexcept
	{
		return nullptr != ptr;
	}
	friend bool operator!=(decltype(nullptr), gc_ptr<T> const& other) noexcept
	{
		return nullptr != other.ptr;
	}

	bool is_null() const noexcept
	{
		return nullptr != ptr;
	}
	T* data() noexcept
	{
		return ptr;
	}
	T const* data() const noexcept
	{
		return ptr;
	}
};
} // namespace core

#endif // GC_SDL_BASICS_GC_PTR_HPP

#pragma once 
#include <stdexcept>
#include <utility>

template <class T>
class polymorphic_ptr
{
public:
	polymorphic_ptr() = default;
	polymorphic_ptr(T* ptr);

	polymorphic_ptr(const polymorphic_ptr<T>& other);
	polymorphic_ptr(polymorphic_ptr<T>&& other) noexcept;

	polymorphic_ptr<T>& operator=(const polymorphic_ptr<T>& other);
	polymorphic_ptr<T>& operator=(polymorphic_ptr<T>&& other) noexcept;

	~polymorphic_ptr();

	T* operator->();
	const T* operator->() const;

	T& operator*();
	const T& operator*() const;

	operator bool() const;
	void reset(T* ptr);

	T* get();
	const T* get() const;

private:
	T* m_Ptr = nullptr;

	void copyFrom(const polymorphic_ptr<T>& other);
	void moveFrom(polymorphic_ptr<T>&& other);
	void free();
};

template<class T>
inline void polymorphic_ptr<T>::copyFrom(const polymorphic_ptr<T>& other)
{
	m_Ptr = other.m_Ptr->clone();
}

template<class T>
inline void polymorphic_ptr<T>::moveFrom(polymorphic_ptr<T>&& other)
{
	m_Ptr = other.m_Ptr;
	other.m_Ptr = nullptr;
}

template<class T>
inline void polymorphic_ptr<T>::free()
{
	delete m_Ptr;
}

template<class T>
inline polymorphic_ptr<T>::polymorphic_ptr(T* ptr) : m_Ptr(ptr)
{
}

template<class T>
inline polymorphic_ptr<T>::polymorphic_ptr(const polymorphic_ptr<T>& other)
{
	copyFrom(other);
}

template<class T>
inline polymorphic_ptr<T>::polymorphic_ptr(polymorphic_ptr<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class T>
inline polymorphic_ptr<T>& polymorphic_ptr<T>::operator=(const polymorphic_ptr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
inline polymorphic_ptr<T>& polymorphic_ptr<T>::operator=(polymorphic_ptr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T>
inline polymorphic_ptr<T>::~polymorphic_ptr()
{
	free();
}

template<class T>
inline T* polymorphic_ptr<T>::operator->()
{
	return m_Ptr;
}

template<class T>
inline const T* polymorphic_ptr<T>::operator->() const
{
	return m_Ptr;
}

template<class T>
inline T& polymorphic_ptr<T>::operator*()
{
	if (!m_Ptr)
	{
		throw std::invalid_argument("Nullptr");
	}
	return *m_Ptr;
}

template<class T>
inline const T& polymorphic_ptr<T>::operator*() const
{
	if (!m_Ptr)
	{
		throw std::invalid_argument("Nullptr");
	}
	return *m_Ptr;
}

template<class T>
inline polymorphic_ptr<T>::operator bool() const
{
	return m_Ptr != nullptr;
}

template<class T>
inline void polymorphic_ptr<T>::reset(T* ptr)
{
	if (m_Ptr != ptr)
	{
		free();
		m_Ptr = ptr;
	}
}

template<class T>
inline T* polymorphic_ptr<T>::get()
{
	return m_Ptr;
}

template<class T>
inline const T* polymorphic_ptr<T>::get() const
{
	return m_Ptr;
}

template <class T, class... Args>
inline T* make_polymorphic(Args&&... args)
{
	return new T(std::forward<Args>(args)...);
}
#pragma once
#include "polymorphic_ptr.hpp"
//----------------------------
#include <vector>

template<typename T>
class polymorphic_ctr 
{
public:
	void emplace_back(polymorphic_ptr<T>&& ptr);
	void push_back(const polymorphic_ptr<T>& ptr);
	void removeAt(size_t index);
	void pop_back();

	polymorphic_ptr<T>& operator[] (size_t index);
	const polymorphic_ptr<T>& operator[] (size_t index) const;

	using iterator = typename std::vector<polymorphic_ptr<T>>::iterator;
	using const_iterator = typename std::vector<polymorphic_ptr<T>>::const_iterator;
	using reverse_iterator = typename std::vector<polymorphic_ptr<T>>::reverse_iterator;
	using const_reverse_iterator = typename std::vector<polymorphic_ptr<T>>::const_reverse_iterator;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	size_t size() const;

private:
	std::vector<polymorphic_ptr<T>> m_Ptrs;
};

template<typename T>
inline size_t polymorphic_ctr<T>::size() const
{
	return m_Ptrs.size();
}

template<typename T>
inline void polymorphic_ctr<T>::emplace_back(polymorphic_ptr<T>&& ptr)
{
	m_Ptrs.emplace_back(ptr);
}

template<typename T>
inline void polymorphic_ctr<T>::push_back(const polymorphic_ptr<T>& ptr)
{
	m_Ptrs.emplace_back(ptr);
}

template<typename T>
inline void polymorphic_ctr<T>::pop_back()
{
	m_Ptrs.pop_back();
}

template<typename T>
inline void polymorphic_ctr<T>::removeAt(size_t index)
{
	std::swap(m_Ptrs[index], m_Ptrs[m_Ptrs.size() - 1]);

	m_Ptrs.pop_back();
}

template<typename T>
inline polymorphic_ptr<T>& polymorphic_ctr<T>::operator[](size_t index)
{
	return m_Ptrs[index];
}

template<typename T>
inline const polymorphic_ptr<T>& polymorphic_ctr<T>::operator[](size_t index) const
{
	return m_Ptrs[index];
}

template<typename T>
inline typename std::vector<polymorphic_ptr<T>>::iterator polymorphic_ctr<T>::begin()
{
	return m_Ptrs.begin();
}

template<typename T>
inline typename std::vector<polymorphic_ptr<T>>::iterator polymorphic_ctr<T>::end()
{
	return m_Ptrs.end();
}

template<typename T>
inline typename std::vector<polymorphic_ptr<T>>::const_iterator polymorphic_ctr<T>::begin() const
{
	return m_Ptrs.cbegin();
}

template<typename T>
inline typename std::vector<polymorphic_ptr<T>>::const_iterator polymorphic_ctr<T>::end() const
{
	return m_Ptrs.cend();
}

template<typename T>
inline typename polymorphic_ctr<T>::reverse_iterator polymorphic_ctr<T>::rbegin()
{
	return m_Ptrs.rbegin();
}

template<typename T>
inline typename polymorphic_ctr<T>::reverse_iterator polymorphic_ctr<T>::rend()
{
	return m_Ptrs.rend();
}

template<typename T>
inline typename polymorphic_ctr<T>::const_reverse_iterator polymorphic_ctr<T>::crbegin() const
{
	return m_Ptrs.crbegin();
}

template<typename T>
inline typename polymorphic_ctr<T>::const_reverse_iterator polymorphic_ctr<T>::crend() const
{
	return m_Ptrs.crend();
}
//==============================================================================
// ListBase.h
//==============================================================================
#ifndef GURAX_LISTBASE_H
#define GURAX_LISTBASE_H
#include "Common.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ListBase
//------------------------------------------------------------------------------
template<typename T> class ListBase {
public:
	using Container = std::vector<T>;
protected:
	Container _container;
public:
	using pointer = typename Container::pointer;
	using const_pointer = typename Container::const_pointer;
	using reference = typename Container::reference;
	using const_reference = typename Container::const_reference;
	using value_type = typename Container::value_type;
	using iterator = typename Container::iterator;
	using const_iterator = typename Container::const_iterator;
	using reverse_iterator = typename Container::reverse_iterator;
	using const_reverse_iterator = typename Container::const_reverse_iterator;
public:
	ListBase() {}
	ListBase(size_t n) : _container(n) {}
	ListBase(size_t n, T elem) : _container(n, elem) {}
	ListBase(const ListBase& src) : _container(src._container) {}
	ListBase(ListBase&& src) : _container(std::move(src._container)) {}
	ListBase(const_iterator first, const_iterator last) : _container(first, last) {}
	ListBase(std::initializer_list<T> initList) : _container(initList) {}
public:
	void operator=(const ListBase& src) { _container = src._container; }
	void operator=(ListBase&& src) { _container = std::move(src._container); }
public:
	reference operator[](size_t pos) { return _container[pos]; }
	const_reference operator[](size_t pos) const { return _container[pos]; }
	bool empty() const { return _container.empty(); }
	size_t capacity() const { return _container.capacity(); }
	size_t size() const { return _container.size(); }
	template<typename TT> TT sizeT() const { return static_cast<TT>(_container.size()); }
	void clear() { _container.clear(); }
	void reserve(size_t size) { _container.reserve(size); }
	operator const_pointer() const { return _container.data(); }
	const_pointer data() const { return _container.data(); }
	const_reference front() const { return _container.front(); }
	const_reference back() const { return _container.back(); }
	reference front() { return _container.front(); }
	reference back() { return _container.back(); }
	iterator begin() { return _container.begin(); }
	iterator end() { return _container.end(); }
	const_iterator begin() const { return _container.begin(); }
	const_iterator end() const { return _container.end(); }
	reverse_iterator rbegin() { return _container.rbegin(); }
	reverse_iterator rend() { return _container.rend(); }
	const_reverse_iterator rbegin() const { return _container.rbegin(); }
	const_reverse_iterator rend() const { return _container.rend(); }
	reference at(size_t pos) { return _container.at(pos); }
	const_reference at(size_t pos) const { return _container.at(pos); }
	void push_back(const_reference elem) { _container.push_back(elem); }
	void pop_back() { _container.pop_back(); }
	void insert(const_iterator pos, const_reference elem) { _container.insert(pos, elem); }
	void insert(const_iterator pos, const_iterator first, const_iterator last) { _container.insert(pos, first, last); }
	void erase(const_iterator pos) { _container.erase(pos); }
	void erase(const_iterator first, const_iterator last) { _container.erase(first, last); }
public:
	bool IsExist(const_reference elem) { return std::find(_container.begin(), _container.end(), elem) != _container.end(); }
public:
	template<typename T_LessThan, typename T_GreaterThan>
	void SortByOrder(SortOrder sortOrder) {
		if (sortOrder == SortOrder::Ascend) {
			std::sort(_container.begin(), _container.end(), T_LessThan());
		} else if (sortOrder == SortOrder::Descend) {
			std::sort(_container.begin(), _container.end(), T_GreaterThan());
		}
	}
	template<typename T_LessThan, typename T_GreaterThan>
	void StableSortByOrder(SortOrder sortOrder) {
		if (sortOrder == SortOrder::Ascend) {
			std::stable_sort(_container.begin(), _container.end(), T_LessThan());
		} else if (sortOrder == SortOrder::Descend) {
			std::stable_sort(_container.begin(), _container.end(), T_GreaterThan());
		}
	}
};

}

#endif

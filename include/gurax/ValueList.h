//==============================================================================
// ValueList.h
//==============================================================================
#ifndef GURAX_VALUELIST_H
#define GURAX_VALUELIST_H
#include "Value.h"

namespace Gurax {

class Random;

//------------------------------------------------------------------------------
// ValueList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueList {
public:
	using V = std::vector<Value*>;
	V v;
	using pointer = V::pointer;
	using const_pointer = V::const_pointer;
	using reference = V::reference;
	using const_reference = V::const_reference;
	using value_type = V::value_type;
	using iterator = V::iterator;
	using const_iterator = V::const_iterator;
	using reverse_iterator = V::reverse_iterator;
	using const_reverse_iterator = V::const_reverse_iterator;
	reference operator[](size_t pos) { return v[pos]; }
	const_reference operator[](size_t pos) const { return v[pos]; }
	bool empty() const { return v.empty(); }
	size_t size() const { return v.size(); }
	void clear() { v.clear(); }
	void reserve(size_t size) { v.reserve(size); }
	const_reference front() const { return v.front(); }
	const_reference back() const { return v.back(); }
	reference front() { return v.front(); }
	reference back() { return v.back(); }
	iterator begin() { return v.begin(); }
	iterator end() { return v.end(); }
	const_iterator begin() const { return v.begin(); }
	const_iterator end() const { return v.end(); }
	reverse_iterator rbegin() { return v.rbegin(); }
	reverse_iterator rend() { return v.rend(); }
	const_reverse_iterator rbegin() const { return v.rbegin(); }
	const_reverse_iterator rend() const { return v.rend(); }
	reference at(size_t pos) { return v.at(pos); }
	const_reference at(size_t pos) const { return v.at(pos); }
	void push_back(const_reference elem) { v.push_back(elem); }
	void pop_back() { v.pop_back(); }
	void insert(const_iterator pos, const_reference elem) { v.insert(pos, elem); }
	void insert(const_iterator pos, const_iterator first, const_iterator last) { v.insert(pos, first, last); }
	void erase(const_iterator pos) { v.erase(pos); }
	void erase(const_iterator first, const_iterator last) { v.erase(first, last); }
public:
	ValueList() {}
	ValueList(const_iterator first, const_iterator last) : v(first, last) {}
public:
	static const ValueList Empty;
public:
	ValueList& Sort(SortOrder sortOrder = SortOrder::Ascend);
	ValueList& Sort(Processor& processor, const Function& function);
	ValueList& StableSort(SortOrder sortOrder = SortOrder::Ascend);
	ValueList& StableSort(Processor& processor, const Function& function);
	ValueList& Shuffle(Random& random);
	VType& GetVTypeOfElems() const;
	void IncCntRefOfEach() const;
	bool CheckPosition(Int pos, Int posRaw) const;
	bool CheckPosition(Int pos) const { return CheckPosition(pos, pos); }
	bool FixPosition(Int* pPos) const;
	bool Contains(const Value& value) const;
	size_t Count(const Value& value) const;
	size_t CountFalse() const;
	size_t CountTrue() const;
	size_t CountIf(Processor& processor, const Function& function) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ValueList& valueList) const { return this == &valueList; }
	bool IsEqualTo(const ValueList& valueList) const { return IsIdentical(valueList); }
	bool IsLessThan(const ValueList& valueList) const { return this < &valueList; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	void IssueError_IndexOutOfRange(Int pos) const;
	void IssueError_IndexOutOfRange(const char* pos) const;
};

}

#endif

//==============================================================================
// ValueDict.h
//==============================================================================
#ifndef GURAX_VALUEDICT_H
#define GURAX_VALUEDICT_H
#include "ValueOwner.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueDict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueDict :
	public std::unordered_map<Value*, Value*, Value::Hash, Value::EqualTo>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueDict);
public:
	enum StoreMode { None, Strict, Overwrite, Timid, };
protected:
	~ValueDict() { Clear(); }
public:
	void Clear();
	ValueDict* Clone() const;
	ValueDict* CloneDeep() const;
	void Assign(Value* pValueKey, Value* pValue);
	bool Store(const ValueDict& valDict, StoreMode storeMode);
	bool Store(const Value& valueKey, const Value& value, StoreMode storeMode);
	const Value* Lookup(const Value& valueKey) const {
		auto pPair = find(const_cast<Value*>(&valueKey));
		return (pPair == end())? nullptr : pPair->second;
	}
	void Erase(const Value& valueKey);
	bool DoesExist(const Value& valueKey) const { return find(const_cast<Value*>(&valueKey)) != end(); }
	ValueOwner* GetKeys() const { return ValueOwner::CollectKeys(*this); }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ValueDict& valueDict) const { return this == &valueDict; }
	bool IsEqualTo(const ValueDict& valueDict) const { return IsIdentical(valueDict); }
	bool IsLessThan(const ValueDict& valueDict) const { return this < &valueDict; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	static void IssueError_KeyNotFound(const Value& valueKey);
};

}

#endif

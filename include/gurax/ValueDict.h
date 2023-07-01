//==============================================================================
// ValueDict.h
//==============================================================================
#ifndef GURAX_VALUEDICT_H
#define GURAX_VALUEDICT_H
#include "ValueOwner.h"
#include "VType_Tuple.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueDict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueDict : public Referable {
public:
	using Map = std::unordered_map<Value*, Value*, Value::Hash, Value::EqualTo>;
private:
	Map _map;
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueDict);
public:
	enum class StoreMode { None, Strict, Overwrite, Timid, };
	enum class IterItem { Pair, Key, Value, };
public:
	template<IterItem iterItem>
	class Iterator_Each : public Iterator {
	private:
		RefPtr<ValueDict> _pValueDict;
		Map::const_iterator _iter;
	public:
		Iterator_Each(ValueDict* pValueDict) : _pValueDict(pValueDict), _iter(pValueDict->GetMap().begin()) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return Flag::Finite | Flag::LenDetermined;
		}
		virtual size_t GetLength() const override { return _pValueDict->GetMap().size(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
protected:
	~ValueDict() { Clear(); }
public:
	Map& GetMap() { return _map; }
	const Map& GetMap() const { return _map; }
	void Clear();
	ValueDict* Clone() const;
	ValueDict* CloneDeep() const;
	void Assign(RefPtr<Value> pValueKey, RefPtr<Value> pValue);
	bool Store(const ValueDict& valDict, StoreMode storeMode);
	bool Store(const Value& valueKey, const Value& value, StoreMode storeMode);
	const Value* Lookup(const Value& valueKey) const {
		auto pPair = _map.find(const_cast<Value*>(&valueKey));
		return (pPair == _map.end())? nullptr : pPair->second;
	}
	void Erase(const Value& valueKey);
	bool DoesExist(const Value& valueKey) const { return _map.find(const_cast<Value*>(&valueKey)) != _map.end(); }
	ValueOwner* GetKeys() const { return ValueOwner::CollectKeys(*this); }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const ValueDict& valueDict) const { return this == &valueDict; }
	bool IsEqualTo(const ValueDict& valueDict) const { return IsIdentical(valueDict); }
	bool IsLessThan(const ValueDict& valueDict) const { return this < &valueDict; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	bool Serialize(Stream& stream) const;
	static ValueDict* Deserialize(Stream& stream);
public:
	static void IssueError_KeyNotFound(const Value& valueKey);
};

//------------------------------------------------------------------------------
// ValueDict::Iterator_Each
//------------------------------------------------------------------------------
template<ValueDict::IterItem iterItem>
Value* ValueDict::Iterator_Each<iterItem>::DoNextValue()
{
	if (_iter == _pValueDict->GetMap().end()) return nullptr;
	auto iter = _iter++;
	if constexpr (iterItem == IterItem::Pair) {
		RefPtr<ValueOwner> pValues(new ValueOwner());
		pValues->reserve(2);
		pValues->push_back(iter->first->Reference());
		pValues->push_back(iter->second->Reference());
		return new Value_Tuple(pValues.release());
	} else if constexpr(iterItem == IterItem::Key) {
		return iter->first->Reference();
	} else { // iterItem == IterItem::Value
		return iter->second->Reference();
	}
}

template<ValueDict::IterItem iterItem>
String ValueDict::Iterator_Each<iterItem>::ToString(const StringStyle& ss) const
{
	return "Dict.Each";
}

}

#endif

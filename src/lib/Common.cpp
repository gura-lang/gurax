//==============================================================================
// Common.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

#if 0
template<typename T_Value, T_Value valueInvalid>
class SymbolMap {
public:
	using MapFromSymbol = std::unordered_map<
		const Symbol*, T_Value, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
	using MapToSymbol = std::unordered_map<T_Value, const Symbol*>;
private:
	MapFromSymbol _mapFromSymbol;
	MapToSymbol _mapToSymbol;
	static SymbolMap* _pSymbolMap;
public:
	virtual void Setup() = 0;
public:
	static T_Value FromSymbol(const Symbol* pSymbol) {
		if (!_pSymbolMap) {
			_pSymbolMap = new SymbolMap();
			_pSymbolMap->Setup();
		}
		auto iter = _pSymbolMap->_mapFromSymbol.find(pSymbol);
		return (iter == _pSymbolMap->_mapFromSymbol.end())? valueInvalid : iter->second;
	}
	static const Symbol* ToSymbol(T_Value value) {
		if (!_pSymbolMap) {
			_pSymbolMap = new SymbolMap();
			_pSymbolMap->Setup();
		}
		auto iter = _pSymbolMap->_mapToSymbol.find(value);
		return (iter == _pSymbolMap->_mapToSymbol.end())? Gurax_SymbolMark(Empty) : iter->second;
	}
};

template<typename T_Value, T_Value valueInvalid>
SymbolMap<T_Value, valueInvalid>* SymbolMap<T_Value, valueInvalid>::_pSymbolMap = nullptr;

class SymbolMap_MemberMode : public SymbolMap<MemberMode, MemberMode::None> {
public:
	virtual void Setup() override {
	}
};
#endif

//------------------------------------------------------------------------------
// MemberMode
//------------------------------------------------------------------------------
MemberMode SymbolToMemberMode(const Symbol* pSymbol)
{
	if (pSymbol->IsIdentical(Gurax_SymbolMark(Period))) return MemberMode::Normal;
	if (pSymbol->IsIdentical(Gurax_SymbolMark(ColonColon))) return MemberMode::MapToList;
	if (pSymbol->IsIdentical(Gurax_SymbolMark(ColonAsterisk))) return MemberMode::MapToIter;
	if (pSymbol->IsIdentical(Gurax_SymbolMark(ColonAnd))) return MemberMode::MapAlong;
	return MemberMode::None;
}

const Symbol* MemberModeToSymbol(MemberMode memberMode)
{
	switch (memberMode) {
	case MemberMode::Normal:	// foo.bar
		return Gurax_SymbolMark(Period);
	case MemberMode::MapToList:	// foo::bar .. map-to-list
		return Gurax_SymbolMark(ColonColon);
	case MemberMode::MapToIter:	// foo:*bar .. map-to-iterator
		return Gurax_SymbolMark(ColonAsterisk);
	case MemberMode::MapAlong:	// foo:&bar .. map-along
		return Gurax_SymbolMark(ColonAnd);
	default:
		return Gurax_SymbolMark(Empty);
	}
}

//------------------------------------------------------------------------------
// SortOrder
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// StringStyle
//------------------------------------------------------------------------------
const StringStyle StringStyle::Empty;

const char* StringStyle::_strsComma[2]		{ ", ", "," };
const char* StringStyle::_strsColon[2]		{ ": ", ":" };
const char* StringStyle::_strsSemicolon[2]	{ "; ", ";" };

//------------------------------------------------------------------------------
// Number types
//------------------------------------------------------------------------------

}

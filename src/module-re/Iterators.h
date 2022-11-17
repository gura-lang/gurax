//==============================================================================
// Iterators.h
//==============================================================================
#ifndef GURAX_MODULE_RE_ITERATORS_H
#define GURAX_MODULE_RE_ITERATORS_H
#include <gurax.h>

Gurax_BeginModuleScope(re)

//-----------------------------------------------------------------------------
// Iterator_Split
//-----------------------------------------------------------------------------
class Iterator_Split : public Iterator {
private:
	RefPtr<Pattern> _pPattern;
	String _str;
	int _cnt;
	int _idx;
	int _len;
	bool _doneFlag;
	OnigRegion_Ptr _region;
public:
	Iterator_Split(Pattern* pPattern, const String& str, int cntMax);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//-----------------------------------------------------------------------------
// Iterator_Scan
//-----------------------------------------------------------------------------
class Iterator_Scan : public Iterator {
private:
	RefPtr<Pattern> _pPattern;
	RefPtr<StringReferable> _pStr;
	int _idx, _idxEnd;
	int _len;
public:
	Iterator_Scan(Pattern* pPattern, StringReferable* pStr, int pos, int posEnd);
public:
	const StringReferable& GetStringReferable() const { return *_pStr; }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
	const char* GetString() const { return _pStr->GetString(); }
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//-----------------------------------------------------------------------------
// Iterator_Grep class declaration
//-----------------------------------------------------------------------------
class Iterator_Grep : public Iterator {
private:
	RefPtr<Iterator> _pIteratorSrc;
	RefPtr<Pattern> _pPattern;
public:
	Iterator_Grep(Iterator* pIteratorSrc, Pattern* pPattern);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return _pIteratorSrc->GetFlags() & (Flag::Finite | Flag::LenDetermined);
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

//-----------------------------------------------------------------------------
// Iterator_Group
//-----------------------------------------------------------------------------
class Iterator_Group : public Iterator {
private:
	RefPtr<Match> _pMatch;
	size_t _iGroup;
public:
	Iterator_Group(Match* pMatch);
public:
	// Virtual functions of Iterator
	virtual Flags GetFlags() const override {
		return Flag::Finite | Flag::LenUndetermined;
	}
	virtual size_t GetLength() const override { return -1; }
	virtual Value* DoNextValue() override;
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(re)

#endif

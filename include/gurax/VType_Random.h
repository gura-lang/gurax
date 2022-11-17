//==============================================================================
// VType_Random.h
//==============================================================================
#ifndef GURAX_VTYPE_RANDOM_H
#define GURAX_VTYPE_RANDOM_H
#include "VType_Object.h"
#include "Random.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Random
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Random : public VType {
public:
	class GURAX_DLLDECLARE Iterator_BoolSeq : public Iterator {
	private:
		RefPtr<Random> _pRandom;
		size_t _cnt;
		size_t _idx;
	public:
		Iterator_BoolSeq(Random* pRandom, size_t cnt) : _pRandom(pRandom), _cnt(cnt), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return (_cnt == -1)? (Flag::Infinite | Flag::LenUndetermined) : (Flag::Finite | Flag::LenDetermined);
		}
		virtual size_t GetLength() const override { return _cnt; }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	class GURAX_DLLDECLARE Iterator_FloatSeq : public Iterator {
	private:
		RefPtr<Random> _pRandom;
		size_t _cnt;
		size_t _idx;
	public:
		Iterator_FloatSeq(Random* pRandom, size_t cnt) :
			_pRandom(pRandom), _cnt(cnt), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return (_cnt == -1)? (Flag::Infinite | Flag::LenUndetermined) : (Flag::Finite | Flag::LenDetermined);
		}
		virtual size_t GetLength() const override { return _cnt; }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	class GURAX_DLLDECLARE Iterator_IntSeq : public Iterator {
	private:
		RefPtr<Random> _pRandom;
		size_t _cnt;
		size_t _idx;
		Int _range;
	public:
		Iterator_IntSeq(Random* pRandom, size_t cnt, Int range) :
			_pRandom(pRandom), _cnt(cnt), _idx(0), _range(range) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return (_cnt == -1)? (Flag::Infinite | Flag::LenUndetermined) : (Flag::Finite | Flag::LenDetermined);
		}
		virtual size_t GetLength() const override { return _cnt; }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	class GURAX_DLLDECLARE Iterator_NormalSeq : public Iterator {
	private:
		RefPtr<Random> _pRandom;
		size_t _cnt;
		size_t _idx;
		Double _mean;
		Double _stddev;
	public:
		Iterator_NormalSeq(Random* pRandom, size_t cnt, Double mean, Double stddev) :
			_pRandom(pRandom), _cnt(cnt), _idx(0), _mean(mean), _stddev(stddev) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return (_cnt == -1)? (Flag::Infinite | Flag::LenUndetermined) : (Flag::Finite | Flag::LenDetermined);
		}
		virtual size_t GetLength() const override { return _cnt; }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Random VTYPE_Random;

//------------------------------------------------------------------------------
// Value_Random
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Random : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Random);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Random");
protected:
	RefPtr<Random> _pRandom;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Random() = delete;
	explicit Value_Random(Random* pRandom, VType& vtype = VTYPE_Random) :
		Value_Object(vtype), _pRandom(pRandom) {}
	// Copy constructor/operator
	Value_Random(const Value_Random& src) :
		Value_Object(src), _pRandom(src._pRandom->Reference()) {}
	Value_Random& operator=(const Value_Random& src) = delete;
	// Move constructor/operator
	Value_Random(Value_Random&& src) = delete;
	Value_Random& operator=(Value_Random&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Random() = default;
public:
	Random& GetRandom() { return *_pRandom; }
	const Random& GetRandom() const { return *_pRandom; }
public:
	static Random& GetRandom(Value& value) {
		return dynamic_cast<Value_Random&>(value).GetRandom();
	}
	static const Random& GetRandom(const Value& value) {
		return dynamic_cast<const Value_Random&>(value).GetRandom();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetRandom().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetRandom().IsEqualTo(dynamic_cast<const Value_Random&>(value).GetRandom());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetRandom().IsLessThan(dynamic_cast<const Value_Random&>(value).GetRandom()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif

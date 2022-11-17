//==============================================================================
// VType_Random.h
//==============================================================================
#ifndef GURAX_MODULE_GMP_VTYPE_RANDOM_H
#define GURAX_MODULE_GMP_VTYPE_RANDOM_H
#include "module-gmp.h"

Gurax_BeginModuleScope(gmp)

//------------------------------------------------------------------------------
// VType_Random
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Random : public VType {
public:
	class GURAX_DLLDECLARE Iterator_FloatSeq : public Iterator {
	private:
		RefPtr<Random> _pRandom;
		size_t _cnt;
		size_t _idx;
		mp_bitcnt_t _prec;
	public:
		Iterator_FloatSeq(Random* pRandom, size_t cnt, mp_bitcnt_t prec) :
			_pRandom(pRandom), _cnt(cnt), _idx(0), _prec(prec) {}
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
		mpz_class _range;
	public:
		Iterator_IntSeq(Random* pRandom, size_t cnt, mpz_class range) :
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
private:
	static RefPtr<Random> _pRandomGlobal;
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	static Random& GetRandomGlobal() { return *_pRandomGlobal; }
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
	RefPtr<Random> _pEntity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Random(Random* pEntity, VType& vtype = VTYPE_Random) :
								Value_Object(vtype), _pEntity(pEntity) {}
	// Copy constructor/operator
	Value_Random(const Value_Random& src) = delete;
	Value_Random& operator=(const Value_Random& src) = delete;
	// Move constructor/operator
	Value_Random(Value_Random&& src) noexcept = delete;
	Value_Random& operator=(Value_Random&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Random() = default;
public:
	Random& GetEntity() { return *_pEntity; }
	const Random& GetEntity() const { return *_pEntity; }
	Random* GetEntityPtr() { return _pEntity.get(); }
	const Random* GetEntityPtr() const { return _pEntity.get(); }
public:
	static Random& GetEntity(Value& value) {
		return dynamic_cast<Value_Random&>(value).GetEntity();
	}
	static const Random& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Random&>(value).GetEntity();
	}
	static Random* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_Random&>(value).GetEntityPtr();
	}
	static const Random* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_Random&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_Random::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_Random::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gmp)

#endif

//==============================================================================
// VType_Palette.h
//==============================================================================
#ifndef GURAX_VTYPE_PALETTE_H
#define GURAX_VTYPE_PALETTE_H
#include "VType_Object.h"
#include "Palette.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Palette
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Palette : public VType {
public:
	class GURAX_DLLDECLARE Iterator_Each : public Iterator {
	private:
		RefPtr<Palette> _pPalette;
		size_t _idx;
	public:
		Iterator_Each(Palette* pPalette) : _pPalette(pPalette), _idx(0) {}
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return Flag::Finite | Flag::LenDetermined;
		}
		virtual size_t GetLength() const override { return _pPalette->GetSize(); }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Palette VTYPE_Palette;

//------------------------------------------------------------------------------
// Value_Palette
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Palette : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Palette);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Palette");
protected:
	RefPtr<Palette> _pPalette;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Palette() = delete;
	Value_Palette(Palette* pPalette, VType& vtype = VTYPE_Palette) : Value_Object(vtype), _pPalette(pPalette) {}
	// Copy constructor/operator
	Value_Palette(const Value_Palette& src) : Value_Object(src), _pPalette(src._pPalette.Reference()) {}
	Value_Palette& operator=(const Value_Palette& src) = delete;
	// Move constructor/operator
	Value_Palette(Value_Palette&& src) = delete;
	Value_Palette& operator=(Value_Palette&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Palette() = default;
public:
	Palette& GetPalette() { return *_pPalette; }
	const Palette& GetPalette() const { return *_pPalette; }
public:
	static Palette& GetPalette(Value& value) {
		return dynamic_cast<Value_Palette&>(value).GetPalette();
	}
	static const Palette& GetPalette(const Value& value) {
		return dynamic_cast<const Value_Palette&>(value).GetPalette();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetPalette().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetPalette().IsEqualTo(Value_Palette::GetPalette(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetPalette().IsLessThan(Value_Palette::GetPalette(value)) :
			GetVType().IsLessThan(value.GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif

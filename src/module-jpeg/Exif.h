//==============================================================================
// Exif.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_EXIF_H
#define GURAX_MODULE_JPEG_EXIF_H
#include <gurax.h>
#include "Segment.h"
#include "IFD.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Exif
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Exif : public Segment {
public:
	// Referable declaration
	Gurax_DeclareReferable(Exif);
protected:
	bool _beFlag;
	RefPtr<IFD> _pIFD0;
	RefPtr<IFD> _pIFD1;
public:
	// Constructor
	Exif(BinaryReferable* pBuff) : Segment(Marker::APP1, pBuff), _beFlag(false) {}
	Exif() : Exif(new BinaryReferable()) {}
	// Copy constructor/operator
	Exif(const Exif& src) = delete;
	Exif& operator=(const Exif& src) = delete;
	// Move constructor/operator
	Exif(Exif&& src) = delete;
	Exif& operator=(Exif&& src) noexcept = delete;
protected:
	~Exif() = default;
public:
	virtual bool IsExif() const override { return true; }
	virtual Value* CreateValue() const override;
	virtual bool AnalyzeBinary() override;
	virtual bool WriteToStream(Stream& stream) override;
	bool UpdateBinary();
public:
	void SetIFD0(IFD* pIFD);
	void SetIFD1(IFD* pIFD);
	IFD* GetIFD0() { return _pIFD0.get(); }
	IFD* GetIFD1() { return _pIFD1.get(); }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Exif& other) const { return this == &other; }
	bool IsEqualTo(const Exif& other) const { return IsIdentical(other); }
	bool IsLessThan(const Exif& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(jpeg)

#endif

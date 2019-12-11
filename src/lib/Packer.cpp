//==============================================================================
// Packer.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Packer
//------------------------------------------------------------------------------
#if 0
class GURAX_DLLDECLARE Packer : public Referable {
public:
	Gura_DeclareReferable(Packer)
public:
	Packer();
protected:
	virtual ~Packer();
public:
	bool Pack(const char *format, const ValueList &valListArg);
	Value Unpack(const char *format,
				 const ValueList &valListArg, bool exceedErrorFlag);
	template<typename T, bool bigEndianFlag> bool Put(T num) {
		if (!StorePrepare(sizeof(T))) return false;
		Store<T, bigEndianFlag>(num, bigEndianFlag);
		return true;
	}
	template<typename T, bool bigEndianFlag> bool Get(T* pNum, bool exceedErrorFlag) {
		const UInt8* pByte = ExtractPrepare(sizeof(T), exceedErrorFlag);
		if (!pByte) return false;
		*pNum = Extract<T, bigEndianFlag>(pByte);
		return true;
	}
	bool PutBuffer(const void* buff, size_t bytes);
public:
	virtual bool StorePrepare(size_t bytes) = 0;
	virtual void StoreBuffer(const void *buff, size_t bytes) = 0;
	virtual const UInt8* ExtractPrepare(size_t bytes, bool exceedErrorFlag) = 0;
private:
	template<typename T, bool bigEndianFlag> void Store(T num);
	template<typename T, bool bigEndianFlag> T Extract(const UInt8* pByte);
private:
	static bool CheckString(const ValueList &valList, ValueList::const_iterator pValue);
	static bool CheckNumber(const ValueList &valList, ValueList::const_iterator pValue);
	static bool CheckNumber(const ValueList &valList,
							ValueList::const_iterator pValue, Number numMin, Number numMax);
};
#endif

}

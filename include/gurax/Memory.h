//==============================================================================
// Memory
//==============================================================================
#ifndef GURAX_MEMORY_H
#define GURAX_MEMORY_H
#include "Common.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Memory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Memory : public Referable {
public:
	Gurax_DeclareReferable(Memory);
protected:
	size_t _bytes;
	char* _buff;
public:
	// Constructor
	Memory() : _bytes(0), _buff(nullptr) {}
	Memory(size_t bytes, void* buff) : _bytes(bytes), _buff(reinterpret_cast<char*>(buff)) {}
	// Copy constructor/operator
	Memory(const Memory& src) = delete;
	Memory& operator=(const Memory& src) = delete;
	// Move constructor/operator
	Memory(Memory&& src) = delete;
	Memory& operator=(Memory&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Memory() = default;
public:
	size_t GetBytes() const { return _bytes; }
	template<typename T> T* GetPointer() const { return reinterpret_cast<T*>(_buff); }
	template<typename T> T* GetPointer(size_t offset) const { return reinterpret_cast<T*>(_buff + offset); }
	void Fill(UInt8 data) { ::memset(_buff, data, _bytes); }
	String MakeId() const;
	virtual Memory* Clone() const = 0;
};

//------------------------------------------------------------------------------
// MemoryList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MemoryList {
public:
	using V = std::vector<Memory*>;
	V v;
};

//------------------------------------------------------------------------------
// MemoryOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MemoryOwner : public MemoryList {
public:
	~MemoryOwner();
	void Clear();
};

//------------------------------------------------------------------------------
// MemoryHeap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MemoryHeap : public Memory {
public:
	MemoryHeap(size_t bytes);
private:
	MemoryHeap(size_t bytes, void* buff) : Memory(bytes, buff) {}
protected:
	virtual ~MemoryHeap();
public:
	virtual Memory* Clone() const override;
};

#if defined(GURAX_ON_MSWIN)

//------------------------------------------------------------------------------
// MemoryDIB
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE MemoryDIB : public Memory {
private:
	HBITMAP _hBitmap;
public:
	MemoryDIB();
protected:
	virtual ~MemoryDIB();
public:
	inline HBITMAP GetHBITMAP() { return _hBitmap; }
	bool AllocBuffer(size_t width, size_t height, size_t bitsPerPixel);
	virtual Memory* Clone() const override;
};

#endif

}

#endif

//==============================================================================
// Binary.h
//==============================================================================
#ifndef GURAX_BINARY_H
#define GURAX_BINARY_H
#include "String.h"
#include "StringStyle.h"
#include "DumpStyle.h"

namespace Gurax {

class BinaryList;
	
//------------------------------------------------------------------------------
// Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Binary : public std::basic_string<UInt8> {
public:
	// Algorithm operators
	struct EqualTo {
		bool operator()(const Binary& binary1, const Binary& binary2) const {
			return binary1.IsEqualTo(binary2);
		}
	};
	struct LessThan {
		bool operator()(const Binary& binary1, const Binary& binary2) const {
			return binary1.IsLessThan(binary2);
		}
	};
	struct GreaterThan {
		bool operator()(const Binary& binary1, const Binary& binary2) const {
			return binary2.IsLessThan(binary1);
		}
	};
	struct Hash {
		bool operator()(const Binary& binary) const {
			return binary.CalcHash();
		}
	};
public:
	static const Binary Empty;
private:
	bool _writableFlag;
public:
	// Constructor
	Binary() : _writableFlag(true) {}
	Binary(const char* src) : basic_string(reinterpret_cast<const UInt8*>(src)), _writableFlag(true) {}
	Binary(const UInt8* src, size_t len) : basic_string(src, len), _writableFlag(true) {}
	Binary(const char* src, size_t len) : Binary(reinterpret_cast<const UInt8*>(src), len) {}
	Binary(const String& src) : Binary(src.data(), src.size()) {}
	Binary(size_t len, UInt8 c) : basic_string(len, c), _writableFlag(true) {}
	// Copy constructor/operator
	Binary(const Binary& src) : basic_string(src), _writableFlag(src._writableFlag) {}
	Binary& operator=(const Binary& src) noexcept;
	// Move constructor/operator
	Binary(Binary&& src) noexcept : basic_string(src), _writableFlag(src._writableFlag) {}
	Binary& operator=(Binary&& src) noexcept;
	// Destructor
	~Binary() = default;
public:
	static void Bootup();
public:
	void SetWritableFlag(bool writableFlag) { _writableFlag = writableFlag; }
	bool IsWritable() const { return _writableFlag; }
	String ConvertToString() { return String(reinterpret_cast<const char*>(data()), size()); }
	String Enquote(char chQuote = '\'') const;
	bool CheckWritable() const;
public:
	Binary& Append(const void* p, size_t bytes) {
		append(reinterpret_cast<const UInt8*>(p), bytes);
		return *this;
	}
	Binary Repeat(bool writableFlag, size_t n) const { return Repeat(*this, writableFlag, n); }
	static Binary Repeat(const Binary& binary, bool writableFlag, size_t n);
public:
	size_t CalcHash() const { return CalcHash(data(), size()); }
	static size_t CalcHash(const UInt8* binary, size_t len);
	bool IsEqualTo(const Binary& binary) const {
		return ::memcmp(data(), binary.data(), std::min(size(), binary.size())) == 0;
	}
	bool IsLessThan(const Binary& binary) const {
		return ::memcmp(data(), binary.data(), std::min(size(), binary.size())) < 0;
	}
	String ToString(const StringStyle& ss) const;
};

//------------------------------------------------------------------------------
// BinaryList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE BinaryList : public ListBase<Binary> {
};

//------------------------------------------------------------------------------
// BinaryReferable
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE BinaryReferable : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(BinaryReferable);
private:
	Binary _binary;
public:
	// Constructor
	BinaryReferable() {}
	BinaryReferable(size_t len, UInt8 data) : _binary(len, data) {}
	explicit BinaryReferable(Binary binary) : _binary(std::move(binary)) {}
	// Copy constructor/operator
	BinaryReferable(const BinaryReferable& src) = delete;
	BinaryReferable& operator=(const BinaryReferable& src) = delete;
	// Move constructor/operator
	BinaryReferable(BinaryReferable&& src) = delete;
	BinaryReferable& operator=(BinaryReferable&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~BinaryReferable() = default;
public:
	Binary& GetBinary() { return _binary; }
	const Binary& GetBinary() const { return _binary; }
};

}

#endif

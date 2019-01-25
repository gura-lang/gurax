//==============================================================================
// Binary.h
//==============================================================================
#ifndef GURAX_BINARY_H
#define GURAX_BINARY_H
#include "String.h"

namespace Gurax {

class BinaryList;
	
//------------------------------------------------------------------------------
// Binary
//------------------------------------------------------------------------------
class Binary : public std::basic_string<UInt8> {
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
public:
	Binary(const char* src) : basic_string(reinterpret_cast<const UInt8*>(src)) {}
	Binary(const char* src, size_t len) : basic_string(reinterpret_cast<const UInt8*>(src), len) {}
	Binary(const String& src) : Binary(src.data(), src.size()) {}
	// Inherits constructors
	using std::basic_string<UInt8>::basic_string;
public:
	static void Bootup();
public:
	String MakeQuoted(bool surroundFlag = false) const;
public:
	size_t CalcHash() const { return CalcHash(data(), size()); }
	static size_t CalcHash(const UInt8* binary, size_t len);
	bool IsEqualTo(const Binary& binary) const {
		return ::memcmp(data(), binary.data(), std::min(size(), binary.size())) == 0;
	}
	bool IsLessThan(const Binary& binary) const {
		return ::memcmp(data(), binary.data(), std::min(size(), binary.size())) < 0;
	}
};

#if 0
inline String operator+(const String& v1, const String& v2) {
	return String(static_cast<std::string>(v1) + static_cast<std::string>(v2));
}
#endif

//------------------------------------------------------------------------------
// BinaryList
//------------------------------------------------------------------------------
class BinaryList : public std::vector<Binary> {
};

//------------------------------------------------------------------------------
// BinaryReferable
//------------------------------------------------------------------------------
class BinaryReferable : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(BinaryReferable);
private:
	Binary _binary;
public:
	// Constructor
	BinaryReferable() = delete;
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

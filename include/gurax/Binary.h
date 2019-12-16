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
	Binary(bool writableFlag) : _writableFlag(writableFlag) {}
	Binary(bool writableFlag, const char* src) :
		basic_string(reinterpret_cast<const UInt8*>(src)), _writableFlag(writableFlag) {}
	Binary(bool writableFlag, const char* src, size_t len) :
		basic_string(reinterpret_cast<const UInt8*>(src), len), _writableFlag(writableFlag) {}
	Binary(bool writableFlag, const String& src) :
		Binary(writableFlag, src.data(), src.size()) {}
	Binary(bool writableFlag, const Binary& src) : basic_string(src), _writableFlag(writableFlag) {}
	// Copy constructor/operator
	Binary(const Binary& src) : basic_string(src), _writableFlag(src._writableFlag) {}
	Binary& operator=(Binary& src) noexcept = delete;
	// Move constructor/operator
	Binary(Binary&& src) : basic_string(src), _writableFlag(src._writableFlag) {}
	Binary& operator=(Binary&& src) noexcept = delete;
	// Destructor
	~Binary() = default;
public:
	static void Bootup();
public:
	void SetWritableFlag(bool writableFlag) { _writableFlag = writableFlag; }
	bool IsWritable() const { return _writableFlag; }
	String ConvertToString() { return String(reinterpret_cast<const char*>(data()), size()); }
	String MakeQuoted(bool surroundFlag = false) const;
	bool CheckWritable() const;
	void Dump(Stream& stream, const StringStyle& ss = StringStyle::Empty) const;
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
class GURAX_DLLDECLARE BinaryList : public std::vector<Binary> {
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
	BinaryReferable(bool writableFlag) : _binary(writableFlag) {}
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

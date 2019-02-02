//==============================================================================
// Declaration.h
//==============================================================================
#ifndef GURAX_DECLARATION_H
#define GURAX_DECLARATION_H
#include "Attribute.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Declaration
//------------------------------------------------------------------------------
class Declaration : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Declaration);
public:
	class ArgInfo : public Referable {
	public:
		// Referable declaration
		Gurax_DeclareReferable(ArgInfo);
	private:
		RefPtr<Attribute> _pAttr;	
	public:
		// Constructor
		ArgInfo() {}
		// Copy constructor/operator
		ArgInfo(const ArgInfo& src) = delete;
		ArgInfo& operator=(const ArgInfo& src) = delete;
		// Move constructor/operator
		ArgInfo(ArgInfo&& src) = delete;
		ArgInfo& operator=(ArgInfo&& src) noexcept = delete;
	protected:
		// Destructor
		~ArgInfo() = default;
	public:
		size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
		bool IsIdentical(const ArgInfo& argInfo) const { return this == &argInfo; }
		bool IsEqualTo(const ArgInfo& argInfo) const { return IsIdentical(argInfo); }
		bool IsLessThan(const ArgInfo& argInfo) const { return this < &argInfo; }
		String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(argInfo)"; }
	};
	class ArgInfoList : public std::vector<ArgInfo*> {
	};
	class ArgInfoOwner: public ArgInfoList {
	public:
		~ArgInfoOwner() { Clear(); }
		void Clear() {
			for (ArgInfo* pArgInfo : *this) ArgInfo::Delete(pArgInfo);
			clear();
		}
	};
private:
	ArgInfoOwner _argInfoOwner;
	RefPtr<Attribute> _pAttr;
public:
	// Constructor
	Declaration() {}
	// Copy constructor/operator
	Declaration(const Declaration& src) = delete;
	Declaration& operator=(const Declaration& src) = delete;
	// Move constructor/operator
	Declaration(Declaration&& src) = delete;
	Declaration& operator=(Declaration&& src) noexcept = delete;
protected:
	// Destructor
	~Declaration() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Declaration& declaration) const { return this == &declaration; }
	bool IsEqualTo(const Declaration& declaration) const { return IsIdentical(declaration); }
	bool IsLessThan(const Declaration& declaration) const { return this < &declaration; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(declaration)"; }
};

}

#endif

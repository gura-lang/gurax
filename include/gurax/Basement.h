//==============================================================================
// Basement.h
//==============================================================================
#ifndef GURAX_BASEMENT_H
#define GURAX_BASEMENT_H
#include "Frame.h"
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Basement
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Basement {
private:
	RefPtr<Frame> _pFrame;
	String _ps1;
	String _ps2;
	StringList _pathList;
public:
	static Basement Inst;
public:
	// Constructor
	Basement();
	// Copy constructor/operator
	Basement(const Basement& src) = delete;
	Basement& operator=(const Basement& src) = delete;
	// Move constructor/operator
	Basement(Basement&& src) = delete;
	Basement& operator=(Basement&& src) noexcept = delete;
	// Destructor
	~Basement() = default;
public:
	void Prepare();
	void PrepareVType(Frame& frame);
	void PrepareValue(Frame& frame);
	Frame& GetFrame() { return *_pFrame; }
	const char* GetPS1() const { return _ps1.c_str(); }
	const char* GetPS2() const { return _ps2.c_str(); }
	void SetPS1(const char* ps1) { _ps1 = ps1; }
	void SetPS2(const char* ps2) { _ps2 = ps2; }
	StringList& GetPathList() { return _pathList; }
	const StringList& GetPathList() const { return _pathList; }
};

}

#endif

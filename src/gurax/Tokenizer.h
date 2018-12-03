//==============================================================================
// Tokenizer.h
//==============================================================================
#ifndef GURAX_TOKENIZER_H
#define GURAX_TOKENIZER_H
#include <memory>
#include <utility>

namespace Gurax {

//------------------------------------------------------------------------------
// UniquePtr
//------------------------------------------------------------------------------
template<typename T> class UniquePtr {
private:
	T *_p;
public:
	UniquePtr(T *p = nullptr) : _p(p) {}
	~UniquePtr() { T::Delete(_p); }
	UniquePtr(const UniquePtr<T> &obj) = delete;
	T &operator*() { return *_p; }
	T &operator*() const { return *_p; }
	T *operator->() { return _p; }
	T *operator->() const { return _p; }
	void reset(T *p = nullptr) { T::Delete(_p); _p = p; }
	T *get() { return _p; }
	T *get() const { return _p; }
	T *release() { T *p = _p; _p = nullptr; return p; }
	bool IsNull() const { return _p == nullptr; }
	void operator=(const T *p) = delete;
};

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
class Tokenizer {
protected:
	int _cntRef;
public:
	Tokenizer() : _cntRef(1) {}
public:
	Tokenizer *Reference() const { const_cast<Tokenizer *>(this)->_cntRef++; return const_cast<Tokenizer *>(this); }
	static void Delete(Tokenizer *p) { if (--p->_cntRef) delete p; }
protected:
	~Tokenizer() {}
};

}

#endif

//==============================================================================
// Random.h
//==============================================================================
#ifndef GURAX_RANDOM_H
#define GURAX_RANDOM_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Random
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Random : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Random);
private:
	UInt32 _seed;
	std::mt19937 _engine;
private:
	static RefPtr<Random> _pRandomGlobal;
public:
	// Constructor
	explicit Random(UInt32 seed) : _seed(seed), _engine(seed) {}
	// Copy constructor/operator
	Random(const Random& src) = delete;
	Random& operator=(const Random& src) = delete;
	// Move constructor/operator
	Random(Random&& src) = delete;
	Random& operator=(Random&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Random() = default;
public:
	static void Bootup(UInt32 seed);
	static void Bootup();
	static Random& Global() { return *_pRandomGlobal; }
	std::mt19937& GetEngine() { return  _engine; }
	void Reset() { _engine.seed(_seed); }
	void SetSeed(UInt32 seed) { _seed = seed; _engine.seed(_seed); }
	UInt32 GetSeed() const { return _seed; }
	Bool GenBool() { return !!GenInt<int>(2); }
	template<typename T = Double> T GenFloat() { return std::uniform_real_distribution<T>()(_engine); }
	template<typename T = Int> T GenInt(T range) { return static_cast<T>(GenFloat<Double>() * range); }
	template<typename T = Double> T GenNormal(T mean = 0., T stddev = 1.) {
		return std::normal_distribution<T>(mean, stddev)(_engine);
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Random& random) const { return this == &random; }
	bool IsEqualTo(const Random& random) const { return IsIdentical(random); }
	bool IsLessThan(const Random& random) const { return this < &random; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif

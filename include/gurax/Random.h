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
	static void Bootup(UInt32 seed) { _pRandomGlobal.reset(new Random(seed)); }
	static void Bootup() { Bootup(std::random_device()()); }
	static Random &Global() { return *_pRandomGlobal; }
	void Reset() { _engine.seed(_seed); }
	template<typename T = double> T Uniform() { return std::uniform_real_distribution<T>()(_engine); }
	template<typename T = double> T Normal(T mean = 0., T stddev = 1.) {
		return std::normal_distribution<T>(mean, stddev)(_engine);
	}
	template<typename T = int> T Range(T range) { return static_cast<T>(Uniform<Double>() * range); }
};

}

#endif

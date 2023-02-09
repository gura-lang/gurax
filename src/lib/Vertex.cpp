//==============================================================================
// Vertex.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Vertex
//------------------------------------------------------------------------------
const Vertex Vertex::Zero;

Vertex Vertex::Translate(const Vertex& v, Double tx, Double ty, Double tz)
{
	return Vertex(v.x + tx, v.y + ty, v.z + tz);
}

Vertex Vertex::RotateX(const Vertex& v, Double rad)
{
	Double numCos = ::cos(rad), numSin = ::sin(rad);
	return Vertex(v.x, numCos * v.y - numSin * v.z, numSin * v.y + numCos * v.z);
}

Vertex Vertex::RotateY(const Vertex& v, Double rad)
{
	Double numCos = ::cos(rad), numSin = ::sin(rad);
	return Vertex(numCos * v.x + numSin * v.z, v.y, -numSin * v.x + numCos * v.z);
}

Vertex Vertex::RotateZ(const Vertex& v, Double rad)
{
	double numCos = ::cos(rad), numSin = ::sin(rad);
	return Vertex(numCos * v.x - numSin * v.y, numSin * v.x + numCos * v.y, v.z);
}

Vertex Vertex::Neg(const Vertex& v)
{
	return Vertex(-v.x, -v.y, -v.z);
}

Vertex Vertex::Add(const Vertex& v1, const Vertex& v2)
{
	return Vertex(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vertex Vertex::Sub(const Vertex& v1, const Vertex& v2)
{
	return Vertex(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vertex Vertex::Mul(const Vertex& v, Double num)
{
	return Vertex(v.x * num, v.y * num, v.z * num);
}

Vertex Vertex::Div(const Vertex& v, Double num)
{
	return Vertex(v.x / num, v.y / num, v.z / num);
}

Double Vertex::Dot(const Vertex& v1, const Vertex& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vertex Vertex::Cross(const Vertex& v1, const Vertex& v2)
{
	return Vertex(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

Double Vertex::Norm(const Vertex& v)
{
	return ::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vertex Vertex::Normal(const Vertex& v1, const Vertex& v2, const Vertex& v3, bool unitFlag)
{
	Double x1 = v2.x - v1.x, y1 = v2.y - v1.y, z1 = v2.z - v1.z;
	Double x2 = v3.x - v1.x, y2 = v3.y - v1.y, z2 = v3.z - v1.z;
	Double x = y1 * z2 - z1 * y2;
	Double y = z1 * x2 - x1 * z2;
	Double z = x1 * y2 - y1 * x2;
	if (unitFlag) {
		Double len = ::sqrt(x * x + y * y + z * z);
		return (len == 0)? Vertex::Zero : Vertex(x / len, y / len, z / len);
	} else {
		return Vertex(x, y, z);
	}
}

Vertex Vertex::CreateFromValues(const ValueList& valList)
{
	return Zero;
}

String Vertex::ToString(const StringStyle& ss) const
{
	return String().Format("Vertex");
}

}

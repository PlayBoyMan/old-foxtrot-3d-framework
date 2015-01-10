#include "Vector.h"

using namespace framework::vec;

/// Cross product operator
Vector<3> framework::vec::operator^(const Vector<3> &left, const Vector<3> &right)
{
	float cross[3] = { left.data[1] * right.data[2] - left.data[2] * right.data[1],
		left.data[2] * right.data[0] - left.data[0] * right.data[2],
		left.data[0] * right.data[1] - left.data[1] * right.data[0] };

	return Vector<3>(cross);

}

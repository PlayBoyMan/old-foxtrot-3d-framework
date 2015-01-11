#include "Frustum.h"

#include "../framework/Foxtrot.h"

using namespace framework;

Frustum::Frustum() 
{
}


Frustum::~Frustum()
{
}

Frustum::Frustum(float n, float f, float r, float l, float t, float b, FrustumType type)
	:	_near(n),
		_far(f),
		right(r),
		left(l),
		top(t), 
		bottom(b),
		frustum_type(type)
{

	set(n, f, r, l, t, b, type);

}

Frustum::Frustum(float n, float f, float r, float l, float t, float b)
	: _near(n),
	_far(f),
	right(r),
	left(l),
	top(t),
	bottom(b),
	frustum_type(PERSPECTIVE_FRUSTUM)
{

	set(n, f, r, l, t, b, PERSPECTIVE_FRUSTUM);

}



void Frustum::set(float n, float f, float r, float l, float t, float b, FrustumType type)
{
	if (type == PERSPECTIVE_FRUSTUM)
		frustum_matrix = transform::frustum_matrix(n, f, r, l, t, b);

	else
		frustum_matrix = transform::orthogonal_projection_matrix(n, f, r, l, t, b);
}

void Frustum::update()
{
	set(_near, _far, right, left, top, bottom, frustum_type);
}

// TODO: multiply instead of increment
void Frustum::zoom(float factor)
{
	float aspect_ratio =  (top - bottom) / (right - left);

	right =  right - factor;
	left =   left  + factor;

	float delta = aspect_ratio * (right - left) - (top - bottom);
	top = top + delta/2;
	bottom = bottom - delta/2;
	
	update();
}

void Frustum::zoom_near(float factor)
{
	_near += factor;
	update();
}
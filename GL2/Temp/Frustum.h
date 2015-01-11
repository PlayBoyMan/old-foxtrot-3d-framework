#pragma once

#include "../framework/Foxtrot.h"

using namespace framework;


class Frustum
{
public:

	enum FrustumType { PERSPECTIVE_FRUSTUM, ORTHOGRAPHIC_FRUSTUM };	

	float _near, _far, right, left, top, bottom;

	mat::Mat4 frustum_matrix;

	FrustumType frustum_type;

	Frustum( );

	Frustum(float n, float f, float r, float l, float t, float b);

	Frustum(float n, float f, float r, float l, float t, float b, FrustumType type);

	void update();

	void set(float n, float f, float r, float l, float t, float b, FrustumType type);

	void zoom(float factor);

	void zoom_near(float factor);

	~Frustum();
};


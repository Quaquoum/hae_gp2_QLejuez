#pragma once

float catmull(float p0, float p1, float p2, float p3, float t)
{
	auto q = 2.0f * p1;
	auto t2 = t * t;

	q += (-p0 + p2) * t;
	q += (2.0f*p0 - 5.0f*p1 + 4.0f * p2 - p3) * t2;
	q += (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t2 * t;

	return q * 0.5f;
}
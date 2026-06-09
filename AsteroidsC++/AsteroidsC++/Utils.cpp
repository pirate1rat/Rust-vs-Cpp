#include "Utils.h"

Vector2 transform(Vector2 p, Vector2 position, float rotation) {
	p = Vector2Add(p, position);
	Vector2 supportVec = Vector2{
		p.x - position.x,
		p.y - position.y
	};
	supportVec = Vector2Rotate(supportVec, rotation);
	return Vector2{
		position.x + supportVec.x,
		position.y + supportVec.y
	};
}

float randFloat(float min, float max) {
	return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}

float cross(Vector2 a, Vector2 b, Vector2 c) {
	return (b.x - a.x) * (c.y - a.y)
		- (b.y - a.y) * (c.x - a.x);
}

bool onSegment(Vector2 a, Vector2 b, Vector2 p) {
	return std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x)
		&& std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}
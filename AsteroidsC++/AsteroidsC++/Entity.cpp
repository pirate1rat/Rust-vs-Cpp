#include "Entity.h"
#include "Constants.h"
#include "raymath.h"

#define DEBUG

Entity::Entity(Sprite spriteEnum) {
	this->prefab = &static_sprites[spriteEnum];
}

void Entity::reposition(Vector2 repositionVec) {
	position = Vector2Add(position, repositionVec);
}

void Entity::draw() {
	Vector2 p1, p2, supportVec;
	for (int i = 0; i < prefab->gLength - 1; i++) {
		p1 = Vector2Add(prefab->gPoints[i], position);
		supportVec = Vector2{ p1.x - position.x,
						      p1.y - position.y };
		supportVec = Vector2Rotate(supportVec, rotation);
		p1 = Vector2{ position.x + supportVec.x,
					  position.y + supportVec.y };

		p2 = Vector2Add(prefab->gPoints[i+1], position);
		supportVec = Vector2{ p2.x - position.x,
							  p2.y - position.y };
		supportVec = Vector2Rotate(supportVec, rotation);
		p2 = Vector2{ position.x + supportVec.x,
					  position.y + supportVec.y };
		DrawLineV(p1, p2, defaultColor);
	}
	Vector2 p0 = Vector2Add(prefab->gPoints[0], position);
	supportVec = Vector2{ p0.x - position.x,
						  p0.y - position.y };
	supportVec = Vector2Rotate(supportVec, rotation);
	p0 = Vector2{ position.x + supportVec.x,
				  position.y + supportVec.y };
	DrawLineV(p2, p0, defaultColor);

#ifdef DEBUG
	for (int i = 0; i < prefab->hLength - 1; i++) {
		p1 = Vector2Add(prefab->hPoints[i], position);
		supportVec = Vector2{ p1.x - position.x,
							  p1.y - position.y };
		supportVec = Vector2Rotate(supportVec, rotation);
		p1 = Vector2{ position.x + supportVec.x,
					  position.y + supportVec.y };

		p2 = Vector2Add(prefab->hPoints[i + 1], position);
		supportVec = Vector2{ p2.x - position.x,
							  p2.y - position.y };
		supportVec = Vector2Rotate(supportVec, rotation);
		p2 = Vector2{ position.x + supportVec.x,
					  position.y + supportVec.y };
		DrawLineV(p1, p2, BLUE);
	}
	p0 = Vector2Add(prefab->hPoints[0], position);
	supportVec = Vector2{ p0.x - position.x,
						  p0.y - position.y };
	supportVec = Vector2Rotate(supportVec, rotation);
	p0 = Vector2{ position.x + supportVec.x,
				  position.y + supportVec.y };
	DrawLineV(p2, p0, BLUE);
#endif // DEBUG

}

void Entity::move() {
	position = Vector2Add(position, movementVec);

	if (position.x < (float)(-MARGIN)) {
		reposition(Vector2{ (float)(WINDOW_WIDTH + 2 * MARGIN), 0.0f });
	}
	else if ((float)(WINDOW_WIDTH + MARGIN) < position.x) {
		reposition(Vector2{ (float)(-WINDOW_WIDTH - 2 * MARGIN), 0.0f });
	}

	if (position.y < (float)(-MARGIN)) {
		reposition(Vector2{ 0.0f, (float)(WINDOW_HIGHT + 2 * MARGIN) });
	}
	else if ((float)(WINDOW_HIGHT + MARGIN) < position.y) {
		reposition(Vector2{ 0.0f, (float)(-WINDOW_HIGHT - 2 * MARGIN) });
	}
}

float Entity::cross(Vector2 a, Vector2 b, Vector2 c) {
	return (b.x - a.x) * (c.y - a.y)
		- (b.y - a.y) * (c.x - a.x);
}

bool Entity::onSegment(Vector2 a, Vector2 b, Vector2 p) {
	return std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x)
		&& std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}

bool Entity::checkCollision(Entity* other) {
	for (int i = 0; i < prefab->hLength - 1; i++) {
		Vector2 a = Vector2Add(prefab->hPoints[i], position);
		Vector2 b = Vector2Add(prefab->hPoints[i+1], position);
		for (int j = 0; j < other->prefab->hLength - 1; j++) {
			Vector2 c = Vector2Add(other->prefab->hPoints[j], other->position);
			Vector2 d = Vector2Add(other->prefab->hPoints[j+1], other->position);

			float d1 = cross(a, b, c);
			float d2 = cross(a, b, d);
			float d3 = cross(c, d, a);
			float d4 = cross(c, d, b);

			if ((d1 > 0 && d2 < 0 || d1 < 0 && d2 > 0) &&
				(d3 > 0 && d4 < 0 || d3 < 0 && d4 > 0)) {
				return true;
			}

			// edgecase
			if (abs(d1) < EPS && onSegment(a, b, c)) return true;
			if (abs(d2) < EPS && onSegment(a, b, d)) return true;
			if (abs(d3) < EPS && onSegment(c, d, a)) return true;
			if (abs(d4) < EPS && onSegment(c, d, b)) return true;
		}
	}

	Vector2 a = Vector2Add(prefab->hPoints[prefab->hLength - 1], position);
	Vector2 b = Vector2Add(prefab->hPoints[0], position);
	Vector2 c = Vector2Add(other->prefab->hPoints[other->prefab->hLength - 1], other->position);
	Vector2 d = Vector2Add(other->prefab->hPoints[0], other->position);

	float d1 = cross(a, b, c);
	float d2 = cross(a, b, d);
	float d3 = cross(c, d, a);
	float d4 = cross(c, d, b);

	if ((d1 > 0 && d2 < 0 || d1 < 0 && d2 > 0) &&
		(d3 > 0 && d4 < 0 || d3 < 0 && d4 > 0)) {
		return true;
	}

	// edgecase
	if (abs(d1) < EPS && onSegment(a, b, c)) return true;
	if (abs(d2) < EPS && onSegment(a, b, d)) return true;
	if (abs(d3) < EPS && onSegment(c, d, a)) return true;
	if (abs(d4) < EPS && onSegment(c, d, b)) return true;
	
	return false;
}

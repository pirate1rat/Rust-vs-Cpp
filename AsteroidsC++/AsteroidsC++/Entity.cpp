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

bool Entity::overlap(Entity& other)
{
	
	return false;
}

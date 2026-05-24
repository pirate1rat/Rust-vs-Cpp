#include "Entity.h"
#include "Constants.h"
#include "raymath.h"

#define DEBUG

Entity::Entity(Sprite spriteEnum) {
	this->sprite = &static_sprites[spriteEnum];
}

void Entity::reposition(Vector2 repositionVec) {
	position = Vector2Add(position, repositionVec);
}

void Entity::draw() {
	Vector2 p1, p2, supportVec;
	for (int i = 0; i < sprite->length - 1; i++) {
		//p1 = p2;
		//p2 = Vector2Add(sprite->points[i], position);
		//supportVec = Vector2{ sprite->points[1].x - position.x,
		//					  sprite->points[1].y - position.y };
		//supportVec = Vector2Rotate(supportVec, rotation);
		//p2 = Vector2{ position.x + supportVec.x,
		//		      position.y + supportVec.y };
		//DrawLineV(p1, p2, defaultColor);
		p1 = Vector2Add(sprite->points[i], position);
		supportVec = Vector2{ p1.x - position.x,
									  p1.y - position.y };
		supportVec = Vector2Rotate(supportVec, rotation);
		p1 = Vector2{ position.x + supportVec.x,
					  position.y + supportVec.y };

		p2 = Vector2Add(sprite->points[i+1], position);
		supportVec = Vector2{ p2.x - position.x,
							  p2.y - position.y };
		supportVec = Vector2Rotate(supportVec, rotation);
		p2 = Vector2{ position.x + supportVec.x,
					  position.y + supportVec.y };
		DrawLineV(p1, p2, defaultColor);
	}
	Vector2 p0 = Vector2Add(sprite->points[0], position);
	supportVec = Vector2{ p0.x - position.x,
						  p0.y - position.y };
	supportVec = Vector2Rotate(supportVec, rotation);
	p0 = Vector2{ position.x + supportVec.x,
				  position.y + supportVec.y };
	DrawLineV(p2, p0, defaultColor);

#ifdef DEBUG
	for (int i = 0; i < hitboxPts.size() - 1; i++) {
		DrawLineV(hitboxPts[i], hitboxPts[i + 1], BLUE);
	}
	DrawLineV(hitboxPts[hitboxPts.size() - 1], hitboxPts[0], BLUE);
#endif // DEBUG

}

void Entity::move() {
	//for (int i = 0; i < graphPts.size(); i++) {
	//	graphPts[i] = Vector2Add(graphPts[i], movementVec);
	//}
	for (int i = 0; i < hitboxPts.size(); i++) {
		hitboxPts[i] = Vector2Add(hitboxPts[i], movementVec);
	}
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

#include "Entity.h"
#include "Constants.h"
#include "raymath.h"

#define DEBUG

Entity::Entity() {
}

void Entity::reposition(Vector2 repositionVec) {
	for (int i = 0; i < graphPts.size(); i++) {
		graphPts[i] = Vector2Add(graphPts[i], repositionVec);
	}
	for (int i = 0; i < hitboxPts.size(); i++) {
		hitboxPts[i] = Vector2Add(hitboxPts[i], repositionVec);
	}
	centerOfGravity = Vector2Add(centerOfGravity, repositionVec);
}

void Entity::draw() {
	for (int i = 0; i < graphPts.size() - 1; i++) {
		DrawLineV(graphPts[i], graphPts[i+1], defaultColor);
	}
	DrawLineV(graphPts[graphPts.size() - 1], graphPts[0], defaultColor);

#ifdef DEBUG
	for (int i = 0; i < hitboxPts.size() - 1; i++) {
		DrawLineV(hitboxPts[i], hitboxPts[i + 1], BLUE);
	}
	DrawLineV(hitboxPts[hitboxPts.size() - 1], hitboxPts[0], BLUE);
#endif // DEBUG

}

void Entity::move() {
	for (int i = 0; i < graphPts.size(); i++) {
		graphPts[i] = Vector2Add(graphPts[i], movementVec);
	}
	for (int i = 0; i < hitboxPts.size(); i++) {
		hitboxPts[i] = Vector2Add(hitboxPts[i], movementVec);
	}
	centerOfGravity = Vector2Add(centerOfGravity, movementVec);

	if (centerOfGravity.x < (float)(-MARGIN)) {
		reposition(Vector2{ (float)(WINDOW_WIDTH + 2 * MARGIN), 0.0f });
	}
	else if ((float)(WINDOW_WIDTH + MARGIN) < centerOfGravity.x) {
		reposition(Vector2{ (float)(-WINDOW_WIDTH - 2 * MARGIN), 0.0f });
	}

	if (centerOfGravity.y < (float)(-MARGIN)) {
		reposition(Vector2{ 0.0f, (float)(WINDOW_HIGHT + 2 * MARGIN) });
	}
	else if ((float)(WINDOW_HIGHT + MARGIN) < centerOfGravity.y) {
		reposition(Vector2{ 0.0f, (float)(-WINDOW_HIGHT - 2 * MARGIN) });
	}
}

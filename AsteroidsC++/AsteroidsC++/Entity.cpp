#include "Entity.h"
#include "Constants.h"
#include "raymath.h"

Entity::Entity(Vector2 windowCenter) {
}

void Entity::reposition(Vector2 repositionVec) {
	for (int i = 0; i < points.size(); i++) {
		points[i] = Vector2Add(points[i], repositionVec);
	}
	centerOfGravity = Vector2Add(centerOfGravity, repositionVec);
}

void Entity::draw() {
	for (int i = 0; i < points.size() - 1; i++) {
		DrawLineV(points[i], points[i+1], defaultColor);
	}
	DrawLineV(points[points.size() - 1], points[0], defaultColor);
}

void Entity::move() {
	for (int i = 0; i < points.size(); i++) {
		points[i] = Vector2Add(points[i], movementVec);
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

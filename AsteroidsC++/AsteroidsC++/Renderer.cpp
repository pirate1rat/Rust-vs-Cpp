#include "Renderer.h"
#include "raymath.h"

void drawSprite(const SpriteStruct& prefab, Vector2 position, float rotation, Color color) {
	for (int i = 0; i < prefab.gLength; i++) {
		Vector2 p1 = transform(prefab.graphicPoints[i], position, rotation);
		Vector2 p2 = transform(prefab.graphicPoints[(i + 1) % prefab.gLength], position, rotation);
		DrawLineV(p1, p2, color);
	}

#ifdef DEBUG
	Vector2 p0, p1, p2, supportVec;
	for (int i = 0; i < prefab.hLength - 1; i++) {
		p1 = Vector2Add(prefab.hitboxPoints[i], position);
		supportVec = Vector2{ p1.x - position.x,
							  p1.y - position.y };
		supportVec = Vector2Rotate(supportVec, rotation);
		p1 = Vector2{ position.x + supportVec.x,
					  position.y + supportVec.y };

		p2 = Vector2Add(prefab.hitboxPoints[i + 1], position);
		supportVec = Vector2{ p2.x - position.x,
							  p2.y - position.y };
		supportVec = Vector2Rotate(supportVec, rotation);
		p2 = Vector2{ position.x + supportVec.x,
					  position.y + supportVec.y };
		DrawLineV(p1, p2, BLUE);
	}
	p0 = Vector2Add(prefab.hitboxPoints[0], position);
	supportVec = Vector2{ p0.x - position.x,
						  p0.y - position.y };
	supportVec = Vector2Rotate(supportVec, rotation);
	p0 = Vector2{ position.x + supportVec.x,
				  position.y + supportVec.y };
	DrawLineV(p2, p0, BLUE);


	DrawRectangleLines(WINDOW_WIDTH / 2 - SPAWNPOINT_SAFEZONE,
					WINDOW_HEIGHT / 2 - SPAWNPOINT_SAFEZONE,
		SPAWNPOINT_SAFEZONE * 2,
		SPAWNPOINT_SAFEZONE * 2,
		GREEN);
#endif // DEBUG

}
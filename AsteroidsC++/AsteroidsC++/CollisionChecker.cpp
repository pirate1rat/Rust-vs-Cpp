#include "CollisionChecker.h"

bool checkCollision(const SpriteStruct& prefabA, Vector2 posA, float rotA,
                    const SpriteStruct& prefabB, Vector2 posB, float rotB) {
	for (int i = 0; i < prefabA.hLength; i++) {
		Vector2 a = transform(prefabA.hitboxPoints[i], posA, rotA);
		Vector2 b = transform(prefabA.hitboxPoints[(i + 1) % prefabA.hLength], posA, rotA);
		for (int j = 0; j < prefabB.hLength; j++) {
			Vector2 c = transform(prefabB.hitboxPoints[j], posB, rotB);
			Vector2 d = transform(prefabB.hitboxPoints[(j + 1) % prefabB.hLength], posB, rotB);

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

	return false;
}
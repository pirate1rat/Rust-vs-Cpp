#pragma once
#include <raylib.h>

#define DEBUG

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int MARGIN = 30;

constexpr int SPAWNPOINT_SAFEZONE = 250; //spawnpoint for player

constexpr int MAX_ASTEROIDS = 7;
constexpr float MIN_ASTEROID_VELOCITY = 40.0f;
constexpr float MAX_ASTEROID_VELOCITY = 100.0f;

constexpr float EPS = 0.000001f;

constexpr float FORWARD = 1.0f;
constexpr float BACKWARD = -1.0f;
constexpr float LEFT = -1.0f;
constexpr float RIGHT = 1.0f;

constexpr Vector2 DEFAULT_UNIT_VECTOR = Vector2{ 0.0f, -1.0f };
constexpr Vector2 DEFAULT_POSITION = Vector2{ 0.0f, 0.0f };
constexpr float DEFAULT_ROTATION_UNIT = 2.0f;

constexpr float PLAYER_SHOT_TIMER = 0.5f;
constexpr float PLAYER_INVIOLABILITY_TIMER = 3.0f;
constexpr float PLAYER_ROTATION_UNIT = 2.0f;
constexpr float PLAYER_MAX_SPEED = 300.0f;
constexpr float PLAYER_ACCELERATION = 300.0f;

constexpr float PROJECTILE_SPEED = 500.0f;
constexpr float PROJECTILE_START_OFFSET = 10.0f;
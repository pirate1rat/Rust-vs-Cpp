use ggez::glam::Vec2;

pub const WINDOW_WIDTH: f32 = 800.0;
pub const WINDOW_HEIGHT: f32 = 600.0;
pub const MARGIN: f32 = 30.0;

pub const SPAWNPOINT_SAFEZONE: f32 = 200.0; // spawnpoint for player

pub const MAX_ASTEROIDS: usize = 7;
pub const MIN_ASTEROID_VELOCITY: f32 = 40.0;
pub const MAX_ASTEROID_VELOCITY: f32 = 100.0;

pub const EPS: f32 = 0.000_001;

pub const FORWARD: f32 = 1.0;
pub const BACKWARD: f32 = -1.0;
pub const LEFT: f32 = -1.0;
pub const RIGHT: f32 = 1.0;

pub const DEFAULT_UNIT_VECTOR: Vec2 = Vec2::new(0.0, -1.0);
pub const DEFAULT_POSITION: Vec2 = Vec2::ZERO;

pub const DEFAULT_ROTATION_UNIT: f32 = 2.0;

pub const PLAYER_SHOT_TIMER: f32 = 0.5;
pub const PLAYER_INVIOLABILITY_TIMER: f32 = 3.0;
pub const PLAYER_ROTATION_UNIT: f32 = 2.0;
pub const PLAYER_MAX_SPEED: f32 = 300.0;
pub const PLAYER_ACCELERATION: f32 = 300.0;

pub const PROJECTILE_SPEED: f32 = 500.0;
pub const PROJECTILE_START_OFFSET: f32 = 10.0;
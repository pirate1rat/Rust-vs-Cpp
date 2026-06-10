use ggez::glam::Vec2;
use rand::Rng;
use crate::entity::Entity;
use crate::sprites::{SpriteStruct, SpriteType};
use crate::{WINDOW_HEIGHT, WINDOW_WIDTH};
use crate::utils::rand_float;
use crate::constants::*;

enum AsteroidSize
{
    NONE,
    SMALL,
    MEDIUM,
    BIG
}

static BIG_SPLIT_INTO: [i32; 3] = [ 3, 4, 5 ]; // indexes for medium
static MEDIUM_SPLIT_INTO: [i32; 2] = [ 6, 7 ]; // indexes for small

struct AsteroidType {
    sprite: SpriteType,
    size: AsteroidSize,
    split_into: Option<&'static [i32]>,
}

static ASTEROID_TYPES: [AsteroidType; 8] = [
    AsteroidType { sprite: SpriteType::ASTEROID_BIG_1, size: AsteroidSize::BIG,    split_into: Some(&BIG_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::ASTEROID_BIG_2, size: AsteroidSize::BIG,    split_into: Some(&BIG_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::ASTEROID_BIG_3, size: AsteroidSize::BIG,    split_into: Some(&BIG_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::ASTEROID_MEDIUM_1, size: AsteroidSize::MEDIUM, split_into: Some(&MEDIUM_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::ASTEROID_MEDIUM_2, size: AsteroidSize::MEDIUM, split_into: Some(&MEDIUM_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::ASTEROID_MEDIUM_3, size: AsteroidSize::MEDIUM, split_into: Some(&MEDIUM_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::ASTEROID_SMALL_1, size: AsteroidSize::SMALL,  split_into: None },
    AsteroidType { sprite: SpriteType::ASTEROID_SMALL_2, size: AsteroidSize::SMALL,  split_into: None },
];
pub struct Asteroid {
    type_idx: usize,
    pub entity: Entity,
}

impl Asteroid {
    pub fn new(rng: &mut impl Rng, type_idx: usize) -> Self {
        let mut ent = Entity::new(ASTEROID_TYPES[type_idx].sprite.clone());
        let mut x_velocity: f32 = rand_float(rng, MIN_ASTEROID_VELOCITY, MAX_ASTEROID_VELOCITY);
        if rng.random_bool(0.5) {
            x_velocity = -x_velocity;
        }
        let mut y_velocity: f32 = rand_float(rng, MIN_ASTEROID_VELOCITY, MAX_ASTEROID_VELOCITY);
        if rng.random_bool(0.5) {
            y_velocity = -y_velocity;
        }
        ent.movement_vec = Vec2{x: x_velocity, y: y_velocity};

        let mut spawn_point: Vec2;
        loop {
            spawn_point = Vec2 {
                x: rand_float(rng, 0.0, WINDOW_WIDTH),
                y: rand_float(rng, 0.0, WINDOW_HEIGHT)
            };

            if ((spawn_point.x <= WINDOW_WIDTH/2.0 - SPAWNPOINT_SAFEZONE as f32) || (WINDOW_WIDTH/2.0 - SPAWNPOINT_SAFEZONE as f32 <= spawn_point.x))
                && ((spawn_point.y <= WINDOW_WIDTH/2.0 - SPAWNPOINT_SAFEZONE as f32) || (WINDOW_WIDTH/2.0 - SPAWNPOINT_SAFEZONE as f32 <= spawn_point.y)) {
                break;
            }
        }

        ent.reposition(spawn_point);

        Asteroid {
            type_idx,
            entity: ent,
        }
    }
}
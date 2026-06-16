use ggez::glam::Vec2;
use rand::Rng;
use crate::entity::{Entity, GameEntity};
use crate::sprites::{SpriteType, SPRITES};
use crate::{WINDOW_HEIGHT, WINDOW_WIDTH};
use crate::constants::*;

static BIG_SPLIT_INTO: [i32; 3] = [ 3, 4, 5 ]; // indexes for medium
static MEDIUM_SPLIT_INTO: [i32; 2] = [ 6, 7 ]; // indexes for small

pub struct AsteroidType {
    sprite: SpriteType,
    size: AsteroidSize,
    split_into: Option<&'static [i32]>,
}

#[derive(Debug, Clone)]
pub enum AsteroidSize{
    Big,
    Medium,
    Small
}

pub static ASTEROID_TYPES: [AsteroidType; 8] = [
    AsteroidType { sprite: SpriteType::AsteroidBig1,    size: AsteroidSize::Big, split_into: Some(&BIG_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::AsteroidBig2,    size: AsteroidSize::Big, split_into: Some(&BIG_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::AsteroidBig3,    size: AsteroidSize::Big, split_into: Some(&BIG_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::AsteroidMedium1, size: AsteroidSize::Medium, split_into: Some(&MEDIUM_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::AsteroidMedium2, size: AsteroidSize::Medium, split_into: Some(&MEDIUM_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::AsteroidMedium3, size: AsteroidSize::Medium, split_into: Some(&MEDIUM_SPLIT_INTO) },
    AsteroidType { sprite: SpriteType::AsteroidSmall1,  size: AsteroidSize::Small, split_into: None },
    AsteroidType { sprite: SpriteType::AsteroidSmall2,  size: AsteroidSize::Small, split_into: None },
];

#[derive(Debug)]
pub struct Asteroid {
    type_idx: usize,
    pub size: AsteroidSize,
    pub entity: Entity,
}

impl GameEntity for Asteroid {
    fn entity(&self) -> &Entity {
        &self.entity
    }

    fn entity_mut(&mut self) -> &mut Entity {
        &mut self.entity
    }
}

impl Asteroid {
    pub fn new(rng: &mut impl Rng, type_idx: usize) -> Self {
        let mut ent = Entity::new(ASTEROID_TYPES[type_idx].sprite.clone());
        let mut x_velocity: f32 = rng.random_range(MIN_ASTEROID_VELOCITY..MAX_ASTEROID_VELOCITY);
        if rng.random_bool(0.5) {
            x_velocity = -x_velocity;
        }
        let mut y_velocity: f32 = rng.random_range(MIN_ASTEROID_VELOCITY..MAX_ASTEROID_VELOCITY);
        if rng.random_bool(0.5) {
            y_velocity = -y_velocity;
        }
        ent.movement_vec = Vec2{x: x_velocity, y: y_velocity};

        let mut spawn_point: Vec2;
        loop {
            spawn_point = Vec2 {
                x: rng.random_range(0.0..WINDOW_WIDTH),
                y: rng.random_range(0.0..WINDOW_HEIGHT)
            };

            if !(((WINDOW_WIDTH/2.0 - SPAWNPOINT_SAFEZONE <= spawn_point.x) && (spawn_point.x <= WINDOW_WIDTH/2.0 + SPAWNPOINT_SAFEZONE))
                && ((WINDOW_WIDTH/2.0 - SPAWNPOINT_SAFEZONE <= spawn_point.y) && (spawn_point.y <= WINDOW_WIDTH/2.0 + SPAWNPOINT_SAFEZONE))) {
                break;
            }
        }

        ent.reposition(spawn_point);

        Asteroid {
            type_idx,
            size: ASTEROID_TYPES[type_idx].size.clone(),
            entity: ent,
        }
    }

    pub fn split(&mut self, rng: &mut impl Rng) -> Option<Asteroid> {
        let t: &AsteroidType = &ASTEROID_TYPES[self.type_idx];

        match &t.split_into {
            Some(split_into) => {
                let idx = rng.random_range(0..split_into.len());
                let child_type_idx = split_into[idx] as usize;
                let idx = rng.random_range(0..split_into.len());
                self.type_idx = split_into[idx] as usize;
                self.entity.prefab = &SPRITES[ASTEROID_TYPES[self.type_idx].sprite.clone().idx()];
                let mut child: Asteroid = Asteroid::new(rng, child_type_idx);
                child.entity.position = self.entity.position;
                Some(child)
            }
            None => {
                self.entity.alive = false;
                return None;
            }
        }
    }
}
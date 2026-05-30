use ggez::glam::Vec2;
use ggez::graphics::Color;
use rand::Rng;
use crate::entity::Entity;
use crate::sprites::SpriteStruct;
use crate::{WINDOW_HEIGHT, WINDOW_WIDTH};

pub struct Asteroid {
    pub entity: Entity,
}

impl Asteroid {
    pub fn new(rng: &mut impl Rng, prefab: &'static SpriteStruct) -> Self {
        let ent = Entity{
            position: Vec2{ x: 0.0, y: 2.5 },
            prefab: prefab,

            rotation: 0.0,
            movement_vec: Vec2{
                x: Entity::rand_float(rng, -1.0, 1.0),
                y: Entity::rand_float(rng, -1.0, 1.0)
            },
            default_color: Color::WHITE,
        };

        let mut asteroid = Asteroid {
            entity: ent,
        };

        asteroid.entity.reposition(
            Vec2 {
                x: Entity::rand_float(rng, 0.0, WINDOW_WIDTH),
                y: Entity::rand_float(rng, 0.0, WINDOW_HEIGHT)
            }
        );
        asteroid
    }
}
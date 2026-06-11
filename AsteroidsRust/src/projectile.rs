use ggez::glam::Vec2;
use crate::constants::{MARGIN, WINDOW_HEIGHT, WINDOW_WIDTH};
use crate::entity::{Entity, GameEntity};
use crate::sprites::SpriteType;

#[derive(Debug)]
pub struct Projectile {
    pub entity: Entity
}

impl GameEntity for Projectile {
    fn entity(&self) -> &Entity {
        &self.entity
    }

    fn entity_mut(&mut self) -> &mut Entity {
        &mut self.entity
    }

    fn move_entity(&mut self, delta_time: f32) {
        self.entity.position += self.entity.movement_vec * delta_time;

        if self.entity.position.x < -MARGIN {
            self.entity.alive = false;
        } else if (WINDOW_WIDTH + MARGIN) < self.entity.position.x {
            self.entity.alive = false;
        }

        if self.entity.position.y < -MARGIN {
            self.entity.alive = false;
        } else if WINDOW_HEIGHT + MARGIN < self.entity.position.y {
            self.entity.alive = false;
        }
    }
}

impl Projectile {
    pub fn new(position: Vec2, velocity: Vec2) -> Self {
        let mut entity = Entity::new(SpriteType::Projectile);
        entity.position = position;
        entity.movement_vec = velocity;
        Projectile { entity }
    }
}
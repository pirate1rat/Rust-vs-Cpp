use ggez::glam::Vec2;
use crate::constants::{MARGIN, WINDOW_HEIGHT, WINDOW_WIDTH};
use crate::entity::Entity;

pub struct Projectile {
    pub entity: Entity
}

impl Projectile {
    pub fn move_entity(&mut self, delta_time: f32) {
        self.entity.position += self.entity.movement_vec * delta_time;

        if self.entity.position.x < -MARGIN as f32 {
            self.entity.alive = false;
        }
        else if ((WINDOW_WIDTH + MARGIN) as f32) < self.entity.position.x {
            self.entity.alive = false;
        }

        if self.entity.position.y < -MARGIN as f32 {
            self.entity.alive = false;
        }
        else if ((WINDOW_HEIGHT + MARGIN) as f32) < self.entity.position.y {
            self.entity.alive = false;
        }
    }
}
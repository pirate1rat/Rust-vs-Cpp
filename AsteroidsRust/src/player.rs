use crate::entity::{Entity, GameEntity};
use ggez::glam::{Vec2};
use crate::constants::*;
use crate::projectile::Projectile;
use crate::sprites::{SpriteType, SPRITES};

#[derive(Debug)]
pub struct Player{
    pub entity: Entity,
    max_movement_vec_length: f32,
    acceleration: f32,
    acceleration_direction: f32,
    ////
    start_position: Vec2
}

impl GameEntity for Player {
    fn entity(&self) -> &Entity {
        &self.entity
    }

    fn entity_mut(&mut self) -> &mut Entity {
        &mut self.entity
    }
}

impl Player{
    pub fn new(window_center: Vec2, sprite: SpriteType) -> Player {
        Player {
            entity: Entity {
                prefab: &SPRITES[SpriteType::Player.idx()],
                position: window_center + Vec2 { x: 0.0, y: -2.5 },
                ..Default::default()
            },
            max_movement_vec_length: PLAYER_MAX_SPEED,
            acceleration: PLAYER_ACCELERATION,
            acceleration_direction: FORWARD,
            start_position: window_center + Vec2 { x: 0.0, y: -2.5 }
        }
    }

    pub fn change_velocity(&mut self, acceleration_direction: f32, delta_time: f32) {
        if acceleration_direction == BACKWARD && self.entity.movement_vec == Vec2::ZERO {
            return;
        }

        if self.acceleration_direction != acceleration_direction {
            self.acceleration_direction = acceleration_direction;
        }
        let current_acceleration = self.acceleration * self.acceleration_direction;

        let forward_unit_vec = self.entity.direction_unit_vec * current_acceleration;
        let new_movement_vec: Vec2 = self.entity.movement_vec + (forward_unit_vec * delta_time);
        if new_movement_vec.dot(self.entity.movement_vec) < 0.0 {
            self.entity.movement_vec = Vec2::ZERO;
        }
        else if new_movement_vec.length() <= self.max_movement_vec_length {
            self.entity.movement_vec = new_movement_vec;
        }
    }

    pub fn shoot_projectile(&self) -> Projectile {
        let start = self.entity.position + self.entity.direction_unit_vec * PROJECTILE_START_OFFSET;
        let speed = self.entity.direction_unit_vec * PROJECTILE_SPEED;
        Projectile::new(start, speed)
    }

    pub fn respawn(&mut self) {
        self.entity.position = self.start_position;
        self.entity.movement_vec = Vec2::ZERO;
        self.entity.direction_unit_vec = DEFAULT_UNIT_VECTOR;
        self.entity.rotation = 0.0;
    }
}
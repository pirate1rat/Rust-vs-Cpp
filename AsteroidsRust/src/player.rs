use std::ops::Neg;
use crate::entity::Entity;

use ggez::glam::{Mat2, Vec2};
use ggez::graphics::Color;
use crate::constants::{BACKWARD, FORWARD};
use crate::sprites::SpriteStruct;

pub struct Player{
    pub(crate) entity: Entity,
    acceleration_vec: Vec2,
    rotation_unit: f32,
    max_movement_vec_length: f32,
    acceleration_direction: f32
}

impl Player{
    pub fn new(window_center: Vec2, prefab: &'static SpriteStruct) -> Player {
        let ent = Entity{
            position: Vec2{ x: 0.0, y: 2.5 },
            prefab: prefab,

            rotation: 0.0,
            movement_vec: Vec2{ x: 0.0, y: 0.0},
            default_color: Color::WHITE,
        };

        let mut player = Player {
            entity: ent,
            acceleration_vec: Vec2{ x: 0.0, y: -0.5 },
            rotation_unit: 0.1,
            max_movement_vec_length: 5.0,
            acceleration_direction: FORWARD
        };
        player.entity.reposition(window_center);
        player
    }

    pub fn rotate(&mut self, rotation_direction: f32) {
        let r: f32 = self.rotation_unit * rotation_direction;
        self.entity.rotation += r;
        let rot = Mat2::from_angle(r);
        self.entity.movement_vec = rot * self.entity.movement_vec;
        self.acceleration_vec = rot * self.acceleration_vec;
    }

    pub fn change_velocity(&mut self, acceleration_direction: f32) {
        if acceleration_direction == BACKWARD && self.entity.movement_vec == Vec2::ZERO {
            return;
        }

        if self.acceleration_direction != acceleration_direction {
            self.acceleration_direction = acceleration_direction;
            self.acceleration_vec = -self.acceleration_vec;
        }

        let new_movement_vec: Vec2 = self.entity.movement_vec + self.acceleration_vec;
        if new_movement_vec.dot(self.entity.movement_vec) < 0.0 {
            self.entity.movement_vec = Vec2::ZERO;
        }
        else if new_movement_vec.length() <= self.max_movement_vec_length {
            self.entity.movement_vec = new_movement_vec;
        }
    }
}
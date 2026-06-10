use ggez::{Context, GameResult};
use ggez::glam::{Mat2, Vec2};
use ggez::graphics::{Canvas, Color};
use crate::collision_checker::check_collision;
use crate::sprites::{SpriteStruct, SpriteType, SPRITES};
use crate::constants::*;
use crate::renderer::draw_sprite;


pub struct Entity {
    pub prefab: &'static SpriteStruct,
    pub direction_unit_vec: Vec2,
    pub movement_vec: Vec2,
    pub position: Vec2,
    pub rotation: f32,
    pub rotation_unit: f32,
    pub alive: bool,
    pub default_color: Color,
}

impl Entity {
    pub fn new(sprite: SpriteType) -> Self {
        Entity{
            prefab: &SPRITES[sprite.idx()],
            direction_unit_vec: DEFAULT_UNIT_VECTOR,
            movement_vec: Vec2::ZERO,
            position: Vec2::ZERO,
            rotation: 0.0,
            rotation_unit: DEFAULT_ROTATION_UNIT,
            alive: true,
            default_color: Color::WHITE,
        }
    }

    //////getters/setters
    pub fn get_position(&self) -> Vec2 {
        self.position
    }
    //////////

    pub fn reposition(&mut self, reposition_vec: Vec2) {
        self.position += reposition_vec;
    }

    pub fn move_entity(&mut self, delta_time: f32) {
        self.position += self.movement_vec * delta_time;

        if self.position.x < -MARGIN as f32 {
            self.reposition(Vec2{x: (WINDOW_WIDTH + 2 * MARGIN) as f32, y: 0.0});
        }
        else if ((WINDOW_WIDTH + MARGIN) as f32) < self.position.x {
            self.reposition(Vec2{x: (-WINDOW_WIDTH - 2 * MARGIN) as f32, y: 0.0});
        }

        if self.position.y < -MARGIN as f32 {
            self.reposition(Vec2{y: (WINDOW_HEIGHT + 2 * MARGIN) as f32, x: 0.0});
        }
        else if ((WINDOW_HEIGHT + MARGIN) as f32) < self.position.y {
            self.reposition(Vec2{y: (-WINDOW_HEIGHT - 2 * MARGIN) as f32, x: 0.0});
        }
    }

    pub fn rotate(&mut self, rotation_direction: f32, delta_time: f32) {
        let r: f32 = self.rotation_unit * rotation_direction * delta_time;
        self.rotation += r;
        let rot = Mat2::from_angle(r);
        self.movement_vec = rot * self.movement_vec;
        self.direction_unit_vec = rot * self.direction_unit_vec;
    }

    pub fn draw(&self, ctx: &mut Context, canvas: &mut Canvas) -> GameResult {
        draw_sprite(ctx, canvas, self.prefab, self.position, self.rotation, self.default_color)
    }

    pub fn check_collision(&self, other: &Entity) -> bool {
        check_collision(self.prefab, self.position, self.rotation, other.prefab, other.position, other.rotation)
    }
}
use ggez::{Context, GameResult};
use ggez::glam::{Vec2};
use ggez::graphics::{Canvas, Color};
use crate::collision_checker::check_collision;
use crate::sprites::{SpriteStruct, SpriteType, SPRITES};
use crate::constants::*;
use crate::renderer::draw_sprite;


pub struct Entity {
    pub prefab: &'static SpriteStruct,
    pub movement_vec: Vec2,
    pub position: Vec2,
    pub rotation: f32,
    pub default_color: Color,
}

impl Entity {
    pub fn new(sprite: SpriteType) -> Self {
        Entity{
            prefab: &SPRITES[sprite.idx()],
            movement_vec: Vec2{ x: 0.0, y: 0.0},
            position: Vec2{ x: 0.0, y: 0.0},
            rotation: 0.0,
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

    pub fn move_entity(&mut self) {
        self.position += self.movement_vec;

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

    pub fn draw(&self, ctx: &mut Context, canvas: &mut Canvas) -> GameResult {
        draw_sprite(ctx, canvas, self.prefab, self.position, self.rotation, self.default_color)
    }

    pub fn check_collision(&self, other: &Entity) -> bool {
        check_collision(self.prefab, self.position, self.rotation, other.prefab, other.position, other.rotation)
    }
}
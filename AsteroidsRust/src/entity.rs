use ggez::{Context, GameResult};
use ggez::glam::{Mat2, Vec2};
use ggez::graphics::{Canvas, Color, DrawParam, Mesh};
use rand::{Rng};
use crate::sprites::{SpriteStruct};
use crate::constants::*;

pub struct Entity {
    pub prefab: &'static SpriteStruct,
    pub movement_vec: Vec2,
    pub position: Vec2,
    pub rotation: f32,
    pub default_color: Color,
}

impl Entity {
    pub fn new(prefab: &'static SpriteStruct) -> Self {
        Entity{
            prefab,
            movement_vec: Vec2{ x: 0.0, y: 0.0},
            position: Vec2{ x: 0.0, y: 0.0},
            rotation: 0.0,
            default_color: Color::WHITE,
        }
    }

    //////getters/setters
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
        let self_length = self.prefab.g_points.len();
        for (i, point) in self.prefab.g_points.iter().enumerate() {
            let p1 = self.transform(self.prefab.g_points[i]);
            let p2 = self.transform(self.prefab.g_points[(i+1)%self_length]);
            let line = Mesh::new_line(
                ctx,
                &[ p1, p2 ],
                1.0,
                self.default_color,
            )?;

            canvas.draw(&line, DrawParam::default());
        }
        Ok(())
    }

    pub fn check_collision(&self, other: &Entity) -> bool {
        let self_length = self.prefab.h_points.len();
        let other_length = other.prefab.h_points.len();
        for (i, _) in self.prefab.h_points.iter().enumerate() {
            let a: Vec2 = self.transform(self.prefab.h_points[i]);
            let b: Vec2 = self.transform(self.prefab.h_points[(i+1)%self_length]);
            for (j, _) in other.prefab.h_points.iter().enumerate() {
                let c: Vec2 = other.transform(other.prefab.h_points[j]);
                let d: Vec2 = other.transform(other.prefab.h_points[(j+1)%other_length]);

                let d1 = Self::cross(a, b, c);
                let d2 = Self::cross(a, b, d);
                let d3 = Self::cross(c, d, a);
                let d4 = Self::cross(c, d, b);

                if (d1 > 0.0 && d2 < 0.0 || d1 < 0.0 && d2 > 0.0) &&
                    (d3 > 0.0 && d4 < 0.0 || d3 < 0.0 && d4 > 0.0) {
                    return true
                }

                if d1.abs() < EPS && Self::on_segment(a, b, c) { return true };
                if d2.abs() < EPS && Self::on_segment(a, b, d) { return true };
                if d3.abs() < EPS && Self::on_segment(c, d, a) { return true };
                if d4.abs() < EPS && Self::on_segment(c, d, b) { return true };
            }
        }

        false
    }

    ///////
    pub fn rand_float(rng: &mut impl Rng, min: f32, max: f32) -> f32 {
        rng.random_range(min..max)
    }

    fn cross(a: Vec2, b: Vec2, c: Vec2) -> f32 {
        (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)
    }

    fn on_segment(a: Vec2, b: Vec2, p: Vec2) -> bool {
        a.x.min(b.x) <= p.x && p.x <= a.x.max(b.x)
        && a.y.min(b.y) <= p.y && p.y <= a.y.max(b.y)
    }

    fn transform(&self, p: Vec2) -> Vec2 {
        let p: Vec2 = p + self.position;
        let support_vec: Vec2 = Vec2{
            x: p.x - self.position.x,
            y: p.y - self.position.y,
        };
        let rot = Mat2::from_angle(self.rotation);
        let support_vec: Vec2 = rot * support_vec;
        Vec2{
            x: self.position.x + support_vec.x,
            y: self.position.y + support_vec.y,
        }
    }


}
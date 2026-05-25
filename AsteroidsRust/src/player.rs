use crate::entity::Entity;

use ggez::{Context, GameResult};
use ggez::glam::{Mat2, Vec2};
use ggez::graphics::{Canvas, Color, DrawParam, Mesh};



pub struct Player{
    points: [Vec2; 4],
    center_of_gravity: Vec2,
    movement_vec: Vec2,
    rotation: f32,
	player_color: Color
}

impl Player{
    pub fn new(window_center: Vec2) -> Player {
        let base_points = [
            Vec2{ x: 0.0, y: -16.0 },
            Vec2{ x: -8.0, y: 14.0 },
            Vec2{ x: 0.0, y: 9.5 },
            Vec2{ x: 8.0, y: 14.0 },
        ];
        let points = base_points.map(|p| Vec2{
            x: p.x + window_center.x, y: p.y + window_center.y
        });

        let base_center: Vec2 = Vec2{ x: 0.0, y: 2.5 };
        let center_of_gravity = base_center + window_center;

        Player {
            points: points,
            center_of_gravity: center_of_gravity,
            movement_vec: Vec2{ x: 0.0, y: -7.0 },
            rotation: 0.07,
            player_color: Color::WHITE,
        }
    }

    pub fn draw(&self, ctx: &mut Context, canvas: &mut Canvas) -> GameResult {
        for (i, _) in self.points.iter().enumerate() {
            let line = Mesh::new_line(
                ctx,
                &[
                    self.points[i],
                    self.points[(i + 1) % self.points.len()],
                ],
                1.0,
                self.player_color,
            )?;

            canvas.draw(&line, DrawParam::default());
        }

        Ok(())
    }

    pub fn reposition(&mut self) -> GameResult {
        for p in self.points.iter_mut(){
            p.x += self.movement_vec.x;
            p.y += self.movement_vec.y;
        }
        self.center_of_gravity += self.movement_vec;
        Ok(())
    }

    pub fn rotate(&mut self, rotationDirection: i8) -> GameResult {
        let current_rotation: f32 = self.rotation * rotationDirection as f32;
        let rot = Mat2::from_angle(current_rotation);

        self.movement_vec = rot * self.movement_vec;

        for p in self.points.iter_mut(){
            let support_vec = Vec2{
                x: p.x - self.center_of_gravity.x,
                y: p.y - self.center_of_gravity.y
            };
            let support_vec = rot * support_vec;

            p.x = self.center_of_gravity.x + support_vec.x;
            p.y = self.center_of_gravity.y + support_vec.y;
        }

        Ok(())
    }
}
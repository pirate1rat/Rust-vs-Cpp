use ggez::{graphics, Context, GameResult};
use ggez::event::EventHandler;
use ggez::glam::Vec2;
use ggez::graphics::Color;
use ggez::input::keyboard::KeyCode;
use rand::prelude::ThreadRng;
use rand::Rng;
use crate::asteroid::{Asteroid, ASTEROID_TYPES};
use crate::constants::{BACKWARD, FORWARD, LEFT, MAX_ASTEROIDS, PLAYER_SHOT_TIMER, RIGHT};
use crate::player::Player;
use crate::sprites::{SpriteType, SPRITES};
use crate::{WINDOW_HEIGHT, WINDOW_WIDTH};
use crate::entity::GameEntity;
use crate::projectile::Projectile;

pub struct Game {
    player: Player,
    asteroids: Vec<Asteroid>,
    projectiles: Vec<Projectile>,
    rng: ThreadRng,
    shot_timer: f32
}

impl Game {
    pub fn new(_ctx: &mut Context) -> Game {
        let mut rng = rand::rng();
        let mut asteroids: Vec<Asteroid> = Vec::new();
        let num_of_asteroids: i32 = rng.random_range(1..=MAX_ASTEROIDS as i32) + 4;

        for i in 0..num_of_asteroids {
            let asteroid_type = rng.random_range(0..ASTEROID_TYPES.len());
            asteroids.push(
                Asteroid::new(
                    &mut rng,
                    asteroid_type
                )
            );
        }

        Game {
            player: Player::new(
                Vec2{x: WINDOW_WIDTH/2.0, y: WINDOW_HEIGHT/2.0},
                SpriteType::Player
            ),
            asteroids,
            projectiles: Vec::new(),
            rng,
            shot_timer: 0.0,
        }
    }

    fn update_entities(&mut self, delta_time: f32) -> GameResult {
        for asteroid in self.asteroids.iter_mut() {
            asteroid.move_entity(delta_time);
        }
        for projectile in self.projectiles.iter_mut() {
            projectile.move_entity(delta_time);
        }
        self.player.move_entity(delta_time);
        Ok(())
    }

    fn handle_input(&mut self, ctx: &mut Context, delta_time: f32) -> GameResult {
        if ctx.keyboard.is_key_pressed(KeyCode::Up) {
            self.player.change_velocity(FORWARD, delta_time);
        }
        if ctx.keyboard.is_key_pressed(KeyCode::Down) {
            self.player.change_velocity(BACKWARD, delta_time);
        }
        if ctx.keyboard.is_key_pressed(KeyCode::Left) {
            self.player.rotate(LEFT, delta_time);
        }
        if ctx.keyboard.is_key_pressed(KeyCode::Right) {
            self.player.rotate(RIGHT, delta_time);
        }
        if ctx.keyboard.is_key_pressed(KeyCode::Space) && self.shot_timer <= 0f32 {
            self.shot_timer = PLAYER_SHOT_TIMER;
            self.projectiles.push(self.player.shoot_projectile());
            println!("piuu\n");
        }
        Ok(())
    }

    fn handle_collision(&mut self) -> GameResult {
        for asteroid in self.asteroids.iter() {
            if self.player.check_collision(asteroid) {
                println!("kolizja! {:?}", asteroid.entity.position);
            }
        }
        let mut new_asteroids: Vec<Asteroid> = Vec::new();
        for projectile in self.projectiles.iter_mut(){
            for asteroid in self.asteroids.iter_mut(){
                if projectile.check_collision(asteroid) {
                    projectile.entity.alive = false;
                    if let Some(asteroid) = asteroid.split(&mut self.rng) {
                        new_asteroids.push(asteroid);
                    }
                }
            }
        }
        self.asteroids.extend(new_asteroids);
        Ok(())
    }

    fn cleanup(&mut self) -> GameResult {
        self.asteroids.retain(|asteroid| asteroid.is_alive());
        self.projectiles.retain(|projectile| projectile.is_alive());
        Ok(())
    }
}

impl EventHandler for Game {
    fn update(&mut self, ctx: &mut Context) -> GameResult {
        let dt = ctx.time.delta().as_secs_f32();
        self.shot_timer -= dt;

        self.handle_input(ctx, dt)?;
        self.update_entities(dt)?;
        self.handle_collision()?;
        self.cleanup()?;

        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);
        self.player.draw(ctx, &mut canvas)?;

        for asteroid in self.asteroids.iter() {
            asteroid.draw(ctx, &mut canvas)?;
        }
        for projectile in self.projectiles.iter() {
            projectile.draw(ctx, &mut canvas)?;
        }

        canvas.finish(ctx)?;

        Ok(())
    }
}
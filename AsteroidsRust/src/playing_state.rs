use std::fmt::format;
use ggez::{graphics, Context, GameResult};
use ggez::event::EventHandler;
use ggez::glam::Vec2;
use ggez::graphics::{Color, DrawParam, Text, TextFragment};
use ggez::input::keyboard::KeyCode;
use rand::prelude::ThreadRng;
use rand::Rng;
use crate::app::{GameState, Transition};
use crate::asteroid::{Asteroid, AsteroidSize, ASTEROID_TYPES};
use crate::constants::*;
use crate::player::Player;
use crate::sprites::{SpriteType, SPRITES};
use crate::{WINDOW_HEIGHT, WINDOW_WIDTH};
use crate::entity::GameEntity;
use crate::name_entry_state::NameEntryState;
use crate::projectile::Projectile;

pub struct PlayingState {
    player: Player,
    asteroids: Vec<Asteroid>,
    projectiles: Vec<Projectile>,
    rng: ThreadRng,
    shot_timer: f32,
    inviolability_timer: f32,
    
    points: i32,
    extra_lives: i32,
}

impl PlayingState {
    pub fn new() -> PlayingState {
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

        PlayingState {
            player: Player::new(
                Vec2{x: WINDOW_WIDTH/2.0, y: WINDOW_HEIGHT/2.0},
                SpriteType::Player
            ),
            asteroids,
            projectiles: Vec::new(),
            rng,
            shot_timer: 0.0,
            inviolability_timer: 0.0,
            points: 0,
            extra_lives: 2,
        }
    }

    fn update_entities(&mut self, delta_time: f32) {
        for asteroid in self.asteroids.iter_mut() {
            asteroid.move_entity(delta_time);
        }
        for projectile in self.projectiles.iter_mut() {
            projectile.move_entity(delta_time);
        }
        self.player.move_entity(delta_time);
    }

    fn handle_input(&mut self, ctx: &mut Context, delta_time: f32) {
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
        }
    }

    fn handle_collision(&mut self) -> bool {
        for asteroid in self.asteroids.iter() {
            if self.player.check_collision(asteroid) && self.inviolability_timer <= 0f32 {
                if self.extra_lives == 0 {
                    return true
                }
                else {
                    self.extra_lives -= 1;
                    self.inviolability_timer = PLAYER_INVIOLABILITY_TIMER;
                    self.player.respawn();
                }
            }
        }
        let mut new_asteroids: Vec<Asteroid> = Vec::new();
        for projectile in self.projectiles.iter_mut(){
            for asteroid in self.asteroids.iter_mut(){
                if projectile.check_collision(asteroid) {
                    match asteroid.size {
                        AsteroidSize::Big => { self.points += 10 }
                        AsteroidSize::Medium => { self.points += 15 }
                        AsteroidSize::Small => { self.points += 20 }
                    }
                    
                    projectile.entity.alive = false;
                    if let Some(asteroid) = asteroid.split(&mut self.rng) {
                        new_asteroids.push(asteroid);
                    }
                }
            }
        }
        self.asteroids.extend(new_asteroids);
        false
    }

    fn cleanup(&mut self) {
        self.asteroids.retain(|asteroid| asteroid.is_alive());
        self.projectiles.retain(|projectile| projectile.is_alive());

        if self.asteroids.is_empty() {
            let previous_points = self.points;
            let previous_lives = self.extra_lives;
            *self = PlayingState::new();
            self.points = previous_points;
            self.extra_lives = previous_lives;
        }
    }

    pub fn update(&mut self, ctx: &mut Context) -> Transition {
        let dt = 1.0 / 60.0;
        self.shot_timer -= dt;
        self.inviolability_timer -= dt;

        self.handle_input(ctx, dt);
        self.update_entities(dt);
        if self.handle_collision() {
            return Transition::ToState(GameState::NameEntry(NameEntryState::new(self.points)))
        }
        self.cleanup();

        Transition::None
    }

    pub fn draw(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);
        self.player.draw(ctx, &mut canvas);

        for asteroid in self.asteroids.iter() {
            asteroid.draw(ctx, &mut canvas);
        }
        for projectile in self.projectiles.iter() {
            projectile.draw(ctx, &mut canvas);
        }

        let lifes_text = Text::new(TextFragment::new(format!("extra lives: {}", self.extra_lives)).scale(20.0));
        let points_text = Text::new(TextFragment::new(format!("points: {}", self.points)).scale(20.0));
        let x = points_text.measure(ctx)?.x;
        canvas.draw(&lifes_text, DrawParam::default().dest([20.0, 20.0]));
        canvas.draw(&points_text, DrawParam::default().dest([WINDOW_WIDTH - x - 20.0, 20.0]));

        canvas.finish(ctx)?;
        
        Ok(())
    }
}
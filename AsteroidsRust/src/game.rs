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
                SpriteType::PLAYER
            ),
            asteroids,
            projectiles: Vec::new(),
            rng,
            shot_timer: 0.0,
        }
    }
}

impl EventHandler for Game {
    fn update(&mut self, _ctx: &mut Context) -> GameResult {
        let dt = _ctx.time.delta().as_secs_f32();
        self.shot_timer -= dt;

        if _ctx.keyboard.is_key_pressed(KeyCode::Up) {
            self.player.change_velocity(FORWARD, dt);
        }
        if _ctx.keyboard.is_key_pressed(KeyCode::Down) {
            self.player.change_velocity(BACKWARD, dt);
        }
        if _ctx.keyboard.is_key_pressed(KeyCode::Left) {
            self.player.entity.rotate(LEFT, dt);
        }
        if _ctx.keyboard.is_key_pressed(KeyCode::Right) {
            self.player.entity.rotate(RIGHT, dt);
        }
        if _ctx.keyboard.is_key_pressed(KeyCode::Space) && self.shot_timer <= 0f32 {
            self.shot_timer = PLAYER_SHOT_TIMER;
            self.projectiles.push(self.player.shoot_projectile());
            println!("piuu\n");
        }

        //updating entities
        for mut asteroid in self.asteroids.iter_mut() {
            asteroid.entity.move_entity(dt);
        }
        for mut projectile in self.projectiles.iter_mut() {
            projectile.move_entity(dt);
        }
        self.player.entity.move_entity(dt);

        //checking collision
        for asteroid in self.asteroids.iter() {
            if self.player.entity.check_collision(&asteroid.entity) {
                println!("kolizja! {:?}", asteroid.entity.position);
            }
        }
        let mut new_asteroids: Vec<Asteroid> = Vec::new();
        for mut projectile in self.projectiles.iter_mut(){
            for mut asteroid in self.asteroids.iter_mut(){
                if projectile.entity.check_collision(&asteroid.entity) {
                    projectile.entity.alive = false;
                    let split_asteroid = asteroid.split(&mut self.rng);
                    if split_asteroid.is_some() {
                        new_asteroids.push(split_asteroid.unwrap());
                    }
                }
            }
        }
        self.asteroids.extend(new_asteroids);

        //clearing
        self.asteroids.retain(|asteroid| asteroid.entity.alive);
        self.projectiles.retain(|projectile| projectile.entity.alive);

        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);
        self.player.entity.draw(ctx, &mut canvas).expect("TODO: panic message");

        for asteroid in self.asteroids.iter() {
            asteroid.entity.draw(ctx, &mut canvas).expect("TODO: panic message");
        }
        for projectile in self.projectiles.iter() {
            projectile.entity.draw(ctx, &mut canvas).expect("TODO: panic message");
        }

        canvas.finish(ctx)?;

        Ok(())
    }
}
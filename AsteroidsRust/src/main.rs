mod player;
mod entity;
mod sprites;
mod constants;
mod asteroid;
mod renderer;
mod collision_checker;
mod utils;

use ggez::{Context, ContextBuilder, GameResult};
use ggez::conf::WindowMode;
use ggez::graphics::{self, Color};
use ggez::event::{self, EventHandler};
use ggez::glam::Vec2;
use ggez::input::keyboard::{self, KeyCode};
use rand::prelude::ThreadRng;
use rand::Rng;
use crate::constants::*;
use player::Player;
use crate::sprites::{SpriteType, SPRITES};
use asteroid::Asteroid;

const WINDOW_WIDTH: f32 = 800.0;
const WINDOW_HEIGHT: f32 = 600.0;

fn main() {
    // Make a Context.
    let (mut ctx, event_loop) = ContextBuilder::new("my_game", "Cool Game Author")
        .window_mode(WindowMode {
            width: WINDOW_WIDTH,
            height: WINDOW_HEIGHT,
            ..Default::default()
        })
        .build()
        .expect("aieee, could not create ggez context!");

    // Create an instance of your event handler.
    // Usually, you should provide it with the Context object to
    // use when setting your game up.
    let my_game = MyGame::new(&mut ctx);

    // Run!
    event::run(ctx, event_loop, my_game);
}

struct MyGame {
    player: Player,
    asteroids: Vec<Asteroid>,
    rng: ThreadRng
}

impl MyGame {
    pub fn new(_ctx: &mut Context) -> MyGame {
        let mut rng = rand::rng();

        // Load/create resources such as images here.
        let mut asteroids: Vec<Asteroid> = Vec::new();
        let num_of_asteroids: i32 = rng.random_range(1..=MAX_ASTEROIDS) + 4;

        for i in 0..num_of_asteroids {
            let sprite = SpriteType::random(&mut rng);
            asteroids.push(
                Asteroid::new(
                    &mut rng,
                    &SPRITES[sprite.idx()]
                )
            );
        }

        MyGame {
            player: Player::new(
                Vec2{x: WINDOW_WIDTH/2.0, y: WINDOW_HEIGHT/2.0},
                &SPRITES[SpriteType::PLAYER.idx()]
            ),
            asteroids,
            rng
        }
    }
}

impl EventHandler for MyGame {
    fn update(&mut self, _ctx: &mut Context) -> GameResult {

        if _ctx.keyboard.is_key_pressed(KeyCode::Up) {
            self.player.change_velocity(FORWARD);
        }
        if _ctx.keyboard.is_key_pressed(KeyCode::Down) {
            self.player.change_velocity(BACKWARD);
        }
        if _ctx.keyboard.is_key_pressed(KeyCode::Left) {
            self.player.rotate(LEFT);
        }
        if _ctx.keyboard.is_key_pressed(KeyCode::Right) {
            self.player.rotate(RIGHT);
        }

        //updating entities
        for mut asteroid in self.asteroids.iter_mut() {
            asteroid.entity.move_entity();
        }
        self.player.entity.move_entity();

        for asteroid in self.asteroids.iter() {
            if self.player.entity.check_collision(&asteroid.entity) {
                println!("kolizja! {:?}", asteroid.entity.position);
            }
        }

        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);
        self.player.entity.draw(ctx, &mut canvas).expect("TODO: panic message");

        for asteroid in self.asteroids.iter() {
            asteroid.entity.draw(ctx, &mut canvas).expect("TODO: panic message");
        }

        canvas.finish(ctx)?;

        Ok(())
    }
}
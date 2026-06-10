mod player;
mod entity;
mod sprites;
mod constants;
mod asteroid;
mod renderer;
mod collision_checker;
mod utils;
mod game;
mod projectile;

use ggez::{ContextBuilder};
use ggez::conf::WindowMode;
use ggez::event::{self, EventHandler};
use rand::Rng;
use game::Game;

const WINDOW_WIDTH: f32 = 800.0;
const WINDOW_HEIGHT: f32 = 600.0;

fn main() {
    let (mut ctx, event_loop) = ContextBuilder::new("my_game", "Cool Game Author")
        .window_mode(WindowMode {
            width: WINDOW_WIDTH,
            height: WINDOW_HEIGHT,
            ..Default::default()
        })
        .build()
        .expect("aieee, could not create ggez context!");

    let game = Game::new(&mut ctx);
    event::run(ctx, event_loop, game);
}
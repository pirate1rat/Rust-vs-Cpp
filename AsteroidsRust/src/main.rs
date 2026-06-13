mod app;
mod playing_state;
mod menu_state;
mod name_entry_state;
mod player;
mod entity;
mod sprites;
mod constants;
mod asteroid;
mod renderer;
mod collision_checker;
mod utils;
mod projectile;

use crate::app::App;
use ggez::{ContextBuilder};
use ggez::conf::WindowMode;
use ggez::event::{self, EventHandler};
use constants::*;

fn main() {
    let (mut ctx, event_loop) = ContextBuilder::new("AsteroidsRust", "pirate1rat")
        .window_mode(WindowMode {
            width: WINDOW_WIDTH,
            height: WINDOW_HEIGHT,
            ..Default::default()
        })
        .build()
        .expect("aieee, could not create ggez context!");

    let app = App::new(&mut ctx);
    event::run(ctx, event_loop, app);
}
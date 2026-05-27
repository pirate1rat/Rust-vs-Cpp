mod player;
mod entity;
mod sprites;
mod constants;

use player::Player;
use ggez::{Context, ContextBuilder, GameResult};
use ggez::conf::WindowMode;
use ggez::graphics::{self, Color};
use ggez::event::{self, EventHandler};
use ggez::glam::Vec2;
use ggez::input::keyboard::{self, KeyCode};
use crate::constants::{BACKWARD, FORWARD, LEFT, RIGHT};
use crate::sprites::{SpriteType, STATIC_SPRITES};

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
    player: Player
}

impl MyGame {
    pub fn new(_ctx: &mut Context) -> MyGame {
        // Load/create resources such as images here.
        MyGame {
            player: Player::new(
                Vec2{x: WINDOW_WIDTH/2.0, y: WINDOW_HEIGHT/2.0},
                &STATIC_SPRITES[SpriteType::PLAYER.idx()]
            ),
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
        self.player.entity.move_entity();

        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);
        self.player.entity.draw(ctx, &mut canvas).expect("TODO: panic message");
        canvas.finish(ctx)?;

        Ok(())
    }
}
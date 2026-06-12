use ggez::Context;
use ggez::input::keyboard::KeyCode;
use crate::app::{Transition, GameState};
use crate::playing_state::PlayingState;


pub struct MenuState {

}

impl MenuState {
    pub fn new() -> MenuState {
        MenuState {  }
    }

    pub fn update(&mut self, ctx: &mut Context) -> Transition {
        if ctx.keyboard.is_key_pressed(KeyCode::Space) {
            return Transition::ToState(GameState::Playing(PlayingState::new(ctx)));
        }
        Transition::None
    }

    pub fn draw(&mut self, ctx: &mut Context) {

    }
}
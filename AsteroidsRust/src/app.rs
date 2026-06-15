use ggez::{ContextBuilder};
use ggez::conf::WindowMode;
use ggez::event::{self, EventHandler};
use ggez::{Context, GameResult};
use ggez::timer;
use rand::Rng;
use crate::constants::*;
use crate::playing_state::PlayingState;
use crate::menu_state::MenuState;
use crate::name_entry_state::NameEntryState;
use crate::scores_state::ScoresState;

pub enum GameState {
    Menu(MenuState),
    Playing(PlayingState),
    NameEntry(NameEntryState),
    DisplayScores(ScoresState)
    //GameOver(GameOverState),
}

pub enum Transition {
    None,
    ToState(GameState)
}

pub struct App {
    state: GameState,
}

impl App {
    pub fn new(ctx: &mut Context) -> App {
        App {
            state: GameState::Menu(MenuState::new()),
        }
    }
}

impl EventHandler for App {
    fn update(&mut self, ctx: &mut Context) -> GameResult {
        while ctx.time.check_update_time(60) {
            let transition = match &mut self.state {
                GameState::Menu(s) => s.update(ctx),
                GameState::Playing(s) => s.update(ctx),
                GameState::NameEntry(s) => s.update(ctx),
                GameState::DisplayScores(s) => s.update(ctx),
                //GameState::GameOver(s) => s.update(ctx),
            };

            if let Transition::ToState(new_state) = transition {
                self.state = new_state;
            }
        }

        Ok(())
    }

    fn draw(&mut self, ctx: &mut Context) -> GameResult {
        match &mut self.state {
            GameState::Menu(s) => s.draw(ctx)?,
            GameState::Playing(s) => s.draw(ctx)?,
            GameState::NameEntry(s) => s.draw(ctx)?,
            GameState::DisplayScores(s) => s.draw(ctx)?,
            //GameState::GameOver(s) => s.draw(ctx),
        }
        
        Ok(())
    }

    fn text_input_event(&mut self, _ctx: &mut Context, character: char) -> GameResult {
        match &mut self.state {
            GameState::NameEntry(s) => { s.text_input_event(character); }
            _ => {}
        }

        Ok(())
    }
}
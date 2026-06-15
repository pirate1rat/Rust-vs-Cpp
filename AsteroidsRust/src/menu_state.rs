use std::cmp::PartialEq;
use ggez::{graphics, Context, GameResult};
use ggez::graphics::{Color, DrawParam, Text, TextFragment};
use ggez::input::keyboard::KeyCode;
use crate::app::{Transition, GameState};
use crate::constants::{WINDOW_HEIGHT, WINDOW_WIDTH};
use crate::playing_state::PlayingState;
use crate::renderer::draw_option;
use crate::scores_state::ScoresState;

#[derive(Eq, PartialEq)]
enum MenuOption{
    Play,
    Scores,
    //Demo
}

pub struct MenuState {
    current_option: MenuOption
}

impl MenuState {
    pub fn new() -> MenuState {
        MenuState {
            current_option: MenuOption::Play
        }
    }

    pub fn update(&mut self, ctx: &mut Context) -> Transition {
        if ctx.keyboard.is_key_just_pressed(KeyCode::Up){
            self.current_option = match self.current_option {
                MenuOption::Play => MenuOption::Scores,
                MenuOption::Scores => MenuOption::Play,
                //MenuOption::Demo => MenuOption::Scores,
            }
        }

        if ctx.keyboard.is_key_just_pressed(KeyCode::Down){
            self.current_option = match self.current_option {
                MenuOption::Play => MenuOption::Scores,
                MenuOption::Scores => MenuOption::Play,
                //MenuOption::Demo => MenuOption::Play,
            }
        }

        if ctx.keyboard.is_key_just_pressed(KeyCode::Space)
            || ctx.keyboard.is_key_just_pressed(KeyCode::Return) {
            return match self.current_option {
                MenuOption::Play => { Transition::ToState(GameState::Playing(PlayingState::new())) }
                MenuOption::Scores => { Transition::ToState(GameState::DisplayScores(ScoresState::new())) }
                //MenuOption::Demo => { Transition::None }
            };
        }

        Transition::None
    }

    pub fn draw(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);

        let game_title = Text::new(TextFragment::new("ASTEROIDS").scale(72.0));
        let dims = game_title.measure(ctx)?;
        let x = (WINDOW_WIDTH - dims.x) / 2.0;
        let y = (WINDOW_HEIGHT - dims.y) / 4.0;

        canvas.draw(&game_title, DrawParam::default().dest([x, y]));

        draw_option(ctx, &mut canvas, "Play",
            (WINDOW_HEIGHT / 2.0) - 20.0, self.current_option == MenuOption::Play);

        draw_option(ctx, &mut canvas, "Scores",
            (WINDOW_HEIGHT / 2.0) + 60.0, self.current_option == MenuOption::Scores);

        // draw_option(ctx, &mut canvas, "Demo",
        //     (WINDOW_HEIGHT / 2.0) + 140.0, self.current_option == MenuOption::Demo);

        canvas.finish(ctx)
    }
}
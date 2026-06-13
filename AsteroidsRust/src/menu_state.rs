use std::cmp::PartialEq;
use ggez::{graphics, Context};
use ggez::graphics::{Color, DrawMode, DrawParam, Mesh, Rect, Text, TextFragment};
use ggez::input::keyboard::KeyCode;
use crate::app::{Transition, GameState};
use crate::constants::{WINDOW_HEIGHT, WINDOW_WIDTH};
use crate::playing_state::PlayingState;

#[derive(Eq, PartialEq)]
enum MenuOption{
    Play,
    Scores,
    Demo
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
                MenuOption::Play => MenuOption::Demo,
                MenuOption::Scores => MenuOption::Play,
                MenuOption::Demo => MenuOption::Scores,
            }
        }

        if ctx.keyboard.is_key_just_pressed(KeyCode::Down){
            self.current_option = match self.current_option {
                MenuOption::Play => MenuOption::Scores,
                MenuOption::Scores => MenuOption::Demo,
                MenuOption::Demo => MenuOption::Play,
            }
        }

        if ctx.keyboard.is_key_just_pressed(KeyCode::Space) {
            return match self.current_option {
                MenuOption::Play => { Transition::ToState(GameState::Playing(PlayingState::new(ctx))) }
                MenuOption::Scores => { Transition::None }
                MenuOption::Demo => { Transition::None }
            };
        }

        Transition::None
    }

    fn draw_option(ctx: &mut Context, canvas: &mut graphics::Canvas, label: &str, y: f32, selected: bool) {
        let text = Text::new(TextFragment::new(label).scale(36.0));
        let dims = text.measure(ctx).unwrap();
        let text_width = dims.x;
        let text_height = dims.y;

        let x = (WINDOW_WIDTH - text_width) / 2.0;

        canvas.draw(&text, DrawParam::default().dest([x, y]));

        if selected {
            let padding_x = 12.0;
            let padding_y = 8.0;
            let rect = Rect::new(
                x - padding_x,
                y - padding_y,
                text_width + padding_x * 2.0,
                text_height + padding_y * 2.0,
            );

            let border = Mesh::new_rectangle(ctx, DrawMode::stroke(2.0), rect, Color::WHITE).unwrap();
            canvas.draw(&border, DrawParam::default());
        }
    }

    pub fn draw(&mut self, ctx: &mut Context) {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);

        let game_title = Text::new(TextFragment::new("ASTEROIDS").scale(72.0));
        let dims = game_title.measure(ctx).unwrap();
        let x = (WINDOW_WIDTH - dims.x) / 2.0;
        let y = (WINDOW_HEIGHT - dims.y) / 4.0;

        canvas.draw(&game_title, DrawParam::default().dest([x, y]));

        Self::draw_option(
            ctx,
            &mut canvas,
            "Play",
            (WINDOW_HEIGHT / 2.0) - 20.0,
            self.current_option == MenuOption::Play,
        );

        Self::draw_option(
            ctx,
            &mut canvas,
            "Scores",
            (WINDOW_HEIGHT / 2.0) + 60.0,
            self.current_option == MenuOption::Scores,
        );

        Self::draw_option(
            ctx,
            &mut canvas,
            "Demo",
            (WINDOW_HEIGHT / 2.0) + 140.0,
            self.current_option == MenuOption::Demo,
        );

        canvas.finish(ctx);
    }
}
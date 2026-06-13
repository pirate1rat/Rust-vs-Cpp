use ggez::{graphics, Context};
use ggez::graphics::{Color, DrawParam, Text, TextFragment};
use ggez::input::keyboard::KeyCode;
use crate::app::{GameState, Transition};
use crate::constants::*;
use crate::menu_state::MenuState;

pub struct NameEntryState {
    pub name: String,
    cursor_timer: f32,
    show_cursor: bool,
}

impl NameEntryState {
    pub fn new() -> NameEntryState{
        NameEntryState {
            name: String::from(""),
            cursor_timer: 0.3,
            show_cursor: true,
        }
    }

    pub fn update(&mut self, ctx: &mut Context, score: &mut i32) -> Transition {
        self.cursor_timer += ctx.time.delta().as_secs_f32();
        if self.cursor_timer >= 0.5 {
            self.cursor_timer = 0.0;
            self.show_cursor = !self.show_cursor;
        }

        if ctx.keyboard.is_key_just_pressed(KeyCode::Back) {
            self.name.pop();
        }

        if ctx.keyboard.is_key_just_pressed(KeyCode::Return) {
            //self.save_score();
            return Transition::ToState(GameState::Menu(MenuState::new()));
        }

        Transition::None
    }

    pub fn draw(&mut self, ctx: &mut Context, score: &mut i32) {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);

        let title = Text::new(TextFragment::new("Your scores:").scale(48.0));
        let title_dims = title.measure(ctx).unwrap();
        let title_x = (WINDOW_WIDTH - title_dims.x) / 2.0;
        let title_y = WINDOW_HEIGHT / 2.0 - 90.0;

        canvas.draw(&title, DrawParam::default().dest([title_x, title_y]));

        let cursor = if self.show_cursor { "|" } else { " " };
        let input_line = format!("Enter your name: {}{}", self.name, cursor);

        let input_text = Text::new(TextFragment::new(input_line).scale(32.0));
        let input_dims = input_text.measure(ctx).unwrap();
        let input_x = (WINDOW_WIDTH - input_dims.x) / 2.0;
        let input_y = WINDOW_HEIGHT / 2.0;

        canvas.draw(&input_text, DrawParam::default().dest([input_x, input_y]));

        canvas.finish(ctx);
    }

    pub fn text_input_event(&mut self, character: char) {
        if character.is_control() {
            return;
        }

        if self.name.len() < 12 {
            self.name.push(character);
        }
    }
}
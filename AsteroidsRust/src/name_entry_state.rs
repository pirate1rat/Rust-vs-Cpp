use std::io::Write;
use std::fs::OpenOptions;
use ggez::{graphics, Context, GameResult};
use ggez::graphics::{Color, DrawParam, Text, TextFragment};
use ggez::input::keyboard::KeyCode;
use crate::app::{GameState, Transition};
use crate::constants::*;
use crate::menu_state::MenuState;

pub struct NameEntryState {
    pub name: String,
    score: i32,
    cursor_timer: f32,
    show_cursor: bool
}

impl NameEntryState {
    pub fn new(score: i32) -> NameEntryState{
        NameEntryState {
            name: String::from(""),
            score,
            cursor_timer: 0.3,
            show_cursor: true,
        }
    }

    pub fn update(&mut self, ctx: &mut Context) -> Transition {
        self.cursor_timer += ctx.time.delta().as_secs_f32();
        if self.cursor_timer >= 0.5 {
            self.cursor_timer = 0.0;
            self.show_cursor = !self.show_cursor;
        }

        if ctx.keyboard.is_key_just_pressed(KeyCode::Back) {
            self.name.pop();
        }

        if ctx.keyboard.is_key_just_pressed(KeyCode::Return) && self.save_score(self.score){
            return Transition::ToState(GameState::Menu(MenuState::new()));
        }

        Transition::None
    }

    pub fn draw(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);

        let title = Text::new(TextFragment::new("GAME OVER").color(Color::RED).scale(70.0));
        let title_dims = title.measure(ctx)?;
        let title_x = (WINDOW_WIDTH - title_dims.x) / 2.0;
        let title_y = 100.0;
        canvas.draw(&title, DrawParam::default().dest([title_x, title_y]));

        let scores_text = Text::new(TextFragment::new(format!("Your score: {}", self.score)).scale(36.0));
        let score_dims = scores_text.measure(ctx)?;
        let score_x = (WINDOW_WIDTH - score_dims.x) / 2.0;
        let score_y = 180.0;
        canvas.draw(&scores_text, DrawParam::default().dest([score_x, score_y]));

        let enter_name_text = Text::new(TextFragment::new("Enter your name:").color(Color::new(0.49019607, 0.49019607, 0.49019607, 1.0)).scale(32.0));
        let enter_name_dims = enter_name_text.measure(ctx)?;
        let enter_x = (WINDOW_WIDTH - enter_name_dims.x) / 2.0;
        let enter_y = 260.0;
        canvas.draw(&enter_name_text, DrawParam::default().dest([enter_x, enter_y]));

        let cursor = if self.show_cursor { "|" } else { " " };
        let input_line = format!("{}{}", self.name, cursor);
        let input_text = Text::new(TextFragment::new(input_line).color(Color::YELLOW).scale(32.0));
        let input_dims = input_text.measure(ctx)?;
        let input_x = (WINDOW_WIDTH - input_dims.x) / 2.0;
        let input_y = 330.0;
        canvas.draw(&input_text, DrawParam::default().dest([input_x, input_y]));

        let to_exit_text = Text::new(TextFragment::new("Press ENTER to save").color(Color::new(0.3529412, 0.3529412, 0.3529412, 1.0)).scale(26.0));
        let to_exit_dims = to_exit_text.measure(ctx)?;
        let to_exit_x = (WINDOW_WIDTH - to_exit_dims.x) / 2.0;
        let to_exit_y = 450.0;
        canvas.draw(&to_exit_text, DrawParam::default().dest([to_exit_x, to_exit_y]));

        canvas.finish(ctx)?;

        Ok(())
    }

    pub fn text_input_event(&mut self, character: char) {
        if character.is_control() {
            return;
        }

        if self.name.len() < 12 {
            self.name.push(character);
        }
    }

    fn save_score(&self, score: i32) -> bool {
        if self.name.trim().is_empty() {
            return false;
        }

        if let Ok(mut file) = OpenOptions::new()
            .create(true)
            .append(true)
            .open("scores.txt")
        {
            let _ = writeln!(file, "{};{};", self.name.trim(), score);
        }
        true
    }
}
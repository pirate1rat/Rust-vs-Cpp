use std::fs;
use ggez::{graphics, Context, GameResult};
use ggez::graphics::{Color, DrawParam, Text, TextFragment};
use ggez::input::keyboard::KeyCode;
use crate::app::{Transition, GameState};
use crate::constants::{MAIN_FONT, WINDOW_HEIGHT, WINDOW_WIDTH};
use crate::menu_state::MenuState;

#[derive(Clone)]
struct PlayerScore {
    name: String,
    score: u32,
}

pub struct ScoresState {
    scores: Vec<PlayerScore>,
    scroll_index: usize,
}

impl ScoresState {
    pub fn new() -> ScoresState {
        let mut state = ScoresState {
            scores: Vec::new(),
            scroll_index: 0,
        };

        state.load_scores();
        state
    }

    fn load_scores(&mut self) {
        self.scores.clear();

        let content = match fs::read_to_string("scores.txt") {
            Ok(text) => text,
            Err(_) => return,
        };

        for line in content.lines() {
            let parts: Vec<&str> = line.split(';').collect();
            if parts.len() < 2 {
                continue;
            }

            let name = parts[0].trim().to_string();
            let score_str = parts[1].trim();

            if name.is_empty() {
                continue;
            }

            if let Ok(score) = score_str.parse::<u32>() {
                self.scores.push(PlayerScore { name, score });
            }
        }

        self.scores.sort_by(|a, b| b.score.cmp(&a.score));

        if self.scroll_index >= self.scores.len() {
            self.scroll_index = 0;
        }
    }

    pub fn update(&mut self, ctx: &mut Context) -> Transition {
        if ctx.keyboard.is_key_just_pressed(KeyCode::Space) {
            return Transition::ToState(GameState::Menu(MenuState::new()));
        }

        if !self.scores.is_empty() {
            let max_start = self.scores.len().saturating_sub(5);

            if ctx.keyboard.is_key_just_pressed(KeyCode::Up) && self.scroll_index > 0 {
                self.scroll_index -= 1;
            }

            if ctx.keyboard.is_key_just_pressed(KeyCode::Down) && self.scroll_index < max_start {
                self.scroll_index += 1;
            }
        }

        Transition::None
    }

    fn draw_centered_text(ctx: &mut Context, canvas: &mut graphics::Canvas, label: &str, y: f32, scale: f32) -> GameResult {
        let text = Text::new(TextFragment::new(label).scale(scale).font(MAIN_FONT));
        let dims = text.measure(ctx)?;
        let x = (WINDOW_WIDTH - dims.x) / 2.0;

        canvas.draw(&text, DrawParam::default().dest([x, y]));
        Ok(())
    }

    pub fn draw(&mut self, ctx: &mut Context) -> GameResult {
        let mut canvas = graphics::Canvas::from_frame(ctx, Color::BLACK);

        let title = Text::new(TextFragment::new("HIGH SCORES")
            .color(Color::YELLOW)
            .scale(44.0)
            .font(MAIN_FONT));
        let title_dims = title.measure(ctx)?;
        let title_x = (WINDOW_WIDTH - title_dims.x) / 2.0;
        let title_y = 60.0;
        canvas.draw(&title, DrawParam::default().dest([title_x, title_y]));

        if self.scores.is_empty() {
            Self::draw_centered_text(ctx, &mut canvas, "No scores yet!",
                                     WINDOW_HEIGHT / 2.0, 22.0)?;
        } else {
            let visible_count = 5;
            let start = self.scroll_index;
            let end = (start + visible_count).min(self.scores.len());

            let base_y = WINDOW_HEIGHT / 2.0 - 100.0;
            let line_spacing = 45.0;

            for (i, player) in self.scores[start..end].iter().enumerate() {
                let rank = start + i + 1;
                let line = format!("{}. {} - {}", rank, player.name, player.score);

                Self::draw_centered_text(ctx, &mut canvas, &line,
                    base_y + i as f32 * line_spacing, 20.0, )?;
            }
        }

        let back_hint = Text::new(TextFragment::new("Press SPACE to return to Menu")
            .color(Color::new(0.3529412, 0.3529412, 0.3529412, 1.0))
            .scale(14.0).
            font(MAIN_FONT));
        let hint_dims = back_hint.measure(ctx)?;
        let hint_x = (WINDOW_WIDTH - hint_dims.x) / 2.0;
        canvas.draw(&back_hint, DrawParam::default().dest([hint_x, 500.0]),
        );

        canvas.finish(ctx)?;
        Ok(())
    }
}
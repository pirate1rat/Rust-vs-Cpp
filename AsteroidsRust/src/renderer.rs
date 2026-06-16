use ggez::{graphics, Context, GameResult};
use ggez::glam::Vec2;
use ggez::graphics::{Canvas, Color, DrawMode, DrawParam, Mesh, Rect, Text, TextFragment};
use crate::constants::{MAIN_FONT, WINDOW_WIDTH};
use crate::sprites::SpriteStruct;
use crate::utils::transform;

pub fn draw_sprite(ctx: &mut Context, canvas: &mut Canvas,
                   prefab: &'static SpriteStruct, position: Vec2, rotation: f32, color: Color) -> GameResult {
    let points: Vec<Vec2> = (0..=prefab.g_points.len())
        .map(|i| transform(prefab.g_points[i % prefab.g_points.len()], position, rotation))
        .collect();

    let mesh = Mesh::new_line(ctx, &points, 1.0, color)?;
    canvas.draw(&mesh, DrawParam::default());
    Ok(())
}

pub fn draw_option(ctx: &mut Context, canvas: &mut Canvas, label: &str, y: f32, selected: bool) -> GameResult {
    let text = Text::new(TextFragment::new(label).scale(28.0).font(MAIN_FONT));
    let dims = text.measure(ctx)?;
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

        let border = Mesh::new_rectangle(ctx, DrawMode::stroke(2.0), rect, Color::WHITE)?;
        canvas.draw(&border, DrawParam::default());
    }
    Ok(())
}
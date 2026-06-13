use ggez::{graphics, Context, GameResult};
use ggez::glam::Vec2;
use ggez::graphics::{Canvas, Color, DrawMode, DrawParam, Mesh, Rect, Text, TextFragment};
use crate::constants::WINDOW_WIDTH;
use crate::sprites::SpriteStruct;
use crate::utils::transform;

pub fn draw_sprite(ctx: &mut Context, canvas: &mut Canvas,
                   prefab: &'static SpriteStruct, position: Vec2, rotation: f32, color: Color) -> GameResult{
    let self_length = prefab.g_points.len();
    for (i, point) in prefab.g_points.iter().enumerate() {
        let p1 = transform(prefab.g_points[i], position, rotation);
        let p2 = transform(prefab.g_points[(i+1)%self_length], position, rotation);
        let line = Mesh::new_line(
            ctx,
            &[ p1, p2 ],
            1.0,
            color,
        )?;
        canvas.draw(&line, DrawParam::default());
    }
    Ok(())
}

pub fn draw_option(ctx: &mut Context, canvas: &mut graphics::Canvas, label: &str, y: f32, selected: bool) {
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
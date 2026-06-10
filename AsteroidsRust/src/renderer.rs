use ggez::{Context, GameResult};
use ggez::glam::Vec2;
use ggez::graphics::{Canvas, Color, DrawParam, Mesh};
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
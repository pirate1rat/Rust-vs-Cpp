use ggez::glam::{Mat2, Vec2};
pub fn cross(a: Vec2, b: Vec2, c: Vec2) -> f32 {
    (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)
}

pub fn on_segment(a: Vec2, b: Vec2, p: Vec2) -> bool {
    a.x.min(b.x) <= p.x && p.x <= a.x.max(b.x)
        && a.y.min(b.y) <= p.y && p.y <= a.y.max(b.y)
}

pub fn transform(p: Vec2, position: Vec2, rotation: f32) -> Vec2 {
    let rot = Mat2::from_angle(rotation);
    position + rot * p
}
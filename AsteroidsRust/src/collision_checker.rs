use ggez::glam::Vec2;
use crate::constants::EPS;
use crate::sprites::SpriteStruct;
use crate::utils::*;

pub fn check_collision(prefab_a: &SpriteStruct, pos_a: Vec2, rot_a: f32,
                       prefab_b: &SpriteStruct, pos_b: Vec2, rot_b: f32) -> bool {
    let self_length = prefab_a.h_points.len();
    let other_length = prefab_b.h_points.len();
    for (i, _) in prefab_a.h_points.iter().enumerate() {
        let a: Vec2 = transform(prefab_a.h_points[i], pos_a, rot_a);
        let b: Vec2 = transform(prefab_a.h_points[(i+1)%self_length], pos_a, rot_a);
        for (j, _) in prefab_b.h_points.iter().enumerate() {
            let c: Vec2 = transform(prefab_b.h_points[i], pos_b, rot_b);
            let d: Vec2 = transform(prefab_b.h_points[(j+1)%other_length], pos_b, rot_b);

            let d1 = cross(a, b, c);
            let d2 = cross(a, b, d);
            let d3 = cross(c, d, a);
            let d4 = cross(c, d, b);

            if (d1 > 0.0 && d2 < 0.0 || d1 < 0.0 && d2 > 0.0) &&
                (d3 > 0.0 && d4 < 0.0 || d3 < 0.0 && d4 > 0.0) {
                return true
            }

            if d1.abs() < EPS && on_segment(a, b, c) { return true };
            if d2.abs() < EPS && on_segment(a, b, d) { return true };
            if d3.abs() < EPS && on_segment(c, d, a) { return true };
            if d4.abs() < EPS && on_segment(c, d, b) { return true };
        }
    }

    false
}
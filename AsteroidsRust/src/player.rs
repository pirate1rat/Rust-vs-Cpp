use ggez::mint::{Point2, Vector2};
use ggez::graphics::Color;

struct Player{
    points: [Point2<f32>; 4],
    direction_vec: Vector2<f32> = Vector2{ x: 0.0, y: -0.1 },
    rotation: f32 = 0.001,
    center_of_gravity: Vector2<f32> = Vector2{ x: 0.0f, y: -2.5f },
	player_color: Color = Color(255, 255, 255, 255)
}

impl Player{
    fn new(center: Point2<f32>) -> Player {
        let base_points = [
            Point2{ x: 0.0f, y: -16.0f },
            Point2{ x: -8.0f, y: 14.0f },
            Point2{ x: 0.0f, y: 9.5f },
            Point2{ x: 8.0f, y: 14.0f },
        ];
        let base_center = Point2{ x: 0.0f, y: -2.5f };

        let points = base_points.map(|p| Point2{
            x: p.x + center.x, y: p.y + center.y
        });

        Player { 
            center_of_gravity: center_of_gravity + center, .. }
    }
}
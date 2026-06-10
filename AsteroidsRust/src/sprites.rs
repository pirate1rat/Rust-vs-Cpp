use ggez::glam::{Mat2, Vec2};
use rand::Rng;

pub struct SpriteStruct {
    pub g_points: &'static [Vec2],
    pub h_points: &'static [Vec2],
}

#[repr(usize)]
#[derive(Clone)]
pub enum SpriteType {
    PLAYER = 0,
    ASTEROID_SMALL_1,
    ASTEROID_SMALL_2,
    ASTEROID_MEDIUM_1,
    ASTEROID_MEDIUM_2,
    ASTEROID_MEDIUM_3,
    ASTEROID_BIG_1,
    ASTEROID_BIG_2,
    ASTEROID_BIG_3,
    PROJECTILE,
    ENUM_LENGTH
}

impl SpriteType {
    pub fn idx(self) -> usize {
        self as usize
    }
}

static PLAYER: [Vec2; 4] = [
    Vec2 { x: 0.0, y: -16.0 },
    Vec2 { x: -8.0, y: 14.0 },
    Vec2 { x: 0.0, y: 9.5 },
    Vec2 { x: 8.0, y: 14.0 },
];

static ASTEROID_SMALL_1: [Vec2; 7] = [
    Vec2 { x: 9.0, y: -1.0 },
    Vec2 { x: 4.0, y: 8.5 },
    Vec2 { x: -6.0, y: 7.0 },
    Vec2 { x: -9.5, y: 1.5 },
    Vec2 { x: -7.0, y: -6.5 },
    Vec2 { x: 0.5, y: -9.0 },
    Vec2 { x: 7.0, y: -6.0 },
];

static ASTEROID_SMALL_2: [Vec2; 8] = [
    Vec2 { x: 8.5, y: 2.0 },
    Vec2 { x: 5.0, y: 8.0 },
    Vec2 { x: -3.0, y: 9.0 },
    Vec2 { x: -8.5, y: 4.5 },
    Vec2 { x: -7.5, y: -4.0 },
    Vec2 { x: -2.0, y: -8.5 },
    Vec2 { x: 4.5, y: -7.5 },
    Vec2 { x: 9.5, y: -3.0 },
];

static ASTEROID_MEDIUM_1: [Vec2; 7] = [
    Vec2 { x: 18.5, y: 0.0 },
    Vec2 { x: 8.0, y: 15.5 },
    Vec2 { x: -9.5, y: 14.0 },
    Vec2 { x: -19.0, y: 3.0 },
    Vec2 { x: -12.0, y: -11.0 },
    Vec2 { x: 0.0, y: -17.5 },
    Vec2 { x: 11.5, y: -12.0 },
];

static ASTEROID_MEDIUM_2: [Vec2; 8] = [
    Vec2 { x: 16.0, y: 4.0 },
    Vec2 { x: 10.0, y: 16.5 },
    Vec2 { x: -5.0, y: 18.0 },
    Vec2 { x: -17.5, y: 9.0 },
    Vec2 { x: -15.0, y: -7.0 },
    Vec2 { x: -4.0, y: -16.0 },
    Vec2 { x: 8.0, y: -14.5 },
    Vec2 { x: 19.5, y: -5.0 },
];

static ASTEROID_MEDIUM_3: [Vec2; 10] = [
    Vec2 { x: 17.0, y: 2.0 },
    Vec2 { x: 13.0, y: 11.0 },
    Vec2 { x: 4.0, y: 19.0 },
    Vec2 { x: -9.0, y: 15.5 },
    Vec2 { x: -18.5, y: 6.0 },
    Vec2 { x: -16.0, y: -8.0 },
    Vec2 { x: -7.0, y: -17.0 },
    Vec2 { x: 3.0, y: -19.5 },
    Vec2 { x: 12.0, y: -13.0 },
    Vec2 { x: 19.0, y: -6.0 },
];

static ASTEROID_BIG_1: [Vec2; 8] = [
    Vec2 { x: 38.0, y: 5.0 },
    Vec2 { x: 22.0, y: 33.0 },
    Vec2 { x: -15.0, y: 36.0 },
    Vec2 { x: -39.0, y: 12.0 },
    Vec2 { x: -31.0, y: -22.0 },
    Vec2 { x: -8.0, y: -37.0 },
    Vec2 { x: 25.0, y: -29.0 },
    Vec2 { x: 39.5, y: -12.0 },
];

static ASTEROID_BIG_2: [Vec2; 9] = [
    Vec2 { x: 28.0, y: 10.0 },
    Vec2 { x: 18.0, y: 32.0 },
    Vec2 { x: -5.0, y: 39.0 },
    Vec2 { x: -26.0, y: 25.0 },
    Vec2 { x: -35.0, y: -5.0 },
    Vec2 { x: -21.0, y: -31.0 },
    Vec2 { x: 2.0, y: -38.5 },
    Vec2 { x: 24.0, y: -26.0 },
    Vec2 { x: 33.0, y: -11.0 },
];

static ASTEROID_BIG_3: [Vec2; 10] = [
    Vec2 { x: 35.0, y: 3.0 },
    Vec2 { x: 26.0, y: 24.0 },
    Vec2 { x: 9.0, y: 37.0 },
    Vec2 { x: -18.0, y: 31.0 },
    Vec2 { x: -36.0, y: 14.0 },
    Vec2 { x: -33.0, y: -17.0 },
    Vec2 { x: -14.0, y: -35.0 },
    Vec2 { x: 8.0, y: -38.0 },
    Vec2 { x: 27.0, y: -25.0 },
    Vec2 { x: 37.0, y: -13.0 },
];

static PROJECTILE: [Vec2; 4] = [
    Vec2{ x: 0.0, y:-2.5 },
    Vec2{ x: -2.5, y: 0.0 },
    Vec2{ x: 0.0, y: 2.5 },
    Vec2{ x: 2.5, y: 0.0 },
];

////// HITBOXES

static H_PLAYER: [Vec2; 3] = [
    Vec2 { x: 0.0, y: -16.0 },
    Vec2 { x: -8.0, y: 14.0 },
    Vec2 { x: 8.0, y: 14.0 },
];

static H_SMALL_ASTEROID: [Vec2; 4] = [
    Vec2 { x: -10.0, y: -10.0 },
    Vec2 { x: -10.0, y: 10.0 },
    Vec2 { x: 10.0, y: 10.0 },
    Vec2 { x: 10.0, y: -10.0 },
];

static H_MEDIUM_ASTEROID: [Vec2; 4] = [
    Vec2 { x: -20.0, y: -20.0 },
    Vec2 { x: -20.0, y: 20.0 },
    Vec2 { x: 20.0, y: 20.0 },
    Vec2 { x: 20.0, y: -20.0 },
];

static H_BIG_ASTEROID: [Vec2; 4] = [
    Vec2 { x: -40.0, y: -40.0 },
    Vec2 { x: -40.0, y: 40.0 },
    Vec2 { x: 40.0, y: 40.0 },
    Vec2 { x: 40.0, y: -40.0 },
];

static H_PROJECTILE: [Vec2; 4] = [
    Vec2{ x: 0.0, y: -2.5},
    Vec2{ x: -2.5,y:  0.0},
    Vec2{ x: 0.0, y: 2.5},
    Vec2{ x: 2.5, y: 0.0},
]; 

//////// READY PREFABS

pub static SPRITES: [SpriteStruct; 10] = [
    SpriteStruct {
        g_points: &PLAYER,
        h_points: &H_PLAYER,
    },
    SpriteStruct {
        g_points: &ASTEROID_SMALL_1,
        h_points: &H_SMALL_ASTEROID,
    },
    SpriteStruct {
        g_points: &ASTEROID_SMALL_2,
        h_points: &H_SMALL_ASTEROID,
    },
    SpriteStruct {
        g_points: &ASTEROID_MEDIUM_1,
        h_points: &H_MEDIUM_ASTEROID,
    },
    SpriteStruct {
        g_points: &ASTEROID_MEDIUM_2,
        h_points: &H_MEDIUM_ASTEROID,
    },
    SpriteStruct {
        g_points: &ASTEROID_MEDIUM_3,
        h_points: &H_MEDIUM_ASTEROID,
    },
    SpriteStruct {
        g_points: &ASTEROID_BIG_1,
        h_points: &H_BIG_ASTEROID,
    },
    SpriteStruct {
        g_points: &ASTEROID_BIG_2,
        h_points: &H_BIG_ASTEROID,
    },
    SpriteStruct {
        g_points: &ASTEROID_BIG_3,
        h_points: &H_BIG_ASTEROID,
    },
    SpriteStruct {
        g_points: &PROJECTILE,
        h_points: &H_PROJECTILE,
    },
];
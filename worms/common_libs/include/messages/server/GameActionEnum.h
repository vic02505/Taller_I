#pragma once
#include <stdint.h>

enum GameAction : uint8_t {
    START_TURN = 0x00,
    WORM_MOVE_RIGHT = 0x01,
    WORM_MOVE_LEFT = 0x02,
    WORM_IDLE = 0x03,
    WORM_NONE = 0x04,
    WORM_JUMP = 0x05,
    WORM_FALL = 0x06,
    HAS_WEAPON_AND_ATTACK = 0X07,
    HAS_WEAPON_AND_NO_ATTACK = 0X08,
    NO_HAS_WEAPON = 0X09,
    WORM_ATTACKED = 0x0A,
    WORM_DIE = 0x0B,
    WORM_GRAVE = 0x0C,
    END_TURN = 0x0D,
    TURN_TRANSITION = 0x0E,
    PROJECTILE_LAUNCHED = 0x0F,
    END_GAME = 0x10,
    PROJECTILE_COLLIDED = 0x11,
    INVALID_ACTION = 0xFF
};
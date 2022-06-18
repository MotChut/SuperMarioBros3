#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_QUESTIONBLOCK	6
#define OBJECT_TYPE_MUSHROOM	7
#define OBJECT_TYPE_TRANSBLOCK	8
#define OBJECT_TYPE_BRICK_BREAK	9
#define OBJECT_TYPE_BUTTON	11

#define OBJECT_TYPE_TILES 10

#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_BIG_KICK (ID_SPRITE_MARIO_BIG + 700)
#define ID_SPRITE_MARIO_BIG_KICK_LEFT (ID_SPRITE_MARIO_BIG_KICK + 10)
#define ID_SPRITE_MARIO_BIG_KICK_RIGHT (ID_SPRITE_MARIO_BIG_KICK + 20)

#define ID_SPRITE_MARIO_BIG_CARRY (ID_SPRITE_MARIO_BIG + 800)
#define ID_SPRITE_MARIO_BIG_CARRY_LEFT (ID_SPRITE_MARIO_BIG_CARRY + 10)
#define ID_SPRITE_MARIO_BIG_CARRY_RIGHT (ID_SPRITE_MARIO_BIG_CARRY + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#define ID_SPRITE_MARIO_SMALL_KICK (ID_SPRITE_MARIO_SMALL + 600)
#define ID_SPRITE_MARIO_SMALL_KICK_LEFT (ID_SPRITE_MARIO_SMALL_KICK + 10)
#define ID_SPRITE_MARIO_SMALL_KICK_RIGHT (ID_SPRITE_MARIO_SMALL_KICK + 20)

#define ID_SPRITE_MARIO_SMALL_CARRY (ID_SPRITE_MARIO_SMALL + 700)
#define ID_SPRITE_MARIO_SMALL_CARRY_LEFT (ID_SPRITE_MARIO_SMALL_CARRY + 10)
#define ID_SPRITE_MARIO_SMALL_CARRY_RIGHT (ID_SPRITE_MARIO_SMALL_CARRY + 20)


#define ID_SPRITE_MARIO_TAIL (ID_SPRITE_MARIO + 3000)
#define ID_SPRITE_MARIO_TAIL_IDLE (ID_SPRITE_MARIO_TAIL + 100)
#define ID_SPRITE_MARIO_TAIL_IDLE_LEFT (ID_SPRITE_MARIO_TAIL_IDLE + 10)
#define ID_SPRITE_MARIO_TAIL_IDLE_RIGHT (ID_SPRITE_MARIO_TAIL_IDLE + 20)

#define ID_SPRITE_MARIO_TAIL_WALKING (ID_SPRITE_MARIO_TAIL + 200)
#define ID_SPRITE_MARIO_TAIL_WALKING_LEFT (ID_SPRITE_MARIO_TAIL_WALKING + 10)
#define ID_SPRITE_MARIO_TAIL_WALKING_RIGHT (ID_SPRITE_MARIO_TAIL_WALKING + 20)
#define ID_SPRITE_MARIO_TAIL_RUNNING (ID_SPRITE_MARIO_TAIL + 300)
#define ID_SPRITE_MARIO_TAIL_RUNNING_LEFT (ID_SPRITE_MARIO_TAIL_RUNNING + 10)
#define ID_SPRITE_MARIO_TAIL_RUNNING_RIGHT (ID_SPRITE_MARIO_TAIL_RUNNING + 20)
#define ID_SPRITE_MARIO_TAIL_JUMP (ID_SPRITE_MARIO_TAIL + 400)
#define ID_SPRITE_MARIO_TAIL_JUMP_WALK (ID_SPRITE_MARIO_TAIL_JUMP + 10)
#define ID_SPRITE_MARIO_TAIL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_TAIL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_TAIL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_TAIL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_TAIL_JUMP_RUN (ID_SPRITE_MARIO_TAIL_JUMP + 20)
#define ID_SPRITE_MARIO_TAIL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_TAIL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_TAIL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_TAIL_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_TAIL_SIT (ID_SPRITE_MARIO_TAIL + 500)
#define IID_SPRITE_MARIO_TAIL_SIT_LEFT (ID_SPRITE_MARIO_TAIL_SIT + 10)
#define ID_SPRITE_MARIO_TAIL_SIT_RIGHT (ID_SPRITE_MARIO_TAIL_SIT + 20)
#define ID_SPRITE_MARIO_TAIL_BRACE (ID_SPRITE_MARIO_TAIL + 600)
#define ID_SPRITE_MARIO_TAIL_BRACE_LEFT (ID_SPRITE_MARIO_TAIL_BRACE + 10)
#define ID_SPRITE_MARIO_TAIL_BRACE_RIGHT (ID_SPRITE_MARIO_TAIL_BRACE + 20)
#define ID_SPRITE_MARIO_TAIL_LANDING (ID_SPRITE_MARIO_TAIL + 700)
#define ID_SPRITE_MARIO_TAIL_LANDING_LEFT (ID_SPRITE_MARIO_TAIL_LANDING + 10)
#define ID_SPRITE_MARIO_TAIL_LANDING_RIGHT (ID_SPRITE_MARIO_TAIL_LANDING + 20)

#define ID_SPRITE_MARIO_TAIL_KICK (ID_SPRITE_MARIO_TAIL + 800)
#define ID_SPRITE_MARIO_TAIL_KICK_LEFT (ID_SPRITE_MARIO_TAIL_KICK + 10)
#define ID_SPRITE_MARIO_TAIL_KICK_RIGHT (ID_SPRITE_MARIO_TAIL_KICK + 20)

#define ID_SPRITE_MARIO_TAIL_CARRY (ID_SPRITE_MARIO_TAIL + 900)
#define ID_SPRITE_MARIO_TAIL_CARRY_LEFT (ID_SPRITE_MARIO_TAIL_CARRY + 10)
#define ID_SPRITE_MARIO_TAIL_CARRY_RIGHT (ID_SPRITE_MARIO_TAIL_CARRY + 20)

#define ID_SPRITE_MARIO_TAIL_HIT (ID_SPRITE_MARIO_TAIL + 950)

#pragma endregion 

#define ID_SPRITE_BRICK 20000
#define ID_SPRITE_BRICK_BREAK	21000
#define ID_SPRITE_BUTTON	22000
#define ID_SPRITE_BUTTON_DOWNED	22001

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)
#define ID_SPRITE_GOOMBA_FLIP (ID_SPRITE_GOOMBA + 3000)

#define ID_SPRITE_GOOMBA_RED	(ID_SPRITE_GOOMBA + 4000)
#define ID_SPRITE_GOOMBA_RED_WING	(ID_SPRITE_GOOMBA_RED + 100)
#define ID_SPRITE_GOOMBA_RED_WALKING	(ID_SPRITE_GOOMBA_RED + 1)
#define ID_SPRITE_GOOMBA_RED_DIE	(ID_SPRITE_GOOMBA_RED + 10)
#define ID_SPRITE_GOOMBA_RED_FLIP	(ID_SPRITE_GOOMBA_RED + 11)
#define ID_SPRITE_GOOMBA_RED_WING_WALKING	(ID_SPRITE_GOOMBA_RED_WING + 1)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_TILE_TRANSPARENT 60000
#define ID_SPRITE_QUESTIONBLOCK 70000
#define ID_ITEM	80000
#define ID_ITEM_MUSHROOM	(ID_ITEM + 1000)
#define ID_ITEM_LEAF	(ID_ITEM + 2000)


//KOOPA
#define ID_SPRITE_KOOPA	90000
#define ID_SPRITE_KOOPA_NORMAL_GREEN	(ID_SPRITE_KOOPA + 1000)
#define ID_SPRITE_KOOPA_FLY_GREEN	(ID_SPRITE_KOOPA + 2000)
#define ID_SPRITE_KOOPA_NORMAL_RED	(ID_SPRITE_KOOPA + 3000)
#define ID_SPRITE_KOOPA_FLY_RED	(ID_SPRITE_KOOPA + 4000)

#define ID_SPRITE_KOOPA_NORMAL_GREEN_WALK_LEFT	(ID_SPRITE_KOOPA_NORMAL_GREEN + 100)
#define ID_SPRITE_KOOPA_FLY_GREEN_WALK_LEFT	(ID_SPRITE_KOOPA_FLY_GREEN + 100)
#define ID_SPRITE_KOOPA_NORMAL_RED_WALK_LEFT	(ID_SPRITE_KOOPA_NORMAL_RED + 100)
#define ID_SPRITE_KOOPA_FLY_RED_WALK_LEFT	(ID_SPRITE_KOOPA_FLY_RED + 100)

#define ID_SPRITE_KOOPA_NORMAL_GREEN_WALK_RIGHT	(ID_SPRITE_KOOPA_NORMAL_GREEN + 200)
#define ID_SPRITE_KOOPA_FLY_GREEN_WALK_RIGHT	(ID_SPRITE_KOOPA_FLY_GREEN + 200)
#define ID_SPRITE_KOOPA_NORMAL_RED_WALK_RIGHT	(ID_SPRITE_KOOPA_NORMAL_RED + 200)
#define ID_SPRITE_KOOPA_FLY_RED_WALK_RIGHT	(ID_SPRITE_KOOPA_FLY_RED + 200)

#define ID_SPRITE_KOOPA_GREEN_SHELL	(ID_SPRITE_KOOPA_NORMAL_GREEN + 300)
#define ID_SPRITE_KOOPA_RED_SHELL	(ID_SPRITE_KOOPA_NORMAL_RED + 300)

#define ID_SPRITE_KOOPA_GREEN_SHELL_AWAKE	(ID_SPRITE_KOOPA_NORMAL_GREEN + 400)
#define ID_SPRITE_KOOPA_RED_SHELL_AWAKE	(ID_SPRITE_KOOPA_NORMAL_RED + 400)

#define ID_SPRITE_KOOPA_GREEN_SHELL_MOVING	(ID_SPRITE_KOOPA_NORMAL_GREEN + 500)
#define ID_SPRITE_KOOPA_RED_SHELL_MOVING	(ID_SPRITE_KOOPA_NORMAL_RED + 500)
#define ID_SPRITE_KOOPA_RED_SHELL_FLIPPED	(ID_SPRITE_KOOPA_NORMAL_RED + 600)
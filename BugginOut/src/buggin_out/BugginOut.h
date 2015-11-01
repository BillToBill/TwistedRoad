#pragma once
#include "buggin_out_VS\stdafx.h"

/*
	BugginOutGame.h

	This file contains setup data for making the BugginOut game. Note that nearly
	all of this data would better serve us if loaded from files.
*/

// HERE IS THE BugginOut GAME SETUP/INIT FILE. EVERYTHING WOULD START FROM HERE

static const wstring	W_LEVEL_1_DIR			= L"data/levels/SSlv/";
static const wstring	W_LEVEL_1_NAME			= L"SSlv1.tmx";
static const wstring	W_LEVEL_2_NAME			= L"SSlv2.tmx";
static const wstring	W_LEVEL_3_NAME			= L"SSlv3.tmx";
static const wstring	W_LEVEL_4_NAME			= L"SSlv4.tmx";
static const wstring	W_LEVEL_5_NAME			= L"SSlv5.tmx";
static const wstring	W_LEVEL_6_NAME			= L"SSlv6.tmx";
static const wstring	W_LEVEL_7_NAME			= L"SSlv7.tmx";
static const wstring	W_LEVEL_8_NAME			= L"SSlv8.tmx";
static const wstring	W_LEVEL_9_NAME			= L"SSlv9.tmx";
static const wstring	W_LEVEL_10_NAME			= L"SSlv10.tmx";


static const wstring	W_LEVEL_1_PATH			= W_LEVEL_1_DIR + W_LEVEL_1_NAME;
static const wstring	W_LEVEL_2_PATH			= W_LEVEL_1_DIR + W_LEVEL_2_NAME;
static const wstring	W_LEVEL_3_PATH			= W_LEVEL_1_DIR + W_LEVEL_3_NAME;
static const wstring	W_LEVEL_4_PATH			= W_LEVEL_1_DIR + W_LEVEL_4_NAME;
static const wstring	W_LEVEL_5_PATH			= W_LEVEL_1_DIR + W_LEVEL_5_NAME;
static const wstring	W_LEVEL_6_PATH			= W_LEVEL_1_DIR + W_LEVEL_6_NAME;
static const wstring	W_LEVEL_7_PATH			= W_LEVEL_1_DIR + W_LEVEL_7_NAME;
static const wstring	W_LEVEL_8_PATH			= W_LEVEL_1_DIR + W_LEVEL_8_NAME;
static const wstring	W_LEVEL_9_PATH			= W_LEVEL_1_DIR + W_LEVEL_9_NAME;
static const wstring	W_LEVEL_10_PATH			= W_LEVEL_1_DIR + W_LEVEL_10_NAME;

static const wstring	W_LEVEL_2_DIR			= L"data/levels/SideScrollerDesert/";
//static const wstring	W_LEVEL_2_NAME			= L"SideScrollerDesertLevel.tmx";
//static const wstring	W_LEVEL_2_PATH			= W_LEVEL_2_DIR + W_LEVEL_2_NAME;
static const wstring	W_INIT_FILE				= L"data/BugginOutInit.txt";
static const wstring	W_GUI_INIT_FILE			= L"data/BugginOutGUI.txt";
static const string		W_DEBUG_FILE			= "DebugOutput.txt";

// HERE ARE THE GAME PROPERTIES WE ARE LOADING FROM FROM THE SETUP FILE
static const wstring	W_TITLE					= L"TITLE";
static const wstring	W_SCREEN_WIDTH			= L"SCREEN_WIDTH";
static const wstring	W_SCREEN_HEIGHT			= L"SCREEN_HEIGHT";
static const wstring	W_USE_FULLSCREEN_MODE	= L"USE_FULLSCREEN_MODE";
static const wstring	W_TEXT_FONT_SIZE		= L"TEXT_FONT_SIZE";
static const wstring	W_VIEWPORT_OFFSET_X		= L"VIEWPORT_OFFSET_X";
static const wstring	W_VIEWPORT_OFFSET_Y		= L"VIEWPORT_OFFSET_Y";
static const wstring	W_TOGGLE_OFFSET_Y		= L"TOGGLE_OFFSET_Y";
static const wstring	W_FONT_COLOR_RED		= L"FONT_COLOR_RED";
static const wstring	W_FONT_COLOR_GREEN		= L"FONT_COLOR_GREEN";
static const wstring	W_FONT_COLOR_BLUE		= L"FONT_COLOR_BLUE";
static const wstring	W_COLOR_KEY_RED			= L"COLOR_KEY_RED";
static const wstring	W_COLOR_KEY_GREEN		= L"COLOR_KEY_GREEN";
static const wstring	W_COLOR_KEY_BLUE		= L"COLOR_KEY_BLUE";

// CONSTANTS FOR ARTWORK - NOTE, THIS SHOULD REALLY BE LOADED FROM A FILE
static const wstring	W_GO_TO_MM_COMMAND		= L"Go To Main Menu";
static const wstring	W_START_COMMAND			= L"Start";
static const wstring	W_EXIT_COMMAND			= L"Exit";
static const wstring	W_QUIT_COMMAND			= L"Quit";
static const wstring	W_CONTROLS_COMMAND		= L"Controls";
static const wstring	W_GREEN_CURSOR_PATH		= L"data/gui/cursor/cursor.png";
static const wstring	W_RED_CURSOR_PATH		= L"data/gui/cursor/red_cursor.png";
static const wstring	W_SPLASH_SCREEN_PATH	= L"data/gui/overlays/twisted_road_splash_screen_overlay.png";
static const wstring	W_MAIN_MENU_PATH		= L"data/gui/overlays/twisted_road_main_screen_overlay.png";
static const wstring	W_CONTROLS_PATH			= L"data/gui/overlays/controls_overlay.png";
static const wstring	W_START_IMAGE_PATH		= L"data/gui/buttons/button_newGame_normal.png";
static const wstring	W_START_IMAGE_MO_PATH	= L"data/gui/buttons/button_newGame_hilight.png";
static const wstring	W_EXIT_IMAGE_PATH		= L"data/gui/buttons/button_exit_normal.png";
static const wstring	W_EXIT_IMAGE_MO_PATH	= L"data/gui/buttons/button_exit_hilight.png";
static const wstring	W_CONTROLS_IMAGE_PATH		= L"data/gui/buttons/button_controls_normal.png";
static const wstring	W_CONTROLS_IMAGE_MO_PATH	= L"data/gui/buttons/button_controls_hilight.png";
static const wstring	W_QUIT_IMAGE_PATH		= L"data/gui/buttons/button_quit_normal.png";
static const wstring	W_QUIT_IMAGE_MO_PATH	= L"data/gui/buttons/button_quit_hilight.png";

// CONSTANTS FOR AUDIO
static const char*	W_TITLE_MUSIC = "data/audio/title.mp3";
static const char*	W_GAMEPLAY1_MUSIC = "data/audio/gameplay1.mp3";
static const char*	W_GAMEPLAY2_MUSIC = "data/audio/gameplay2.mp3";
static const char*	W_GAMEPLAY3_MUSIC = "data/audio/gameplay3.mp3";
static const char*	W_GAMEPLAY4_MUSIC = "data/audio/gameplay4.mp3";
static const char*	W_GAMEPLAY5_MUSIC = "data/audio/gameplay5.mp3";
static const char*	W_GRAV_SOUND = "data/audio/gravityShift.mp3";
static const char*	W_JUMP_SOUND = "data/audio/jump.mp3";
static const char*	W_DIE_SOUND = "data/audio/die.mp3";

// FOR OUR SPRITE
static const wstring	SPRITE_TYPES_DIR = L"data/sprite_types/";
static const wstring	SPRITE_TYPES_LIST = SPRITE_TYPES_DIR + L"sprite_type_list.xml";
static const wstring	JUMPING = L"JUMPING";

// FOR THE GAME WORLD
static const float		MAX_VIEWPORT_AXIS_VELOCITY = 20.0f;
static const float		W_GRAVITY = 0.8f;
static const float		JUMPING_BOT_MIN_CYCLES = 30;
static const float		JUMPING_BOT_MAX_CYCLES = 120;
static const float		JUMPING_BOT_MAX_VELOCITY = 40;
static const float		PLAYER_INIT_X = 80.0f;
static const float		PLAYER_INIT_Y = 500.0f;
static const float		YELLOW_INIT_X = PLAYER_INIT_X + 1100.0f;
static const float		YELLOW_INIT_Y = PLAYER_INIT_Y + 500.0f;
static const float		JUMP_SPEED = -24.0f;
static const float		PLAYER_SPEED = 6.0f;
static const int		MIN_FPS = 5;
static const int		MAX_FPS = 100;
static const int		FPS_INC = 1;

static const wstring	ATTACKING_RIGHT(L"ATTACKING_RIGHT");
static const wstring	ATTACKING_LEFT(L"ATTACKING_LEFT");
static const wstring	IDLE(L"IDLE");

//NORMAL GRAVITY POSITIONS
static const wstring	LJUMP(L"LJUMP");
static const wstring	RJUMP(L"RJUMP");
static const wstring	LFALL(L"LFALL");
static const wstring	RFALL(L"RFALL");
static const wstring	LWALK(L"LWALK");
static const wstring	RWALK(L"RWALK");
static const wstring	LIDLE(L"LIDLE");
static const wstring	RIDLE(L"RIDLE");
static const wstring	LDEATH(L"LDEATH");
static const wstring	RDEATH(L"RDEATH");
static const wstring	LHIT(L"LHIT");
static const wstring	RHIT(L"RHIT");

//REVERSE GRAVITY POSITIONS
static const wstring	ULJUMP(L"ULJUMP");
static const wstring	URJUMP(L"URJUMP");
static const wstring	ULFALL(L"ULFALL");
static const wstring	URFALL(L"URFALL");
static const wstring	ULWALK(L"ULWALK");
static const wstring	URWALK(L"URWALK");
static const wstring	ULIDLE(L"ULIDLE");
static const wstring	URIDLE(L"URIDLE");
static const wstring	ULDEATH(L"ULDEATH");
static const wstring	URDEATH(L"URDEATH");
static const wstring	ULHIT(L"ULHIT");
static const wstring	URHIT(L"URHIT");

//LEFT GRAVITY POSITIONS
static const wstring	LLJUMP(L"LLJUMP");
static const wstring	LRJUMP(L"LRJUMP");
static const wstring	LLFALL(L"LLFALL");
static const wstring	LRFALL(L"LRFALL");
static const wstring	LLWALK(L"LLWALK");
static const wstring	LRWALK(L"LRWALK");
static const wstring	LLIDLE(L"LLIDLE");
static const wstring	LRIDLE(L"LRIDLE");
static const wstring	LLDEATH(L"LLDEATH");
static const wstring	LRDEATH(L"LRDEATH");
static const wstring	LLHIT(L"LLHIT");
static const wstring	LRHIT(L"LRHIT");

//RIGHT GRAVITY POSITIONS
static const wstring	RLJUMP(L"RLJUMP");
static const wstring	RRJUMP(L"RRJUMP");
static const wstring	RLFALL(L"RLFALL");
static const wstring	RRFALL(L"RRFALL");
static const wstring	RLWALK(L"RLWALK");
static const wstring	RRWALK(L"RRWALK");
static const wstring	RLIDLE(L"RLIDLE");
static const wstring	RRIDLE(L"RRIDLE");
static const wstring	RLDEATH(L"RLDEATH");
static const wstring	RRDEATH(L"RRDEATH");
static const wstring	RLHIT(L"RLHIT");
static const wstring	RRHIT(L"RRHIT");


// USED FOR MOVEMENT
const unsigned int W_KEY = (unsigned int)'W';
const unsigned int A_KEY = (unsigned int)'A';
const unsigned int S_KEY = (unsigned int)'S';
const unsigned int D_KEY = (unsigned int)'D';
const unsigned int G_KEY = (unsigned int)'G';
const unsigned int P_KEY = (unsigned int)'P';
const unsigned int R_KEY = (unsigned int)'R';
const unsigned int UP_KEY = VK_UP;
const unsigned int DOWN_KEY = VK_DOWN;
const unsigned int LEFT_KEY = VK_LEFT;
const unsigned int RIGHT_KEY = VK_RIGHT;
const unsigned int SPACE_KEY = VK_SPACE;

// THIS IS JUST FOR SHOWING HOW THE CURSOR CAN BE CHANGED
const unsigned int C_KEY = (unsigned int)'C';
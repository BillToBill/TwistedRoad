#include "buggin_out_VS\stdafx.h"

// BugginOut GAME INCLUDES
#include "buggin_out\BugginOutButtonEventHandler.h"
#include "buggin_out\BugginOutDataLoader.h"
#include "buggin_out\BugginOut.h"
#include "buggin_out\BugginOutKeyEventHandler.h"
#include "buggin_out\BugginOutTextGenerator.h"

// GAME OBJECT INCLUDES
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\ai\bots\RandomJumpingBot.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\gui\ScreenGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\os\GameOS.h"
#include "sssf\text\GameText.h"

// WINDOWS PLATFORM INCLUDES
#include "sssf\platforms\Windows\WindowsOS.h"
#include "sssf\platforms\Windows\WindowsInput.h"
#include "sssf\platforms\Windows\WindowsTimer.h"

// DIRECTX INCLUDES
#include "sssf\platforms\DirectX\DirectXGraphics.h"
#include "sssf\platforms\DirectX\DirectXTextureManager.h"

// TMX MAP LOADING
#include "tmxmi\TMXMapImporter.h"

// ANIMATED SPRITE TYPE LOADING
#include "psti\PoseurSpriteTypesImporter.h"

/*
	loadGame - This method loads the setup game data into the game and
	constructs all the needed objects for the game to work.
*/
void BugginOutDataLoader::loadGame(Game *game, wstring gameInitFile)
{
	// AND LET'S READ IN THE GAME SETUP INFO
	// FIRST LOAD ALL THE PROPERTIES
	map<wstring,wstring> *properties = new map<wstring,wstring>();
	loadGameProperties(game, properties, gameInitFile);

	// WE NEED THE TITLE AND USE_FULLSCREEN_MODE TO INITIALIZE OUR WINDOW
	wstring titleProp = (*properties)[W_TITLE];
	wstring useFullscreenProp = (*properties)[W_USE_FULLSCREEN_MODE];
	bool useFullscreen = false;
	if (useFullscreenProp.compare(L"true") == 0)
		useFullscreen = true;

	// GET THE SCREEN WIDTH AND HEIGHT
	int screenWidth, screenHeight;
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;

	// MAKE A CUSTOM GameOS OBJECT (WindowsOS) FOR SOME WINDOWS
	// PLATFORM STUFF, INCLUDING A Window OF COURSE
	WindowsOS *bugginOutOS = new WindowsOS(	hInstance, 
										nCmdShow,
										useFullscreen,
										titleProp,
										screenWidth, screenHeight,
										game);
	
	int textFontSize;
	wstring textFontSizeProp = (*properties)[W_TEXT_FONT_SIZE];
	wstringstream(textFontSizeProp) >> textFontSize;

	// RENDERING WILL BE DONE USING DirectX
	DirectXGraphics *bugginOutGraphics = new DirectXGraphics(game);
	bugginOutGraphics->init(screenWidth, screenHeight);
	bugginOutGraphics->initGraphics(bugginOutOS, useFullscreen);
	bugginOutGraphics->initTextFont(textFontSize);

	// AND NOW LOAD THE COLORS THE GRAPHICS WILL USE
	// AS A COLOR KEY AND FOR RENDERING TEXT
	initColors(bugginOutGraphics, properties);

	// WE'LL USE WINDOWS PLATFORM METHODS FOR GETTING INPUT
	WindowsInput *bugginOutInput = new WindowsInput();

	// AND WINDOWS FOR THE TIMER AS WELL
	WindowsTimer *bugginOutTimer = new WindowsTimer();

	// NOW INITIALIZE THE Game WITH ALL THE
	// PLATFORM AND GAME SPECIFIC DATA WE JUST CREATED
	game->initPlatformPlugins(	(GameGraphics*)bugginOutGraphics,
								(GameInput*)bugginOutInput,
								(GameOS*)bugginOutOS,
								(GameTimer*)bugginOutTimer);

	// LOAD OUR CUSTOM TEXT GENERATOR, WHICH DRAWS
	// TEXT ON THE SCREEN EACH FRAME
	BugginOutTextGenerator *bugginOutTextGenerator = new BugginOutTextGenerator();
	bugginOutTextGenerator->initText(game);
	GameText *text = game->getText();
	text->initDebugFile(W_DEBUG_FILE);
	text->setTextGenerator((TextGenerator*)bugginOutTextGenerator);

	// INIT THE VIEWPORT TOO
	initViewport(game->getGUI(), properties);	

	// WE DON'T NEED THE PROPERTIES MAP ANYMORE, THE GAME IS ALL LOADED
	delete properties;
}

/*
	initColors - this helper method loads the color key, used for loading
	images, and the font color, used for rendering text.
*/
void BugginOutDataLoader::initColors(	GameGraphics *graphics,
									map<wstring,wstring> *properties)
{
	int fontRed, fontGreen, fontBlue;
	wstring fontRedProp = (*properties)[W_FONT_COLOR_RED];
	wstring fontGreenProp = (*properties)[W_FONT_COLOR_GREEN];
	wstring fontBlueProp = (*properties)[W_FONT_COLOR_BLUE];
	wstringstream(fontRedProp) >> fontRed;
	wstringstream(fontGreenProp) >> fontGreen;
	wstringstream(fontBlueProp) >> fontBlue;

	// COLOR USED FOR RENDERING TEXT
	graphics->setFontColor(fontRed, fontGreen, fontBlue);

	int keyRed, keyGreen, keyBlue;
	wstring keyRedProp = (*properties)[W_COLOR_KEY_RED];
	wstring keyGreenProp = (*properties)[W_COLOR_KEY_GREEN];
	wstring keyBlueProp = (*properties)[W_COLOR_KEY_BLUE];
	wstringstream(keyRedProp) >> keyRed;
	wstringstream(keyGreenProp) >> keyGreen;
	wstringstream(keyBlueProp) >> keyBlue;

	// COLOR KEY - COLOR TO BE IGNORED WHEN LOADING AN IMAGE
	// NOTE, IF YOU WISH TO USE PNG IMAGES THAT CONTAIN ALPHA
	// CHANNEL DATA, YOU DON'T NEED A COLOR KEY
	graphics->setColorKey(keyRed, keyGreen, keyBlue);
}

/*
	loadGUI - This method loads all the GUI assets described in the guiInitFile
	argument. Note that we are loading all GUI art for all GUIs when the application
	first starts. We'll learn a better technique later in the semester.
*/
void BugginOutDataLoader::loadGUI(Game *game, wstring guiInitFile)
{
	// WE'RE JUST GOING TO IGNORE THE GUI FILE FOR NOW.
	// FOR THE MOMENT WE ARE CALLING THIS HARD-CODED GUI LOADER
	hardCodedLoadGUIExample(game);
}

/*
	loadLevel - This method should load the data the level described by the
	levelInitFile argument in to the Game's game state manager.
*/
void BugginOutDataLoader::loadWorld(Game *game, wstring levelInitFile)
{
	int level = 1;
	// LOAD THE LEVEL'S BACKGROUND TILES
	TMXMapImporter tmxMapImporter;
	tmxMapImporter.loadWorld(game, W_LEVEL_1_DIR, levelInitFile);

	// LOAD THE LEVEL'S SPRITE IMAGES
	PoseurSpriteTypesImporter psti;
	psti.loadSpriteTypes(game, SPRITE_TYPES_LIST);

	// LET'S MAKE A PLAYER SPRITE
	// @TODO - IT WOULD BE BETTER TO LOAD THIS STUFF FROM A FILE
	GameStateManager *gsm = game->getGSM();
	Physics *physics = gsm->getPhysics();
	SpriteManager *spriteManager = gsm->getSpriteManager();
	AnimatedSprite *player = spriteManager->getPlayer();
	b2World *world = gsm->getPhysics()->getBoxWorld();
	// NOTE THAT RED BOX MAN IS SPRITE ID 2
	AnimatedSpriteType *playerSpriteType = spriteManager->getSpriteType(0);
	player->setSpriteType(playerSpriteType);

	// Box2D Setup

	//Setup the world - give each tile a body/fixture and add it to the world
	World *area = game->getGSM()->getWorld();
	physics->getBoxWorld()->SetGravity(physics->Normal_Grav);
	physics->CurrentGrav = physics->Normal_Grav;


	/*player->dead = false;
	player->setAlpha(255);
	player->setCurrentState(RFALL);
	player->setGrounded(false);
	PhysicalProperties *playerProps = player->getPhysicalProperties();
	playerProps->setX(PLAYER_INIT_X);
	playerProps->setY(PLAYER_INIT_Y);
	player->affixTightAABBBoundingVolume();
	player->setAsDynamicBox(physics->getBoxWorld());*/
	//makeRandomJumpingBot(game, r, 150.0f, 300.0f);
	//Setup the world - give each tile a body/fixture and add it to the world


	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody; //change body type
	b2PolygonShape boxShape;
	//boxShape.SetAsBox(16.0* 0.01f, 16.0* 0.01f);


	b2FixtureDef boxFixtureDef;
	//boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;

	vector<WorldLayer*> *layers = area->getLayers();
	for (int i = 0; i < area->getNumLayers(); i++)
	{
		WorldLayer *layer = layers->at(i);
		if (layer->hasCollidableTiles()) // For all the collidable tiles only
		{
			TiledLayer *tiledLayer = (TiledLayer*)layer;
			int cols = tiledLayer->getColumns();
			int rows = tiledLayer->getRows();
			int height = tiledLayer->getTileHeight();
			int width = tiledLayer->getTileWidth();
			Tile *tile, *prevTile = NULL, *nextTile = NULL;
			int firstCellRow, firstCellCol;

			// create a box2d b2Body for each collidable tile
			for (int j = 0; j < rows; j++)
			{
				int numBoxes = 0;
				for (int k = 0; k < cols; k++)
				{
					tile = tiledLayer->getTile(j, k);
					if (k - 1 > 0)
						prevTile = tiledLayer->getTile(j, k - 1);
					else
						prevTile = NULL;
					
					if (k + 1 < cols)
						nextTile = tiledLayer->getTile(j, k + 1);
					else
						nextTile = NULL;

					if ((*tile).collidable)
					{
						numBoxes++;
						
						if (prevTile == NULL || prevTile->collidable == false)
						{
							firstCellRow = j;
							firstCellCol = k;
						}

						if (nextTile == NULL || nextTile->collidable == false)
						{
							float newWidth = width * numBoxes;
							boxShape.SetAsBox(newWidth/2 * 0.01f, height/2 * 0.01f);
							boxFixtureDef.shape = &boxShape;

							float midRow = float(j + firstCellRow) / 2;
							float midCol = float(k + firstCellCol) / 2;

							float32 centerX = (float32(midCol * width)) * 0.01f - 0.16f;
							float32 centerY = (float32(midRow * height) - 16.0f) * 0.01f;

							myBodyDef.position.Set(centerX, centerY);
							b2Body* staticBody = world->CreateBody(&myBodyDef);
							staticBody->CreateFixture(&boxFixtureDef);
							spriteManager->addStaticBody(staticBody);
							numBoxes = 0;
						}

						/*myBodyDef.position.Set((float32(k * width) - 16.0f) * 0.01f, (float32(j * height) - 16.0f) * 0.01f);
						b2Body* staticBody = world->CreateBody(&myBodyDef);
						staticBody->CreateFixture(&boxFixtureDef);
						spriteManager->addStaticBody(staticBody);*/

					}
				}
			}
			
		}
	}


	// AND LET'S ADD A BUNCH OF RANDOM JUMPING BOTS, FIRST ALONG
	// A LINE NEAR THE TOP

	//Let's not and say we did.

	//AnimatedSpriteType *blockNoneType = spriteManager->getSpriteType(1);
	AnimatedSpriteType *blockLeftType = spriteManager->getSpriteType(1);
	AnimatedSpriteType *blockRightType = spriteManager->getSpriteType(2);
	//AnimatedSpriteType *blockHorizType = spriteManager->getSpriteType(4);
	AnimatedSpriteType *blockUpType = spriteManager->getSpriteType(4);
	AnimatedSpriteType *blockDownType = spriteManager->getSpriteType(5);
	//AnimatedSpriteType *blockVertType = spriteManager->getSpriteType(7);
	AnimatedSpriteType *exitType = spriteManager->getSpriteType(8);

	AnimatedSpriteType *flyerType = spriteManager->getSpriteType(9);
	AnimatedSpriteType *walkerType = spriteManager->getSpriteType(10);
	AnimatedSpriteType *rwalkerType = spriteManager->getSpriteType(11);
	AnimatedSpriteType *lwalkerType = spriteManager->getSpriteType(12);
	AnimatedSpriteType *uwalkerType = spriteManager->getSpriteType(13);
	// Add a directional block to the stage
	
	if (game->getCurrentLevelFileName() == W_LEVEL_1_NAME)
	{
		game->getGSM()->levelSwitchTrigger = false;
		//Gravity Reset
		world->SetGravity(physics->Normal_Grav);
		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY1_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(64.0f);
		playerProps->setY(656.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		//Set Blocks
		makeDirectionalBlock(game, blockUpType, 352.0f, 692.0f);

		//Set Enemies
		//Make a Walker
		/*makeEnemy(game, walkerType, 480.0f, 672.0f, 0);
		makeEnemy(game, flyerType, 450.0f, 250.0f, 1);
		makeEnemy(game, rwalkerType, 672.0f, 320.0f, 2);
		makeEnemy(game, lwalkerType, 32.0f, 320.0f, 3);
		makeEnemy(game, uwalkerType, 200.0f, 32.0f, 4);*/

		//Put the Exit in place
		makeExit(game, exitType, 320.0f, 75.0f);
	}

	if (game->getCurrentLevelFileName() == W_LEVEL_2_NAME)
	{
		//Gravity Reset
		world->SetGravity(physics->Normal_Grav);

		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY1_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(64.0f);
		playerProps->setY(404.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		makeEnemy(game, walkerType, 320.0f, 416.0f, 0);
		makeEnemy(game, rwalkerType, 673.0f, 121.0f, 2);
		makeEnemy(game, uwalkerType, 611.0f, 576.0f, 4);

		//Set Blocks
		makeDirectionalBlock(game, blockUpType, 300.0f, 433.0f);

		//Put the Exit in place
		makeExit(game, exitType, 664.0f, 292.0f);
	}

	if (game->getCurrentLevelFileName() == W_LEVEL_3_NAME)
	{
		//Gravity Reset
		world->SetGravity(physics->Normal_Grav);

		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY2_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(65.0f);
		playerProps->setY(650.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		makeEnemy(game, walkerType, 545.0f, 672.0f, 0);
		makeEnemy(game, uwalkerType, 350.0f, 257.0f, 4);

		//Set Blocks
		makeDirectionalBlock(game, blockUpType, 525.0f, 689.0f);
		makeDirectionalBlock(game, blockDownType, 365.0f, 242.0f);
		makeDirectionalBlock(game, blockUpType, 15.0f, 369.0f);
		makeDirectionalBlock(game, blockDownType, 652.0f, 15.0f);

		//Put the Exit in place
		makeExit(game, exitType, 670.0f, 124.0f);
	}

	if (game->getCurrentLevelFileName() == W_LEVEL_4_NAME)
	{
		//Gravity Reset
		world->SetGravity(physics->Normal_Grav);

		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY2_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(65.0f);
		playerProps->setY(662.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		//Set Blocks
		makeDirectionalBlock(game, blockLeftType, 247.0f, 692.0f);
		makeDirectionalBlock(game, blockLeftType, 690.0f, 150.0f);
		makeDirectionalBlock(game, blockRightType, 17.0f, 279.0f);

		//Put the Exit in place
		makeExit(game, exitType, 484.0f, 353.0f);
	}

	if (game->getCurrentLevelFileName() == W_LEVEL_5_NAME)
	{
		//Gravity Reset
		world->SetGravity(physics->Normal_Grav);

		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY3_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(65.0f);
		playerProps->setY(662.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		//Set Enemies
		makeEnemy(game, flyerType, 182.0f, 234.0f, 1);
		makeEnemy(game, flyerType, 182.0f, 513.0f, 1);
		makeEnemy(game, flyerType, 547.0f, 234.0f, 1);
		makeEnemy(game, flyerType, 547.0f, 513.0f, 1);

		//Set Blocks
		makeDirectionalBlock(game, blockUpType, 631.0f, 694.0f);
		makeDirectionalBlock(game, blockLeftType, 600.0f, 372.0f);
		makeDirectionalBlock(game, blockRightType, 529.0f, 289.0f);
		makeDirectionalBlock(game, blockLeftType, 690.0f, 86.0f);
		makeDirectionalBlock(game, blockDownType, 358.0f, 17.0f);
		makeDirectionalBlock(game, blockDownType, 16.0f, 17.0f);

		//Put the Exit in place
		makeExit(game, exitType, 352.0f, 413.0f);
	}

	if (game->getCurrentLevelFileName() == W_LEVEL_6_NAME)
	{
		//Gravity Reset
		world->SetGravity(physics->Normal_Grav);

		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY3_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(64.0f);
		playerProps->setY(662.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		//Set Enemies
		makeEnemy(game, uwalkerType, 300.0f, 162.0f, 4);
		makeEnemy(game, flyerType, 560.0f, 265.0f, 1);
		//makeEnemy(game, flyerType, 383.0f, 77.0f, 1);

		//Set Blocks
		makeDirectionalBlock(game, blockUpType, 689.0f, 689.0f);
		makeDirectionalBlock(game, blockLeftType, 688.0f, 552.0f);
		makeDirectionalBlock(game, blockDownType, 17.0f, 492.0f);
		makeDirectionalBlock(game, blockUpType, 531.0f, 561.0f);
		makeDirectionalBlock(game, blockDownType, 337.0f, 142.0f);

		//Put the Exit in place
		makeExit(game, exitType, 165.0f, 415.0f);
	}

	if (game->getCurrentLevelFileName() == W_LEVEL_7_NAME)
	{
		//Gravity Reset
		world->SetGravity(physics->Normal_Grav);

		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY4_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(64.0f);
		playerProps->setY(54.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		//Set Enemies
		makeEnemy(game, walkerType, 545.0f, 256.0f, 0);
		makeEnemy(game, flyerType, 608.0f, 673.0f, 1);
		makeEnemy(game, flyerType, 193.0f, 449.0f, 1);

		//Set Blocks
		makeDirectionalBlock(game, blockRightType, 17.0f, 172.0f);
		makeDirectionalBlock(game, blockRightType, 108.0f, 561.0f);
		makeDirectionalBlock(game, blockLeftType, 684.0f, 625.0f);

		//Put the Exit in place
		makeExit(game, exitType, 660.0f, 33.0f);
	}

	if (game->getCurrentLevelFileName() == W_LEVEL_8_NAME)
	{
		//Gravity Reset
		world->SetGravity(physics->Right_Grav);
		physics->CurrentGrav = physics->Right_Grav;
		game->getGSM()->gravR = true;

		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY4_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(60.0f);
		playerProps->setY(660.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		//Set Enemies
		makeEnemy(game, walkerType, 682.0f, 672.0f, 0);
		makeEnemy(game, walkerType, 404.0f, 672.0f, 0);
		makeEnemy(game, flyerType, 321.0f, 384.0f, 1);
		makeEnemy(game, flyerType, 552.0f, 284.0f, 1);
		//makeEnemy(game, flyerType, 448.0f, 128.0f, 1);

		//Set Blocks
		makeDirectionalBlock(game, blockDownType, 16.0f, 138.0f);
		makeDirectionalBlock(game, blockUpType, 525.0f, 690.0f);
		makeDirectionalBlock(game, blockLeftType, 688.0f, 140.0f);
		makeDirectionalBlock(game, blockUpType, 349.0f, 210.0f);
		makeDirectionalBlock(game, blockRightType, 210.0f, 273.0f);
		makeDirectionalBlock(game, blockDownType, 333.0f, 559.0f);

		//Put the Exit in place
		makeExit(game, exitType, 352.0f, 23.0f);
	}

	if (game->getCurrentLevelFileName() == W_LEVEL_9_NAME)
	{
		//Gravity Reset
		world->SetGravity(physics->Normal_Grav);

		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY5_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(64.0f);
		playerProps->setY(656.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		//Set Enemies
		makeEnemy(game, uwalkerType, 75.0f, 32.0f, 4);
		makeEnemy(game, flyerType, 193.0f, 384.0f, 1);
		makeEnemy(game, rwalkerType, 480.0f, 488.0f, 2);

		//Set Blocks
		makeDirectionalBlock(game, blockUpType, 241.0f, 690.0f);
		makeDirectionalBlock(game, blockLeftType, 242.0f, 50.0f);
		makeDirectionalBlock(game, blockRightType, 16.0f, 210.0f);
		makeDirectionalBlock(game, blockDownType, 305.0f, 113.0f);
		makeDirectionalBlock(game, blockLeftType, 690.0f, 17.0f);
		makeDirectionalBlock(game, blockUpType, 690.0f, 369.0f);

		//Put the Exit in place
		makeExit(game, exitType, 339.0f, 670.0f);
	}

	if (game->getCurrentLevelFileName() == W_LEVEL_10_NAME)
	{
		//Gravity Reset
		world->SetGravity(physics->Normal_Grav);

		//Sound Stuff
		channel->stop();
		system->createStream(W_GAMEPLAY5_MUSIC, FMOD_DEFAULT, 0, &song);
		system->playSound(song, 0, false, &channel);
		channel->setMode(FMOD_LOOP_NORMAL);
		channel->setLoopCount(-1);

		player->dead = false;
		player->setAlpha(255);
		player->setCurrentState(RFALL);
		player->setGrounded(false);
		PhysicalProperties *playerProps = player->getPhysicalProperties();
		playerProps->setX(64.0f);
		playerProps->setY(656.0f);
		player->affixTightAABBBoundingVolume();
		player->setAsPlayerBox(physics->getBoxWorld());

		//Set Enemies
		makeEnemy(game, flyerType, 129.0f, 436.0f, 1);
		//makeEnemy(game, flyerType, 225.0f, 140.0f, 1);
		makeEnemy(game, flyerType, 533.0f, 225.0f, 1);
		makeEnemy(game, walkerType, 417.0f, 673.0f, 0);

		//Set Blocks
		makeDirectionalBlock(game, blockRightType, 247.0f, 689.0f);
		makeDirectionalBlock(game, blockDownType, 17.0f, 434.0f);
		makeDirectionalBlock(game, blockLeftType, 691.0f, 17.0f);
		makeDirectionalBlock(game, blockLeftType, 408.0f, 369.0f);
		makeDirectionalBlock(game, blockDownType, 473.0f, 17.0f);
		makeDirectionalBlock(game, blockUpType, 119.0f, 210.0f);

		//Put the Exit in place
		makeExit(game, exitType, 32.0f, 32.0f);
	}
}


void BugginOutDataLoader::makeDirectionalBlock(Game *game, AnimatedSpriteType *blockSpriteType, float initX, float initY)
{
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	AnimatedSprite *block = new AnimatedSprite();
	PhysicalProperties *pp = block->getPhysicalProperties();
	pp->setPosition(initX, initY);
	block->setSpriteType(blockSpriteType);
	block->setCurrentState(L"IDLE");
	block->setAlpha(255);
	block->affixTightAABBBoundingVolume();
	spriteManager->addBlock(block);
	block->setAsBlock(game->getGSM()->getPhysics()->getBoxWorld(), blockSpriteType->getSpriteTypeID());
}

void BugginOutDataLoader::makeExit(Game *game, AnimatedSpriteType *exitSpriteType, float initX, float initY)
{
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	AnimatedSprite *exit = new AnimatedSprite();
	PhysicalProperties *pp = exit->getPhysicalProperties();
	pp->setPosition(initX, initY);
	exit->setSpriteType(exitSpriteType);
	exit->setCurrentState(L"IDLE");
	exit->setAlpha(255);
	exit->affixTightAABBBoundingVolume();
	spriteManager->addExit(exit);
	exit->setAsExit(game->getGSM()->getPhysics()->getBoxWorld());
}

void BugginOutDataLoader::makeEnemy(Game *game, AnimatedSpriteType *enemySpriteType, float initX, float initY, int numType)
{
	SpriteManager *spriteManager = game->getGSM()->getSpriteManager();
	AnimatedSprite *enemy = new AnimatedSprite();
	PhysicalProperties *pp = enemy->getPhysicalProperties();
	pp->setPosition(initX, initY);
	enemy->originalx = initX;
	enemy->originaly = initY;
	enemy->setSpriteType(enemySpriteType);
	enemy->setCurrentState(L"RIDLE");
	enemy->setAlpha(255);
	enemy->affixTightAABBBoundingVolume();
	
	

	//Set As Different things depending on numType
	if (numType == 0) //Walker
	{
		enemy->setAsDynamicBox(game->getGSM()->getPhysics()->getBoxWorld());
		enemy->body->SetUserData(NULL);
		enemy->body->SetUserData(L"walker");
		spriteManager->addEnemy(enemy);
	}

	if (numType == 1) //Flyer
	{
		enemy->setAsDynamicBox(game->getGSM()->getPhysics()->getBoxWorld());
		enemy->body->SetGravityScale(0.0f);
		enemy->body->SetUserData(NULL);
		enemy->body->SetUserData(L"flyer");
		spriteManager->addEnemy(enemy);
	}

	if (numType == 2) //RWalker
	{
		enemy->setAsDynamicBox(game->getGSM()->getPhysics()->getBoxWorld());
		enemy->body->SetGravityScale(0.0f);
		enemy->body->SetUserData(NULL);
		enemy->body->SetUserData(L"rwalker");
		spriteManager->addEnemy(enemy);
	}

	if (numType == 3) //LWalker
	{
		enemy->setAsDynamicBox(game->getGSM()->getPhysics()->getBoxWorld());
		enemy->body->SetGravityScale(0.0f);
		enemy->body->SetUserData(NULL);
		enemy->body->SetUserData(L"lwalker");
		spriteManager->addEnemy(enemy);
	}

	if (numType == 4) //UWalker
	{
		enemy->setAsDynamicBox(game->getGSM()->getPhysics()->getBoxWorld());
		enemy->body->SetGravityScale(0.0f);
		enemy->body->SetUserData(NULL);
		enemy->body->SetUserData(L"uwalker");
		spriteManager->addEnemy(enemy);
	}

	
}
/*
	initBugginOutGUI - This method builds a GUI for the BugginOut Game application.
	Note that we load all the GUI components from this method, including
	the ScreenGUI with Buttons and Overlays and the Cursor.
*/
void BugginOutDataLoader::hardCodedLoadGUIExample(Game *game)
{
	GameGUI *gui = game->getGUI();
	GameGraphics *graphics = game->getGraphics();
	DirectXTextureManager *guiTextureManager = (DirectXTextureManager*)graphics->getGUITextureManager();

	// SETUP THE CURSOR VIA OUR HELPER METHOD
	initCursor(gui, guiTextureManager);
	initSplashScreen(game, gui, guiTextureManager);
	initMainMenu(gui, guiTextureManager);
	initInGameGUI(gui, guiTextureManager);
}

/*
	initCursor - initializes a simple little cursor for the gui.
*/
void BugginOutDataLoader::initCursor(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// SETUP THE CURSOR
	vector<unsigned int> *imageIDs = new vector<unsigned int>();
	int imageID;

	// - FIRST LOAD THE GREEN CURSOR IMAGE
	imageID = guiTextureManager->loadTexture(W_GREEN_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - AND NOW THE RED ONE
	imageID = guiTextureManager->loadTexture(W_RED_CURSOR_PATH);
	imageIDs->push_back(imageID);

	// - NOW BUILD AND LOAD THE CURSOR
	Cursor *cursor = new Cursor();
	cursor->initCursor(	imageIDs,
						*(imageIDs->begin()),
						0,
						0,
						255,
						255,
						32,
						32);
	gui->setCursor(cursor);
}

/*
	initSplashScreen - initializes the game's splash screen gui.
*/
void BugginOutDataLoader::initSplashScreen(Game *game, GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	// NOW, FIRST LET'S ADD A SPLASH SCREEN GUI
	ScreenGUI *splashScreenGUI = new ScreenGUI();

	// WE'LL ONLY HAVE ONE IMAGE FOR OUR GIANT BUTTON
	unsigned int normalTextureID = guiTextureManager->loadTexture(W_SPLASH_SCREEN_PATH);
	unsigned int mouseOverTextureID = normalTextureID;

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							0,
							0,
							0,
							255,
							game->getGraphics()->getScreenWidth(),
							game->getGraphics()->getScreenHeight(),
							false,
							W_GO_TO_MM_COMMAND);
	splashScreenGUI->addButton(buttonToAdd);

	// AND REGISTER IT WITH THE GUI
	gui->addScreenGUI(GS_SPLASH_SCREEN, splashScreenGUI);
}

/*
	initMainMenu - initializes the game's main menu gui.
*/
void BugginOutDataLoader::initMainMenu(GameGUI *gui,	DirectXTextureManager *guiTextureManager)
{
	// NOW LET'S LOAD A MAIN MENU GUI SCREEN
	ScreenGUI *mainMenuGUI = new ScreenGUI();
	unsigned int imageID = guiTextureManager->loadTexture(W_MAIN_MENU_PATH);

	//Sound Stuff

	system->createStream(W_TITLE_MUSIC, FMOD_DEFAULT, 0, &song);
	system->playSound(song, 0, false, &channel);
	channel->setMode(FMOD_LOOP_NORMAL);
	channel->setLoopCount(-1);

	OverlayImage *imageToAdd = new OverlayImage();
	imageToAdd->x = 0;
	imageToAdd->y = 0;
	imageToAdd->z = 0;
	imageToAdd->alpha = 200;
	imageToAdd->width = 512;
	imageToAdd->height = 512;
	imageToAdd->imageID = imageID;
	mainMenuGUI->addOverlayImage(imageToAdd);

	// AND LET'S ADD AN EXIT BUTTON
	Button *buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs
	int normalTextureID = guiTextureManager->loadTexture(W_EXIT_IMAGE_PATH);
	int mouseOverTextureID = guiTextureManager->loadTexture(W_EXIT_IMAGE_MO_PATH);

	// - INIT THE EXIT BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							612,
							600,
							0,
							255,
							200,
							100,
							false,
							W_EXIT_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD A START BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs

	normalTextureID = guiTextureManager->loadTexture(W_START_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_START_IMAGE_MO_PATH);

	// - INIT THE START BUTTON
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							612,
							500,
							0,
							255,
							200,
							100,
							false,
							W_START_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD A CONTROLS BUTTON
	buttonToAdd = new Button();

	// - GET THE BUTTON COMMAND AND IMAGE IDs

	normalTextureID = guiTextureManager->loadTexture(W_CONTROLS_IMAGE_PATH);
	mouseOverTextureID = guiTextureManager->loadTexture(W_CONTROLS_IMAGE_MO_PATH);

	// - INIT THE CONTROLS BUTTON
	buttonToAdd->initButton(normalTextureID,
		mouseOverTextureID,
		612,
		700,
		0,
		255,
		200,
		100,
		false,
		W_CONTROLS_COMMAND);

	// AND NOW LOAD IT INTO A ScreenGUI
	mainMenuGUI->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_MAIN_MENU,		mainMenuGUI);
}

/*
	initInGameGUI - initializes the game's in-game gui.
*/
void BugginOutDataLoader::initInGameGUI(GameGUI *gui, DirectXTextureManager *guiTextureManager)
{
	// NOW ADD THE IN-GAME GUI
	ScreenGUI *inGameGUI = new ScreenGUI();

	unsigned int normalTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_PATH);
	unsigned int mouseOverTextureID = guiTextureManager->loadTexture(W_QUIT_IMAGE_MO_PATH);

	// INIT THE QUIT BUTTON
	Button *buttonToAdd = new Button();
	buttonToAdd->initButton(normalTextureID, 
							mouseOverTextureID,
							0,
							0,
							0,
							255,
							200,
							100,
							false,
							W_QUIT_COMMAND);
	inGameGUI->addButton(buttonToAdd);

	// AND LET'S ADD OUR SCREENS
	gui->addScreenGUI(GS_GAME_IN_PROGRESS,	inGameGUI);
}

/*
	initViewport - initializes the game's viewport.
*/
void BugginOutDataLoader::initViewport(GameGUI *gui, map<wstring,wstring> *properties)
{
	// AND NOW SPECIFY THE VIEWPORT SIZE AND LOCATION. NOTE THAT IN THIS EXAMPLE,
	// WE ARE PUTTING A TOOLBAR WITH A BUTTON ACCROSS THE NORTH OF THE APPLICATION.
	// THAT TOOLBAR HAS A HEIGHT OF 64 PIXELS, SO WE'LL MAKE THAT THE OFFSET FOR
	// THE VIEWPORT IN THE Y AXIS
	Viewport *viewport = gui->getViewport();

	int viewportOffsetX, viewportOffsetY, toggleOffsetY, screenWidth, screenHeight;
	wstring viewportOffsetXProp = (*properties)[W_VIEWPORT_OFFSET_X];
	wstring viewportOffsetYProp = (*properties)[W_VIEWPORT_OFFSET_Y];
	wstring toggleOffsetYProp = (*properties)[W_TOGGLE_OFFSET_Y];
	wstring screenWidthProp = (*properties)[W_SCREEN_WIDTH];
	wstring screenHeightProp = (*properties)[W_SCREEN_HEIGHT];
	wstringstream(viewportOffsetXProp) >> viewportOffsetX;
	wstringstream(viewportOffsetYProp) >> viewportOffsetY;
	wstringstream(toggleOffsetYProp) >> toggleOffsetY;
	wstringstream(screenWidthProp) >> screenWidth;
	wstringstream(screenHeightProp) >> screenHeight;
	int viewportWidth = screenWidth - viewportOffsetX;
	int viewportHeight = screenHeight - viewportOffsetY;
	viewport->setViewportWidth(viewportWidth);
	viewport->setViewportHeight(viewportHeight);
	viewport->setViewportOffsetX(viewportOffsetX);
	viewport->setViewportOffsetY(viewportOffsetY);
	viewport->setToggleOffsetY(toggleOffsetY);
}

void BugginOutDataLoader::FMODErrorCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		exit(-1);
	}
}

void BugginOutDataLoader::initAudio()
{
	// Create FMOD interface object
	result = FMOD::System_Create(&system);
	FMODErrorCheck(result);

	// Initialise FMOD
	result = system->init(100, FMOD_INIT_NORMAL, 0);
	FMODErrorCheck(result);
}

void BugginOutDataLoader::remotePlaySound(FMOD::Sound *sound)
{
	system->playSound(sound, 0, false, &channel2);
}

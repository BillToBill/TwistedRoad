/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugginOutDataLoader.h

	This class provides a custom importer for the BugginOutGame to import
	game data, gui data, and world (i.e. level) data.
*/
#pragma once
#include "buggin_out_VS\stdafx.h"
#include "sssf\data_loader\GameDataLoader.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\platforms\DirectX\DirectXTextureManager.h"
#include "fmod.hpp"
#include "fmod_errors.h"

class BugginOutDataLoader : public GameDataLoader
{
private:
	// WE NEED THESE GUYS TO INIT OUR WINDOWS WINDOW
	HINSTANCE hInstance;
	int nCmdShow;


public:
	BugginOutDataLoader()	{}
	~BugginOutDataLoader()	{}
	FMOD::System *system;
	FMOD_RESULT result;
	FMOD::Sound *song;
	FMOD::Sound *gravSound;
	FMOD::Sound *jumpSound;
	FMOD::Sound *dieSound;
	FMOD::Channel *channel;
	FMOD::Channel *channel2; //For Sound Effects

	// INLINED MUTATOR METHOD
	void initWinHandle(HINSTANCE initHInstance, int initNCmdShow)
	{
		hInstance = initHInstance;
		nCmdShow = initNCmdShow;
	}

	void initGravSound(const char* filename)
	{
		system->createSound(filename, FMOD_DEFAULT, 0, &gravSound);
	}

	void initJumpSound(const char* filename)
	{
		system->createSound(filename, FMOD_DEFAULT, 0, &jumpSound);
	}

	void initDieSound(const char* filename)
	{
		system->createSound(filename, FMOD_DEFAULT, 0, &dieSound);
	}

	// THESE SHOULD BE LOADING DATA FROM FILES. THEY
	// ARE ALL DEFINED IN BugginOutDataLoader.cpp
	void loadGame(Game *game, wstring gameInitFile);
	void loadGUI(Game *game, wstring guiInitFile);
	void loadWorld(Game *game, wstring levelInitFile);

	// THESE ARE HARD-CODED EXAMPLES OF GUI DATA LOADING
	void hardCodedLoadGUIExample(Game *game);

	// SOME HELPER METHODS FOR SETTING UP THE GAME
	void initColors(GameGraphics *graphics,	map<wstring,wstring> *properties);
	void initViewport(GameGUI *gui, map<wstring,wstring> *properties);
	void addLife(Game *game, AnimatedSpriteType *livesType, int x, int y);
	void makeRandomJumpingBot(Game *game, AnimatedSpriteType *randomJumpingBotType, float initX, float initY);
	void makeDirectionalBlock(Game *game, AnimatedSpriteType *blockSpriteType, float initX, float initY);
	void makeExit(Game *game, AnimatedSpriteType *exitSpriteType, float initX, float initY);
	void makeEnemy(Game *game, AnimatedSpriteType *enemySpriteType, float initX, float initY, int numType);
	void FMODErrorCheck(FMOD_RESULT result);

	// AND SOME HELPER METHODS FOR LOADING THE GUI
	void initCursor(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initSplashScreen(Game *game, GameGUI *gui,	DirectXTextureManager *guiTextureManager);
	void initMainMenu(GameGUI *gui,	DirectXTextureManager *guiTextureManager);
	void initInGameGUI(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initAudio();
	void remotePlaySound(FMOD::Sound *sound);



};
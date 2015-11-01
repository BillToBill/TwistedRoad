/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	SpriteManager.h

	This class manages all of the sprites in a given game level. Note
	that the player sprite is also managed by this class.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\ai\BotRecycler.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"

class SpriteManager
{
private:
	// NOTE THAT MULTIPLE SPRITES MAY SHARE ARTWORK, SO SPRITE TYPES
	// SPECIFIES A TYPE OF SPRITE, OF WHICH THERE MAY BE MANY INSTANCES
	vector<AnimatedSpriteType*> spriteTypes;

	// THESE ARE THE BOTS IN THE GAME, LIKE ENEMIES, ROCKETS, OR ANYTHING
	// THAT MOVES AROUND AND IS NOT THE PLAYER
	list<Bot*> bots;
	list<AnimatedSprite*> blocks;
	list<AnimatedSprite*> exits;
	list<AnimatedSprite*> enemies;
	AnimatedSprite *exit;
	list<b2Body*> staticBodies;

	// AND THIS IS THE PLAYER. AS-IS, WE ONLY ALLOW FOR ONE PLAYER AT A TIME
	AnimatedSprite player;
	int playerHP = 10;
	int playerLives = 3;
	list<AnimatedSprite*> lives;

	// AND THIS IS THE YELLOW FLOATING MAN.
	AnimatedSprite yellowMan;

	// THE BotRecycler MAKES SURE WE DON'T HAVE TO CONSTRUCT BOTS WHENEVER
	// WE NEED TO SPAWN THEM, INSTEAD IT WILL RECYCLE THEM FOR US
	BotRecycler recyclableBots;

public:
	// NOTHING TO INIT OR DESTROY
	SpriteManager()		{}
	~SpriteManager()	{}

	// INLINED ACCESSOR METHODS
	int						getNumberOfSprites()	{ return bots.size();		}
	AnimatedSprite*			getPlayer()				{ return &player;			}
	AnimatedSprite*			getYellowMan()			{ return &yellowMan; }
	list<Bot*>::iterator	getBotsIterator()		{ return bots.begin();		}
	list<b2Body*>::iterator getStaticBodiesIterator() { return staticBodies.begin(); };
	list<b2Body*>::iterator getEndOfStaticBodiesIterator() { return staticBodies.end(); };
	list<AnimatedSprite*>::iterator getExitsIterator()		{ return exits.begin(); };
	list<AnimatedSprite*>::iterator getEndOfExitsIterator() { return exits.end(); };
	list<AnimatedSprite*>::iterator	getBlocksIterator()		{ return blocks.begin(); }
	list<AnimatedSprite*>::iterator getEndOfBlocksIterator() { return blocks.end(); }
	list<AnimatedSprite*>::iterator	getEnemyIterator()		{ return enemies.begin(); }
	list<AnimatedSprite*>::iterator getEndOfEnemyIterator() { return enemies.end(); }
	list<Bot*>::iterator	getEndOfBotsIterator()	{ return bots.end();		}
	list<AnimatedSprite*>::iterator getLivesIterator()	{ return lives.begin(); }

	void					clearStaticBodies()		{ staticBodies.clear(); }

	int						getPlayerHP()			{ return playerHP; }
	b2Body*					getExitBody()				{ return exit->body; }
	int						getPlayerLives()		{ return playerLives; }

	void					damagePlayer()			{ playerHP--; }
	void					healPlayer()			{ playerHP = playerHP + (playerHP * 0.1); }
	void					loseLife()				{ playerLives--; }

	void				addStaticBody(b2Body* body) { staticBodies.push_back(body); };

	// METHODS DEFINED IN SpriteManager.cpp
	void				addBot(Bot *botToAdd);
	void				addBlock(AnimatedSprite *blockToAdd);
	void				addLife(AnimatedSprite *life);
	void				addExit(AnimatedSprite *addExit);
	void				addEnemy(AnimatedSprite *addExit);
	void				addSpriteItemsToRenderList(Game *game);
	void				negativeDeltaMovement(float x, float y);
	void				positiveDeltaMovement(float x, float y);
	unsigned int		addSpriteType(AnimatedSpriteType *spriteTypeToAdd);
	void				addSpriteToRenderList(AnimatedSprite *sprite, RenderList *renderList, Viewport *viewport);
	void				clearSprites();
	AnimatedSpriteType* getSpriteType(unsigned int typeIndex);
	Bot*				removeBot(Bot *botToRemove);
	void				unloadSprites();
	void				update(Game *game);
};
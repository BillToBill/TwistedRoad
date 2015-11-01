/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

			Billy Gibson
			108592258

	SpriteManager.cpp

	See SpriteManager.h for a class description.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\state\GameStateManager.h"

/*
	addSpriteToRenderList - This method checks to see if the sprite
	parameter is inside the viewport. If it is, a RenderItem is generated
	for that sprite and it is added to the render list.
*/
void SpriteManager::addSpriteToRenderList(AnimatedSprite *sprite,
										  RenderList *renderList,
										  Viewport *viewport)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();
	PhysicalProperties *pp = sprite->getPhysicalProperties();

	// IS THE SPRITE VIEWABLE?
	if (viewport->areWorldCoordinatesInViewport(	
									pp->getX(),
									pp->getY(),
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight()))
	{
		// SINCE IT'S VIEWABLE, ADD IT TO THE RENDER LIST
		RenderItem itemToAdd;
		itemToAdd.id = sprite->getFrameIndex();
		renderList->addRenderItem(	sprite->getCurrentImageID(),
									/*sprite->body->GetPosition().x*/ pp->round(pp->getX()-viewport->getViewportX()),
									/*sprite->body->GetPosition().y*/  pp->round(pp->getY() - viewport->getViewportY()),
									pp->round(pp->getZ()),
									sprite->getAlpha(),
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight(),
									sprite->getRotationInRadians());
	}
}

/*
	addSpriteItemsToRenderList - This method goes through all of the sprites,
	including the player sprite, and adds the visible ones to the render list.
	This method should be called each frame.
*/
void SpriteManager::addSpriteItemsToRenderList(	Game *game)
{
	GameStateManager *gsm = game->getGSM();
	GameGUI *gui = game->getGUI();
	if (gsm->isWorldRenderable())
	{
		GameGraphics *graphics = game->getGraphics();
		RenderList *renderList = graphics->getWorldRenderList();
		Viewport *viewport = gui->getViewport();

		// ADD THE PLAYER SPRITE
		addSpriteToRenderList(&player, renderList, viewport);


		// NOW ADD THE REST OF THE SPRITES
		list<AnimatedSprite*>::iterator botIterator;
		botIterator = enemies.begin();
		while (botIterator != enemies.end())
		{			
			AnimatedSprite *bot = (*botIterator);
			addSpriteToRenderList(bot, renderList, viewport);
			botIterator++;
		}

		// NOW ADD THE REST OF THE SPRITES
		list<AnimatedSprite*>::iterator blockIterator;
		blockIterator = blocks.begin();
		while (blockIterator != blocks.end())
		{
			AnimatedSprite *block = (*blockIterator);
			addSpriteToRenderList(block, renderList, viewport);
			blockIterator++;
		}

		list<AnimatedSprite*>::iterator exitIt;
		exitIt = exits.begin();
		while (exitIt != exits.end())
		{
			AnimatedSprite *exit = (*exitIt);
			addSpriteToRenderList(exit, renderList, viewport);
			exitIt++;
		}
	}
}


void SpriteManager::negativeDeltaMovement(float x, float y)
{
	list<AnimatedSprite*>::iterator botIterator;
	botIterator = enemies.begin();
	while (botIterator != enemies.end())
	{
		AnimatedSprite *bot = (*botIterator);

		if (bot->body->GetPosition().x == x){
			if (bot->body->GetPosition().y == y)
			{
				bot->deltaMove = -0.01f;
			}
		}
		botIterator++;
	}
}

void SpriteManager::positiveDeltaMovement(float x, float y)
{
	list<AnimatedSprite*>::iterator botIterator;
	botIterator = enemies.begin();
	while (botIterator != enemies.end())
	{
		AnimatedSprite *bot = (*botIterator);

		if (bot->body->GetPosition().x == x){
			if (bot->body->GetPosition().y == y)
			{
				bot->deltaMove = 0.01f;
			}
		}
		botIterator++;
	}
}

/*
	addSprite - This method is for adding a new sprite to 
	this sprite manager. Once a sprite is added it can be 
	scheduled for rendering.
*/
void SpriteManager::addBot(Bot *botToAdd)
{
	bots.push_back(botToAdd);
}

void SpriteManager::addBlock(AnimatedSprite *blockToAdd)
{
	blocks.push_back(blockToAdd);
}

void SpriteManager::addLife(AnimatedSprite *life)
{
	lives.push_back(life);
}

void SpriteManager::addExit(AnimatedSprite *addExit)
{
	exits.push_back(addExit);
	exit = addExit;
}

void SpriteManager::addEnemy(AnimatedSprite *enemy)
{
	enemies.push_back(enemy);
	
}

/*
	addSpriteType - This method is for adding a new sprite
	type. Note that one sprite type can have many sprites. For
	example, we may say that there may be a "Bunny" type of
	sprite, and specify properties for that type. Then there might
	be 100 different Bunnies each with their own properties, but that
	share many things in common according to what is defined in
	the shared sprite type object.
*/
unsigned int SpriteManager::addSpriteType(AnimatedSpriteType *spriteTypeToAdd)
{
	spriteTypes.push_back(spriteTypeToAdd);
	return spriteTypes.size()-1;
}

/*
	clearSprites - This empties all of the sprites and sprite types.
*/
void SpriteManager::clearSprites()
{
	spriteTypes.clear();
	bots.clear();
}

/*
	getSpriteType - This gets the sprite type object that corresponds
	to the index argument.
*/
AnimatedSpriteType* SpriteManager::getSpriteType(unsigned int typeIndex)
{
	if (typeIndex < spriteTypes.size())
		return spriteTypes.at(typeIndex);
	else
		return NULL;
}

/*
	unloadSprites - This method removes all artwork from memory that
	has been allocated for game sprites.
*/
void SpriteManager::unloadSprites()
{
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
	blocks.clear();
	exits.clear();
	enemies.clear();
}

Bot* SpriteManager::removeBot(Bot *botToRemove)
{
	return NULL;
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
}

/*
	update - This method should be called once per frame. It
	goes through all of the sprites, including the player, and calls their
	update method such that they may update themselves.
*/
void SpriteManager::update(Game *game)
{
	// UPDATE THE PLAYER SPRITE
		
		player.updateSprite();
		player.getPhysicalProperties()->setX(player.body->GetPosition().x / 0.01f);
		player.getPhysicalProperties()->setY(player.body->GetPosition().y / 0.01f);

		if (game->getGSM()->gravN)
		{
			//Remake the proper fixture
			b2PolygonShape box = player.getBox();
			b2FixtureDef fixtureDef = player.getFixDef();
			box.SetAsBox(player.getBoundingVolume()->getWidth() / 2 * 0.01f, player.getBoundingVolume()->getHeight() / 2 * 0.01f);
			fixtureDef.shape = &box;
			fixtureDef.density = 15.0f;
			fixtureDef.friction = 1.0f;
			player.body->CreateFixture(&fixtureDef);
			game->getGSM()->gravN = false;
		}

		if (game->getGSM()->gravR)
		{
			//Remake the proper fixture
			b2PolygonShape box = player.getBox();
			b2FixtureDef fixtureDef = player.getFixDef();
			box.SetAsBox(player.getBoundingVolume()->getHeight() / 2 * 0.01f, player.getBoundingVolume()->getWidth() / 2 * 0.01f);
			fixtureDef.shape = &box;
			fixtureDef.density = 15.0f;
			fixtureDef.friction = 1.0f;
			player.body->CreateFixture(&fixtureDef);
			game->getGSM()->gravR = false;
		}

		if (game->getGSM()->gravU)
		{
			//Remake the proper fixture
			b2PolygonShape box = player.getBox();
			b2FixtureDef fixtureDef = player.getFixDef();
			box.SetAsBox(player.getBoundingVolume()->getWidth() / 2 * 0.01f, player.getBoundingVolume()->getHeight() / 2 * 0.01f);
			fixtureDef.shape = &box;
			fixtureDef.density = 15.0f;
			fixtureDef.friction = 1.0f;
			player.body->CreateFixture(&fixtureDef);
			game->getGSM()->gravU = false;
		}

		if (game->getGSM()->gravL)
		{
			//Remake the proper fixture
			b2PolygonShape box = player.getBox();
			b2FixtureDef fixtureDef = player.getFixDef();
			box.SetAsBox(player.getBoundingVolume()->getHeight() / 2 * 0.01f, player.getBoundingVolume()->getWidth() / 2 * 0.01f);
			fixtureDef.shape = &box;
			fixtureDef.density = 15.0f;
			fixtureDef.friction = 1.0f;
			player.body->CreateFixture(&fixtureDef);
			game->getGSM()->gravL = false;
		}

		// NOW ADD THE REST OF THE SPRITES
		list<AnimatedSprite*>::iterator blockIterator;
		blockIterator = blocks.begin();
		while (blockIterator != blocks.end())
		{
			AnimatedSprite *block = (*blockIterator);
			block->getPhysicalProperties()->setX(block->body->GetPosition().x / 0.01f + 16.0f);
			block->getPhysicalProperties()->setY(block->body->GetPosition().y / 0.01f + 16.0f);
			blockIterator++;
		}

		// NOW UPDATE THE REST OF THE SPRITES
		list<AnimatedSprite*>::iterator botIterator;
		botIterator = enemies.begin();
		while (botIterator != enemies.end())
		{
			AnimatedSprite *bot = (*botIterator);
			bot->updateSprite();
			bot->getPhysicalProperties()->setX(bot->body->GetPosition().x / 0.01f);
			bot->getPhysicalProperties()->setY(bot->body->GetPosition().y / 0.01f);
			
			bot->body->SetGravityScale(0);

			if (bot->body->GetUserData() == L"walker" || bot->body->GetUserData() == L"uwalker")
			{
				bot->body->SetTransform(b2Vec2(bot->body->GetPosition().x + bot->deltaMove, bot->body->GetPosition().y), 0.0f);
				
				if ((bot->body->GetPosition().x + bot->deltaMove) / 0.01f > bot->originalx + 50.0f && bot->deltaMove > 0)
					bot->deltaMove *= -1;

				else if ((bot->body->GetPosition().x + bot->deltaMove) / 0.01f < bot->originalx - 50.0f && bot->deltaMove < 0)
					bot->deltaMove *= -1;

			}

			else if (bot->body->GetUserData() == L"rwalker" || bot->body->GetUserData() == L"lwalker")
			{
				bot->body->SetTransform(b2Vec2(bot->body->GetPosition().x, bot->body->GetPosition().y + bot->deltaMove), 0.0f);
				
				if ((bot->body->GetPosition().y + bot->deltaMove) / 0.01f > bot->originaly + 50.0f)
					bot->deltaMove *= -1;

				else if ((bot->body->GetPosition().y + bot->deltaMove) / 0.01f < bot->originaly - 50.0f)
					bot->deltaMove *= -1;
			}

			if (player.dead)
			{
				//bot->deltaMove = 0;
			}
			botIterator++;
		}

		list<AnimatedSprite*>::iterator exitIt;
		exitIt = exits.begin();
		while (exitIt != exits.end())
		{
			AnimatedSprite *exit = (*exitIt);
			exit->updateSprite();
			exitIt++;
		}

		

		if (player.dead)
		{
			player.timeSinceDeath++;
		}

		if (player.timeSinceDeath == 90)
		{
			player.timeSinceDeath = 0;
			game->getGSM()->levelResetTrigger = true;
		}
	
}
/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

			Billy Gibson
			108592258

	Physics.cpp

	See Physics.h for a class description.
*/

#include "sssf_VS\stdafx.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\physics\Collision.h"
#include "sssf\gsm\physics\CollidableObject.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\gsm\world\SparseLayer.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gsm\world\Tile.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gsm\world\WorldLayer.h"
#include "Box2D\Box2D.h"
#include <vector>
#include <list>

/*
	The constructor initializes the data structures and loads
	the necessary ones with recyclable objects for collision tests.
*/
Physics::Physics()
{
	// DEFAULT GRAVITY IS 1.0f
	gravity = 9.8f*GRAVITY_SCALE;
	//grav = b2Vec2(0.0f, DEFAULT_GRAVITY);

	//boxWorld = b2World(grav);
}

/*
	The destructor deletes all the recyclable objects.
*/
Physics::~Physics()
{
	//Delete the Box2DWorld to delete all bodies/joints within it
	
	//delete &boxWorld;
	
}

/*
	This is where all game physics starts each frame. It is called each frame 
	by the game statem manager after player input and AI have been processed. It
	updates the physical state of all dynamic objects in the game and
	moves all objects to their end of frame positions, updates all necessary
	object velocities, and calls all collision event handlers.
*/
void Physics::update(Game *game)
{
	if (this->activated)
		boxWorld.Step(timeStep, velocityIterations, positionIterations);

}


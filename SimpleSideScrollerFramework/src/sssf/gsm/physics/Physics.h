/*	
	Author: Richard McKenna

	Physics.h

	This class will be used to manage all game collisions
	and physics. This includes collision detection, and resolution.
	Each frame we will update the collided objects velocities and
	positions accordingly.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\physics\Collision.h"
#include "sssf\gsm\physics\CollidableObject.h"
#include "sssf\gsm\physics\CollisionListener.h"
#include "sssf\gsm\world\World.h"
#include "sssf\gsm\world\TiledLayer.h"
#include "sssf\gsm\world\Tile.h"
#include "Box2D\Box2D.h"

const float EPSILON = 0.00001f;
const float32 GRAVITY_SCALE = 9.8f;
const float BUFFER_BETWEEN_OBJECTS = 0.2f;
const float NUDGE_VELOCITY = 0.3f;
const float ENERGY_LOSS = 0.95f;

class Physics
{
//private:
public:
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 10;
	int32 positionIterations = 8;
	// THIS IS APPLIED TO EVERY SPRITE EVERY FRAME
	float gravity;
	b2Vec2 Normal_Grav = b2Vec2(0.0f,GRAVITY_SCALE);
	b2Vec2 Reverse_Grav = b2Vec2(0.0f, -GRAVITY_SCALE);
	b2Vec2 Right_Grav = b2Vec2(GRAVITY_SCALE, 0.0f);
	b2Vec2 Left_Grav = b2Vec2(-GRAVITY_SCALE, 0.0f);
	

	b2World boxWorld = b2World(Normal_Grav);
	b2Vec2 CurrentGrav = Normal_Grav;
	// THIS IS THE CUSTOM EVENT HANDLER FOR PROVIDING GAME-SPECIFIC
	// EVENTS TO COLLISIONS BETWEEN GAME OBJECTS
	CollisionListener *collisionListener;

	// USED FOR TESTING PHYSICS BY TURNING IT ON AND OFF IN VARIOUS WAYS
	bool activated;
	bool activatedForSingleUpdate;

	// CONSTRUCDT/DESTRUCTOR
	Physics();
	~Physics();

	// INLINED GET/SET METHODS
	b2Vec2				getGravity()					{ return CurrentGrav;					}
	b2World*			getBoxWorld()					{ return &boxWorld;					}
	CollisionListener*	getCollisionListener()			{ return collisionListener;			}
	bool				isActivated()					{ return activated;					}
	bool				isActivatedForSingleUpdate()	{ return activatedForSingleUpdate;	}
	void				activateForSingleUpdate()										{ activatedForSingleUpdate = true;				}
	void				setCollisionListener(b2ContactListener* contactListener)	{ boxWorld.SetContactListener(contactListener); }

	// PUBLIC METHODS DEFINED INSIDE Physics.cpp - YOU ARE WELCOME TO ADD MORE OR CHANGE WHAT YOU LIKE
	void update(Game *game);

	// HELPER METHODS DEFINED INSIDE Physics.cpp - YOU ARE WELCOME TO ADD MORE AS YOU SEE FIT
private:
};


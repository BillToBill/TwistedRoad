#pragma once

#include "buggin_out\BugginOut.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\physics\CollisionListener.h"
#include "sssf\gsm\physics\Collision.h"

class BugginOutCollisionListener : public b2ContactListener
{
	Game* game;
	AnimatedSprite* player;
	b2Body* exit;
	

public:
	BugginOutCollisionListener(Game* g){ game = g; };
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};
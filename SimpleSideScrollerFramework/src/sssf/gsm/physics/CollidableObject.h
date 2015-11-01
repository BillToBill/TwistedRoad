#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\physics\AABB.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "Box2D/Box2D.h"

class CollidableObject
{
protected:
	AABB boundingVolume;
	bool currentlyCollidable;
	AABB sweptShape;
	PhysicalProperties pp;
	b2BodyDef bodyDef;
	b2PolygonShape box;
	b2FixtureDef fixtureDef;


public:
	b2Body* body;
	float deltaPos;
	float deltaMove = 0.01f;
	float originalx;
	float originaly;
	bool isColliding = false;
	CollidableObject()	{}
	~CollidableObject()	{}

	// CollidableObject.cpp METHODS	
	void setAsGroundBox(b2World *world);
	void setAsDynamicBox(b2World *world);
	void setAsPlayerBox(b2World *world);
	void setAsBlock(b2World *world, int blockType);
	void setAsExit(b2World *world);
	
	// INLINED METHODS
	bool				isCurrentlyCollidable()		{ return currentlyCollidable;	}
	AABB*				getBoundingVolume()			{ return &boundingVolume;		}
	AABB*				getSweptShape()				{ return &sweptShape;			}
	PhysicalProperties* getPhysicalProperties()		{ return &pp;					}
	void				startContact()				{ isColliding = true; }
	void				endContact()				{ isColliding = false; }
	b2PolygonShape		getBox()					{ return box;}
	b2FixtureDef		getFixDef()					{ return fixtureDef; }
	
	void setCurrentlyCollidable(bool initCurrentlyCollidable)
	{	currentlyCollidable = initCurrentlyCollidable; }

};
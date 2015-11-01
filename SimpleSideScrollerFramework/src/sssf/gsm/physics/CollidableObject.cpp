#include "sssf_VS\stdafx.h"
#include "sssf\gsm\physics\Collision.h"
#include "sssf\gsm\physics\CollidableObject.h"
#include "Box2D\Box2D.h"

/*
	This method updates the position and dimensions of this
	dynamic object's swept shape based on how much time
	is left during this frame.
*/

void CollidableObject::setAsGroundBox(b2World *world)
{
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pp.getX() * 0.01f, pp.getY() * 0.01f);
	body = world->CreateBody(&bodyDef);
	box.SetAsBox(boundingVolume.getWidth() * 0.01f, boundingVolume.getHeight() * 0.01f);
	fixtureDef.shape = &box;
	fixtureDef.density = 1.0f*0.01f;
	fixtureDef.friction = 1.0f;
	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);
}

void CollidableObject::setAsDynamicBox(b2World *world)
{
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pp.getX() * 0.01f, pp.getY() * 0.01f);
	body = world->CreateBody(&bodyDef);
	box.SetAsBox(boundingVolume.getWidth() / 2 * 0.01f, boundingVolume.getHeight() / 2 * 0.01f);
	fixtureDef.shape = &box;
	fixtureDef.density = 2.0f;
	fixtureDef.friction = 1.0f;
	body->SetUserData(this);
	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);
	
}

void CollidableObject::setAsPlayerBox(b2World *world)
{
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pp.getX() * 0.01f, pp.getY() * 0.01f);
	body = world->CreateBody(&bodyDef);
	box.SetAsBox(boundingVolume.getWidth() / 2 * 0.01f, boundingVolume.getHeight() / 2 * 0.01f);
	fixtureDef.shape = &box;
	fixtureDef.density = 2.0f;
	fixtureDef.friction = 1.0f;
	body->SetUserData(this);
	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);

}

void CollidableObject::setAsBlock(b2World *world, int blockType)
{
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pp.getX() * 0.01f, pp.getY() * 0.01f);
	bodyDef.linearDamping = 0.01f;
	body = world->CreateBody(&bodyDef);
	if (blockType == 1)
		 body->SetUserData(L"leftblock");
	else if (blockType == 2)
		 body->SetUserData(L"rightblock");
	else if (blockType == 4)
		 body->SetUserData(L"upblock");
	else if (blockType == 5)
		 body->SetUserData(L"downblock");
	box.SetAsBox(16.0f*0.01f, 16.0f*0.01f);
	fixtureDef.shape = &box;
	fixtureDef.density = 50.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.isSensor = true;
	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);
	//body->SetGravityScale(0);
}

void CollidableObject::setAsExit(b2World *world)
{
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(pp.getX() * 0.01f, pp.getY() * 0.01f);
	//bodyDef.linearDamping = 0.01f;
	body = world->CreateBody(&bodyDef);
	box.SetAsBox(32.0f*0.01f, 32.0f*0.01f);
	fixtureDef.shape = &box;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.isSensor = true;
	body->SetUserData(this);
	body->SetGravityScale(0.0f);
	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);
	
}
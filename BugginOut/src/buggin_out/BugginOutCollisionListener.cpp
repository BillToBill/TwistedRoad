/*
	Billy Gibson
	108592258
*/

#include "buggin_out\BugginOut.h"
#include "buggin_out\BugginOutDataLoader.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\physics\Collision.h"
#include "buggin_out\BugginOutCollisionListener.h"

void BugginOutCollisionListener::BeginContact(b2Contact* contact)
{
	player = game->getGSM()->getSpriteManager()->getPlayer();
	exit = game->getGSM()->getSpriteManager()->getExitBody();
	Physics* phy = game->getGSM()->getPhysics();

	if (contact->GetFixtureA()->GetBody() == player->body)
	{
		if (contact->GetFixtureB()->GetBody()->GetUserData() == L"upblock")
		{
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->gravSound);
			phy->getBoxWorld()->SetGravity(phy->Reverse_Grav);
			phy->CurrentGrav = phy->Reverse_Grav;
			game->getGSM()->gravU = true;
			player->setGrounded(false);
		}

		else if (contact->GetFixtureB()->GetBody()->GetUserData() == L"rightblock")
		{
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->gravSound);
			phy->getBoxWorld()->SetGravity(phy->Right_Grav);
			phy->CurrentGrav = phy->Right_Grav;
			game->getGSM()->gravR = true; 
			player->setGrounded(false);
		}

		else if (contact->GetFixtureB()->GetBody()->GetUserData() == L"leftblock")
		{
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->gravSound);
			phy->getBoxWorld()->SetGravity(phy->Left_Grav);
			phy->CurrentGrav = phy->Left_Grav;
			game->getGSM()->gravL = true;
			player->setGrounded(false);
		}

		else if (contact->GetFixtureB()->GetBody()->GetUserData() == L"downblock")
		{
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->gravSound);
			phy->getBoxWorld()->SetGravity(phy->Normal_Grav);
			phy->CurrentGrav = phy->Normal_Grav;
			game->getGSM()->gravN = true;
			player->setGrounded(false);
		}


		else if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody)
		{
			//player->setGrounded(true);

			if (player->dead == false)
			{
				if (player->getPhysicalProperties()->facing == 0)
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
					{
						/*if (contact->GetFixtureB()->GetBody()->GetPosition().x >= contact->GetFixtureA()->GetBody()->GetPosition().x - 0.16)
						{
							if (contact->GetFixtureB()->GetBody()->GetPosition().x <= contact->GetFixtureA()->GetBody()->GetPosition().x + 0.16)
							{*/
								if (contact->GetFixtureB()->GetBody()->GetPosition().y > contact->GetFixtureA()->GetBody()->GetPosition().y)
								{
									player->setGrounded(true);
									player->setCurrentState(RIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Reverse_Grav)
					{
						/*if (contact->GetFixtureB()->GetBody()->GetPosition().x >= contact->GetFixtureA()->GetBody()->GetPosition().x - 0.16)
						{
							if (contact->GetFixtureB()->GetBody()->GetPosition().x <= contact->GetFixtureA()->GetBody()->GetPosition().x + 0.16)
							{*/
								if (contact->GetFixtureB()->GetBody()->GetPosition().y < contact->GetFixtureA()->GetBody()->GetPosition().y)
								{
									player->setGrounded(true);
									player->setCurrentState(URIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Left_Grav)
					{
						/*if (contact->GetFixtureB()->GetBody()->GetPosition().y >= contact->GetFixtureA()->GetBody()->GetPosition().y - 0.16)
						{
							if (contact->GetFixtureB()->GetBody()->GetPosition().y <= contact->GetFixtureA()->GetBody()->GetPosition().y + 0.16)
							{*/
								if (contact->GetFixtureB()->GetBody()->GetPosition().x < contact->GetFixtureA()->GetBody()->GetPosition().x)
								{
									player->setGrounded(true);
									player->setCurrentState(LRIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Right_Grav)
					{
						/*if (contact->GetFixtureB()->GetBody()->GetPosition().y >= contact->GetFixtureA()->GetBody()->GetPosition().y - 0.16)
						{
							if (contact->GetFixtureB()->GetBody()->GetPosition().y <= contact->GetFixtureA()->GetBody()->GetPosition().y + 0.16)
							{*/
								if (contact->GetFixtureB()->GetBody()->GetPosition().x > contact->GetFixtureA()->GetBody()->GetPosition().x)
								{
									player->setGrounded(true);
									player->setCurrentState(RRIDLE);
								}
							/*}
						}*/
					}
				}
				else if (player->getPhysicalProperties()->facing != 0)
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
					{
						/*if (contact->GetFixtureB()->GetBody()->GetPosition().x >= contact->GetFixtureA()->GetBody()->GetPosition().x - 0.16)
						{
							if (contact->GetFixtureB()->GetBody()->GetPosition().x <= contact->GetFixtureA()->GetBody()->GetPosition().x + 0.16)
							{*/
								if (contact->GetFixtureB()->GetBody()->GetPosition().y > contact->GetFixtureA()->GetBody()->GetPosition().y)
								{
									player->setGrounded(true);
									player->setCurrentState(LIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Reverse_Grav)
					{
						/*if (contact->GetFixtureB()->GetBody()->GetPosition().x >= contact->GetFixtureA()->GetBody()->GetPosition().x - 0.16)
						{
							if (contact->GetFixtureB()->GetBody()->GetPosition().x <= contact->GetFixtureA()->GetBody()->GetPosition().x + 0.16)
							{*/
								if (contact->GetFixtureB()->GetBody()->GetPosition().y < contact->GetFixtureA()->GetBody()->GetPosition().y)
								{
									player->setGrounded(true);
									player->setCurrentState(ULIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Left_Grav)
					{
						/*if (contact->GetFixtureB()->GetBody()->GetPosition().y >= contact->GetFixtureA()->GetBody()->GetPosition().y - 0.16)
						{
							if (contact->GetFixtureB()->GetBody()->GetPosition().y <= contact->GetFixtureA()->GetBody()->GetPosition().y + 0.16)
							{*/
								if (contact->GetFixtureB()->GetBody()->GetPosition().x < contact->GetFixtureA()->GetBody()->GetPosition().x)
								{
									player->setGrounded(true);
									player->setCurrentState(LLIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Right_Grav)
					{
						/*if (contact->GetFixtureB()->GetBody()->GetPosition().y >= contact->GetFixtureA()->GetBody()->GetPosition().y - 0.16)
						{
							if (contact->GetFixtureB()->GetBody()->GetPosition().y <= contact->GetFixtureA()->GetBody()->GetPosition().y + 0.16)
							{*/
								if (contact->GetFixtureB()->GetBody()->GetPosition().x > contact->GetFixtureA()->GetBody()->GetPosition().x)
								{
									player->setGrounded(true);
									player->setCurrentState(RLIDLE);
								}
							/*}
						}*/
					}
				}
			}
		}

		if (contact->GetFixtureB()->GetBody() == exit)
		{
			game->getGSM()->levelSwitchTrigger = true;
		}

		else if (contact->GetFixtureB()->GetBody()->GetUserData() == L"walker" && player->dead == false)
		{
			player->dead = true;
			player->body->SetGravityScale(0.0f);
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}

		else if (contact->GetFixtureB()->GetBody()->GetUserData() == L"uwalker" && player->dead == false)
		{
			player->dead = true;
			player->body->SetGravityScale(0.0f);
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}

		else if (contact->GetFixtureB()->GetBody()->GetUserData() == L"rwalker" && player->dead == false)
		{
			player->dead = true;
			player->body->SetGravityScale(0.0f);
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}

		else if (contact->GetFixtureB()->GetBody()->GetUserData() == L"lwalker" && player->dead == false)
		{
			player->dead = true;
			player->body->SetGravityScale(0.0f);
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}

		else if (contact->GetFixtureB()->GetBody()->GetUserData() == L"flyer" && player->dead == false)
		{
			player->dead = true;
			player->body->SetGravityScale(0.0f);
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}
	}

	if (contact->GetFixtureB()->GetBody() == player->body)
	{
		if (contact->GetFixtureA()->GetBody()->GetUserData() == L"upblock")
		{
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->gravSound);
			phy->getBoxWorld()->SetGravity(phy->Reverse_Grav);
			phy->CurrentGrav = phy->Reverse_Grav;
			game->getGSM()->gravU = true;
			player->setGrounded(false);
		}

		else if (contact->GetFixtureA()->GetBody()->GetUserData() == L"rightblock")
		{
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->gravSound);
			phy->getBoxWorld()->SetGravity(phy->Right_Grav);
			phy->CurrentGrav = phy->Right_Grav;
			game->getGSM()->gravR = true;
			player->setGrounded(false);
		}

		else if (contact->GetFixtureA()->GetBody()->GetUserData() == L"leftblock")
		{
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->gravSound);
			phy->getBoxWorld()->SetGravity(phy->Left_Grav);
			phy->CurrentGrav = phy->Left_Grav;
			game->getGSM()->gravL = true;
			player->setGrounded(false);
		}

		else if (contact->GetFixtureA()->GetBody()->GetUserData() == L"downblock")
		{
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->gravSound);
			phy->getBoxWorld()->SetGravity(phy->Normal_Grav);
			phy->CurrentGrav = phy->Normal_Grav;
			game->getGSM()->gravN = true;
			player->setGrounded(false);
		}


		else if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody)
		{
			//player->setGrounded(true);

			if (player->dead == false)
			{
				if (player->getPhysicalProperties()->facing == 0)
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
					{
						/*if (contact->GetFixtureA()->GetBody()->GetPosition().x >= contact->GetFixtureB()->GetBody()->GetPosition().x - 0.16)
						{
							if (contact->GetFixtureA()->GetBody()->GetPosition().x <= contact->GetFixtureB()->GetBody()->GetPosition().x + 0.16)
							{*/
								if (contact->GetFixtureA()->GetBody()->GetPosition().y > contact->GetFixtureB()->GetBody()->GetPosition().y)
								{
									player->setGrounded(true);
									player->setCurrentState(RIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Reverse_Grav)
					{
						/*if (contact->GetFixtureA()->GetBody()->GetPosition().x >= contact->GetFixtureB()->GetBody()->GetPosition().x - 0.16)
						{
							if (contact->GetFixtureA()->GetBody()->GetPosition().x <= contact->GetFixtureB()->GetBody()->GetPosition().x + 0.16)
							{*/
								if (contact->GetFixtureA()->GetBody()->GetPosition().y < contact->GetFixtureB()->GetBody()->GetPosition().y)
								{
									player->setGrounded(true);
									player->setCurrentState(URIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Left_Grav)
					{
						/*if (contact->GetFixtureA()->GetBody()->GetPosition().y >= contact->GetFixtureB()->GetBody()->GetPosition().y - 0.16)
						{
							if (contact->GetFixtureA()->GetBody()->GetPosition().y <= contact->GetFixtureB()->GetBody()->GetPosition().y + 0.16)
							{*/
								if (contact->GetFixtureA()->GetBody()->GetPosition().x < contact->GetFixtureB()->GetBody()->GetPosition().x)
								{
									player->setGrounded(true);
									player->setCurrentState(LRIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Right_Grav)
					{
						/*if (contact->GetFixtureA()->GetBody()->GetPosition().y >= contact->GetFixtureB()->GetBody()->GetPosition().y - 0.16)
						{
							if (contact->GetFixtureA()->GetBody()->GetPosition().y <= contact->GetFixtureB()->GetBody()->GetPosition().y + 0.16)
							{*/
								if (contact->GetFixtureA()->GetBody()->GetPosition().x > contact->GetFixtureB()->GetBody()->GetPosition().x)
								{
									player->setGrounded(true);
									player->setCurrentState(RRIDLE);
								}
							/*}
						}*/
					}
				}
				else if (player->getPhysicalProperties()->facing != 0)
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
					{
						/*if (contact->GetFixtureA()->GetBody()->GetPosition().x >= contact->GetFixtureB()->GetBody()->GetPosition().x - 0.16)
						{
							if (contact->GetFixtureA()->GetBody()->GetPosition().x <= contact->GetFixtureB()->GetBody()->GetPosition().x + 0.16)
							{*/
								if (contact->GetFixtureA()->GetBody()->GetPosition().y > contact->GetFixtureB()->GetBody()->GetPosition().y)
								{
									player->setGrounded(true);
									player->setCurrentState(LIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Reverse_Grav)
					{
						/*if (contact->GetFixtureA()->GetBody()->GetPosition().x >= contact->GetFixtureB()->GetBody()->GetPosition().x - 0.16)
						{
							if (contact->GetFixtureA()->GetBody()->GetPosition().x <= contact->GetFixtureB()->GetBody()->GetPosition().x + 0.16)
							{*/
								if (contact->GetFixtureA()->GetBody()->GetPosition().y > contact->GetFixtureB()->GetBody()->GetPosition().y)
								{
									player->setGrounded(true);
									player->setCurrentState(ULIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Left_Grav)
					{
						/*if (contact->GetFixtureA()->GetBody()->GetPosition().y >= contact->GetFixtureB()->GetBody()->GetPosition().y - 0.16)
						{
							if (contact->GetFixtureA()->GetBody()->GetPosition().y <= contact->GetFixtureB()->GetBody()->GetPosition().y + 0.16)
							{*/
								if (contact->GetFixtureA()->GetBody()->GetPosition().x < contact->GetFixtureB()->GetBody()->GetPosition().x)
								{
									player->setGrounded(true);
									player->setCurrentState(LLIDLE);
								}
							/*}
						}*/
					}
					else if (phy->CurrentGrav == phy->Right_Grav)
					{
						/*if (contact->GetFixtureA()->GetBody()->GetPosition().y >= contact->GetFixtureB()->GetBody()->GetPosition().y - 0.16)
						{
							if (contact->GetFixtureA()->GetBody()->GetPosition().y <= contact->GetFixtureB()->GetBody()->GetPosition().y + 0.16)
							{*/
								if (contact->GetFixtureA()->GetBody()->GetPosition().x > contact->GetFixtureB()->GetBody()->GetPosition().x)
								{
									player->setGrounded(true);
									player->setCurrentState(RLIDLE);
								}
							/*}
						}*/
					}
				}
			}
		}

		if (contact->GetFixtureA()->GetBody() == exit)
		{
			game->getGSM()->levelSwitchTrigger = true;
		}

		else if (contact->GetFixtureA()->GetBody()->GetUserData() == L"walker" && player->dead == false)
		{
			player->dead = true;
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}

		else if (contact->GetFixtureA()->GetBody()->GetUserData() == L"uwalker" && player->dead == false)
		{
			player->dead = true;
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}

		else if (contact->GetFixtureA()->GetBody()->GetUserData() == L"rwalker" && player->dead == false)
		{
			player->dead = true;
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}

		else if (contact->GetFixtureA()->GetBody()->GetUserData() == L"lwalker" && player->dead == false)
		{
			player->dead = true;
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}

		else if (contact->GetFixtureA()->GetBody()->GetUserData() == L"flyer" && player->dead == false)
		{
			player->dead = true;
			((BugginOutDataLoader*)game->getDataLoader())->channel->stop();
			((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->dieSound);
			player->setCurrentState(L"LDEATH");
		}
	}

	if (contact->GetFixtureA()->GetBody()->GetUserData() == L"walker" || contact->GetFixtureA()->GetBody()->GetUserData() == L"uwalker"){
		if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody  && !contact->GetFixtureB()->IsSensor())
		{
			if (contact->GetFixtureB()->GetBody()->GetPosition().y <= contact->GetFixtureA()->GetBody()->GetPosition().y + 0.32f)
			{
				if (contact->GetFixtureB()->GetBody()->GetPosition().y >= contact->GetFixtureA()->GetBody()->GetPosition().y - 0.32f)
				{
					if (contact->GetFixtureB()->GetBody()->GetPosition().x > contact->GetFixtureA()->GetBody()->GetPosition().x)
						game->getGSM()->getSpriteManager()->negativeDeltaMovement(contact->GetFixtureA()->GetBody()->GetPosition().x, contact->GetFixtureA()->GetBody()->GetPosition().y);
					else if (contact->GetFixtureB()->GetBody()->GetPosition().x < contact->GetFixtureA()->GetBody()->GetPosition().x)
						game->getGSM()->getSpriteManager()->positiveDeltaMovement(contact->GetFixtureA()->GetBody()->GetPosition().x, contact->GetFixtureA()->GetBody()->GetPosition().y);
				}
			}
		}
	}

	if (contact->GetFixtureB()->GetBody()->GetUserData() == L"walker" || contact->GetFixtureA()->GetBody()->GetUserData() == L"uwalker"){
		if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody  && !contact->GetFixtureA()->IsSensor())
		{
			if (contact->GetFixtureA()->GetBody()->GetPosition().y <= contact->GetFixtureB()->GetBody()->GetPosition().y + 0.32f)
			{
				if (contact->GetFixtureA()->GetBody()->GetPosition().y >= contact->GetFixtureB()->GetBody()->GetPosition().y - 0.32f)
				{
					if (contact->GetFixtureA()->GetBody()->GetPosition().x > contact->GetFixtureB()->GetBody()->GetPosition().x)
						game->getGSM()->getSpriteManager()->negativeDeltaMovement(contact->GetFixtureB()->GetBody()->GetPosition().x, contact->GetFixtureB()->GetBody()->GetPosition().y);
					else if (contact->GetFixtureA()->GetBody()->GetPosition().x < contact->GetFixtureB()->GetBody()->GetPosition().x)
						game->getGSM()->getSpriteManager()->positiveDeltaMovement(contact->GetFixtureB()->GetBody()->GetPosition().x, contact->GetFixtureB()->GetBody()->GetPosition().y);
				}
			}
		}
	}

	if (contact->GetFixtureA()->GetBody()->GetUserData() == L"rwalker" || contact->GetFixtureA()->GetBody()->GetUserData() == L"lwalker"){
		if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody && !contact->GetFixtureB()->IsSensor())
		{
			//if (contact->GetFixtureB()->GetBody()->GetPosition().x <= contact->GetFixtureA()->GetBody()->GetPosition().x + 0.16f)
			if (contact->GetFixtureB()->GetBody()->GetPosition().x < contact->GetFixtureA()->GetBody()->GetPosition().x)
			{
				/*if (contact->GetFixtureB()->GetBody()->GetPosition().x >= contact->GetFixtureA()->GetBody()->GetPosition().x - 0.16f)
				{*/
					if (contact->GetFixtureB()->GetBody()->GetPosition().y > contact->GetFixtureA()->GetBody()->GetPosition().y)
						game->getGSM()->getSpriteManager()->negativeDeltaMovement(contact->GetFixtureA()->GetBody()->GetPosition().x, contact->GetFixtureA()->GetBody()->GetPosition().y);
					else if (contact->GetFixtureB()->GetBody()->GetPosition().y < contact->GetFixtureA()->GetBody()->GetPosition().y)
						game->getGSM()->getSpriteManager()->positiveDeltaMovement(contact->GetFixtureA()->GetBody()->GetPosition().x, contact->GetFixtureA()->GetBody()->GetPosition().y);
				//}
			}
		}
	}

	if (contact->GetFixtureB()->GetBody()->GetUserData() == L"rwalker" || contact->GetFixtureB()->GetBody()->GetUserData() == L"lwalker"){
		if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody  && !contact->GetFixtureA()->IsSensor())
		{
			//if (contact->GetFixtureA()->GetBody()->GetPosition().x <= contact->GetFixtureB()->GetBody()->GetPosition().x + 0.16f)
			if (contact->GetFixtureB()->GetBody()->GetPosition().x < contact->GetFixtureA()->GetBody()->GetPosition().x)
			{
				/*if (contact->GetFixtureA()->GetBody()->GetPosition().x >= contact->GetFixtureB()->GetBody()->GetPosition().x - 0.16f)
				{*/
					if (contact->GetFixtureA()->GetBody()->GetPosition().y > contact->GetFixtureB()->GetBody()->GetPosition().y)
						game->getGSM()->getSpriteManager()->negativeDeltaMovement(contact->GetFixtureB()->GetBody()->GetPosition().x, contact->GetFixtureB()->GetBody()->GetPosition().y);
					else if (contact->GetFixtureA()->GetBody()->GetPosition().y < contact->GetFixtureB()->GetBody()->GetPosition().y)
						game->getGSM()->getSpriteManager()->positiveDeltaMovement(contact->GetFixtureB()->GetBody()->GetPosition().x, contact->GetFixtureB()->GetBody()->GetPosition().y);
				//}
			}
		}
	}

}

void BugginOutCollisionListener::EndContact(b2Contact* contact)
{
	player = game->getGSM()->getSpriteManager()->getPlayer();
	/*if (contact->GetFixtureA()->GetBody() == player->body)
	{
	}*/
}
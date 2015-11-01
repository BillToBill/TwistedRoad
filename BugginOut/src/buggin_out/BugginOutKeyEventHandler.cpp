/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugginOutKeyEventHandler.cpp

	See BugginOutKeyEventHandler.h for a class description.
*/

#include "buggin_out_VS\stdafx.h"
#include "buggin_out\BugginOut.h"
#include "buggin_out\BugginOutKeyEventHandler.h"
#include "buggin_out\BugginOutDataLoader.h"
#include "sssf\game\Game.h"
#include "sssf\game\WStringTable.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\timer\GameTimer.h"
#include "sssf\platforms\Windows\WindowsTimer.h"

/*
	handleKeyEvent - this method handles all keyboard interactions. Note that every frame this method
	gets called and it can respond to key interactions in any custom way. Ask the GameInput class for
	key states since the last frame, which can allow us to respond to key presses, including when keys
	are held down for multiple frames.
*/
void BugginOutKeyEventHandler::handleKeyEvents(Game *game)
{
	// WE CAN QUERY INPUT TO SEE WHAT WAS PRESSED
	GameInput *input = game->getInput();

	// LET'S GET THE PLAYER'S PHYSICAL PROPERTIES, IN CASE WE WANT TO CHANGE THEM
	GameStateManager *gsm = game->getGSM();
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	list<AnimatedSprite*>::iterator blocks;
	PhysicalProperties *pp = player->getPhysicalProperties();
	Viewport *viewport = game->getGUI()->getViewport();

	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		Physics *phy = game->getGSM()->getPhysics();
		// WASD KEY PRESSES WILL CONTROL THE PLAYER
		// SO WE'LL UPDATE THE PLAYER VELOCITY WHEN THESE KEYS ARE
		// PRESSED, THAT WAY PHYSICS CAN CORRECT AS NEEDED
		float vX = pp->getVelocityX();
		float vY = pp->getVelocityY();

		// YOU MIGHT WANT TO UNCOMMENT THIS FOR SOME TESTING,

		b2Body *body = player->body;

		if (game->getGSM()->levelSwitchTrigger == true)
		{
			game->quitGame();

			if (game->getCurrentLevelFileName() == W_LEVEL_1_NAME)
				game->setCurrentLevelFileName(W_LEVEL_2_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_2_NAME)
				game->setCurrentLevelFileName(W_LEVEL_3_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_3_NAME)
				game->setCurrentLevelFileName(W_LEVEL_4_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_4_NAME)
				game->setCurrentLevelFileName(W_LEVEL_5_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_5_NAME)
				game->setCurrentLevelFileName(W_LEVEL_6_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_6_NAME)
				game->setCurrentLevelFileName(W_LEVEL_7_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_7_NAME)
				game->setCurrentLevelFileName(W_LEVEL_8_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_8_NAME)
				game->setCurrentLevelFileName(W_LEVEL_9_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_9_NAME)
				game->setCurrentLevelFileName(W_LEVEL_10_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_10_NAME)
				game->setCurrentLevelFileName(W_LEVEL_1_NAME);

			game->startGame();
			game->getGSM()->levelSwitchTrigger = false;
		}

		if (game->getGSM()->levelResetTrigger == true)
		{
			game->quitGame();

			if (game->getCurrentLevelFileName() == W_LEVEL_1_NAME)
				game->setCurrentLevelFileName(W_LEVEL_1_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_2_NAME)
				game->setCurrentLevelFileName(W_LEVEL_2_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_3_NAME)
				game->setCurrentLevelFileName(W_LEVEL_3_NAME);

			else if (game->getCurrentLevelFileName() == W_LEVEL_4_NAME)
				game->setCurrentLevelFileName(W_LEVEL_4_NAME);

			game->startGame();
			game->getGSM()->levelResetTrigger = false;
		}

		if (input->isKeyDown('1')){
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_1_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_1_NAME);
			/*game->setCurrentLevelFileName(W_LEVEL_1_NAME);
			game->startGame();*/
		}
		else if (input->isKeyDown('2')){
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_2_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_2_NAME);
		}
		else if (input->isKeyDown('3')){
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_3_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_3_NAME);
		}
		else if (input->isKeyDown('4'))
		{
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_4_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_4_NAME);
		}
		else if (input->isKeyDown('5'))
		{
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_5_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_4_NAME);
		}
		else if (input->isKeyDown('6'))
		{
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_6_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_4_NAME);
		}
		else if (input->isKeyDown('7'))
		{
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_7_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_4_NAME);
		}
		else if (input->isKeyDown('8'))
		{
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_8_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_4_NAME);
		}
		else if (input->isKeyDown('9'))
		{
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_9_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_4_NAME);
		}
		else if (input->isKeyDown('0'))
		{
			game->quitGame();
			game->setCurrentLevelFileName(W_LEVEL_10_NAME);
			game->startGame();
			//game->getGSM()->unloadCurrentLevel();
			//game->getGSM()->loadLevel(game, W_LEVEL_1_DIR + W_LEVEL_4_NAME);
		}

		else if (input->isKeyDown(A_KEY))
		{
			if (player->dead == false)
			{
				pp->facing = 1;

				if ((phy->CurrentGrav == phy->Normal_Grav || phy->CurrentGrav == phy->Reverse_Grav))
				{
					if (player->onGround())
						body->ApplyForce(b2Vec2(body->GetMass() * -0.1 / (1 / 60.0), 0), body->GetWorldCenter(), true);
					else
						body->ApplyForce(b2Vec2(body->GetMass() * -0.1 / (1 / 60.0), 0), body->GetWorldCenter(), true);
				}

				if ((phy->CurrentGrav == phy->Left_Grav || phy->CurrentGrav == phy->Right_Grav))
				{
					if (player->onGround())
						body->ApplyForce(b2Vec2(0, body->GetMass() * -0.1 / (1 / 60.0)), body->GetWorldCenter(), true);
					else
						body->ApplyForce(b2Vec2(0, body->GetMass() * -0.1 / (1 / 60.0)), body->GetWorldCenter(), true);
				}

				if (player->onGround())
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
						player->setCurrentState(LWALK);
					else if (phy->CurrentGrav == phy->Reverse_Grav)
						player->setCurrentState(ULWALK);
					else if (phy->CurrentGrav == phy->Right_Grav)
						player->setCurrentState(RLWALK);
					else if (phy->CurrentGrav == phy->Left_Grav)
						player->setCurrentState(LLWALK);
				}
				else
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
						player->setCurrentState(LFALL);
					else if (phy->CurrentGrav == phy->Reverse_Grav)
						player->setCurrentState(ULFALL);
					else if (phy->CurrentGrav == phy->Right_Grav)
						player->setCurrentState(RLFALL);
					else if (phy->CurrentGrav == phy->Left_Grav)
						player->setCurrentState(LLFALL);
				}
			}
		}
		else if (input->isKeyDown(D_KEY))
		{
			if (player->dead == false)
			{
				pp->facing = 0;
				if ((phy->CurrentGrav == phy->Normal_Grav || phy->CurrentGrav == phy->Reverse_Grav))
				{
					if (player->onGround())
						body->ApplyForce(b2Vec2(body->GetMass() * 0.1 / (1 / 60.0), 0), body->GetWorldCenter(), true);
					else
						body->ApplyForce(b2Vec2(body->GetMass() * 0.1 / (1 / 60.0), 0), body->GetWorldCenter(), true);
				}

				if ((phy->CurrentGrav == phy->Left_Grav || phy->CurrentGrav == phy->Right_Grav))
				{
					if (player->onGround())
						body->ApplyForce(b2Vec2(0, body->GetMass() * 0.1 / (1 / 60.0)), body->GetWorldCenter(), true);
					else
						body->ApplyForce(b2Vec2(0, body->GetMass() * 0.1 / (1 / 60.0)), body->GetWorldCenter(), true);
				}

				if (player->onGround())
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
						player->setCurrentState(RWALK);
					else if (phy->CurrentGrav == phy->Reverse_Grav)
						player->setCurrentState(URWALK);
					else if (phy->CurrentGrav == phy->Right_Grav)
						player->setCurrentState(RRWALK);
					else if (phy->CurrentGrav == phy->Left_Grav)
						player->setCurrentState(LRWALK);
				}

				else
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
						player->setCurrentState(RFALL);
					else if (phy->CurrentGrav == phy->Reverse_Grav)
						player->setCurrentState(URFALL);
					else if (phy->CurrentGrav == phy->Right_Grav)
						player->setCurrentState(RRFALL);
					else if (phy->CurrentGrav == phy->Left_Grav)
						player->setCurrentState(LRFALL);
				}
			}
		}
		else if (input->isKeyDownForFirstTime(G_KEY))
		{
			/*((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->gravSound);
			b2World *world = game->getGSM()->getPhysics()->getBoxWorld();

			if (phy->CurrentGrav == phy->Normal_Grav)
			{
				player->body->SetTransform(player->body->GetPosition(), 0.0f);
				blocks = gsm->getSpriteManager()->getBlocksIterator();
				while (blocks != gsm->getSpriteManager()->getEndOfBlocksIterator())
				{
					(*blocks)->body->SetGravityScale(1);
					blocks++;
				}

				world->SetGravity(phy->Reverse_Grav);
				phy->CurrentGrav = phy->Reverse_Grav;
			}

			else if (phy->CurrentGrav == phy->Reverse_Grav)
			{
				player->body->SetTransform(player->body->GetPosition(), 270.0f);
				blocks = gsm->getSpriteManager()->getBlocksIterator();
				while (blocks != gsm->getSpriteManager()->getEndOfBlocksIterator())
				{
					(*blocks)->body->SetGravityScale(0);
					blocks++;
				}

				world->SetGravity(phy->Left_Grav);
				phy->CurrentGrav = phy->Left_Grav;

			}

			else if (phy->CurrentGrav == phy->Left_Grav)
			{
				player->body->SetTransform(player->body->GetPosition(), 270.0f);
				blocks = gsm->getSpriteManager()->getBlocksIterator();
				while (blocks != gsm->getSpriteManager()->getEndOfBlocksIterator())
				{
					(*blocks)->body->SetGravityScale(0);
					blocks++;
				}

				world->SetGravity(phy->Right_Grav);
				phy->CurrentGrav = phy->Right_Grav;

			}

			else if (phy->CurrentGrav == phy->Right_Grav)
			{
				player->body->SetTransform(player->body->GetPosition(), 0.0f);
				blocks = gsm->getSpriteManager()->getBlocksIterator();
				while (blocks != gsm->getSpriteManager()->getEndOfBlocksIterator())
				{
					(*blocks)->body->SetGravityScale(1);
					blocks++;
				}

				world->SetGravity(phy->Normal_Grav);
				phy->CurrentGrav = phy->Normal_Grav;

			}

			player->setGrounded(false);*/
		}

		else if (player->onGround())
		{
			if (player->dead == false)
			{
				if (pp->facing == 0)
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
						player->setCurrentState(RIDLE);
					else if (phy->CurrentGrav == phy->Reverse_Grav)
						player->setCurrentState(URIDLE);
					else if (phy->CurrentGrav == phy->Right_Grav)
						player->setCurrentState(RRIDLE);
					else if (phy->CurrentGrav == phy->Left_Grav)
						player->setCurrentState(LRIDLE);
				}
				else
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
						player->setCurrentState(LIDLE);
					else if (phy->CurrentGrav == phy->Reverse_Grav)
						player->setCurrentState(ULIDLE);
					else if (phy->CurrentGrav == phy->Right_Grav)
						player->setCurrentState(RLIDLE);
					else if (phy->CurrentGrav == phy->Left_Grav)
						player->setCurrentState(LLIDLE);
				}
			}

			else
			{
				if (player->getCurrentState() != L"LDEATH")
				{
					if (pp->facing == 0){
						if (phy->CurrentGrav == phy->Normal_Grav)
							player->setCurrentState(RFALL);
						else if (phy->CurrentGrav == phy->Reverse_Grav)
							player->setCurrentState(URFALL);
						else if (phy->CurrentGrav == phy->Right_Grav)
							player->setCurrentState(RRFALL);
						else if (phy->CurrentGrav == phy->Left_Grav)
							player->setCurrentState(LRFALL);
					}
					else{
						if (phy->CurrentGrav == phy->Normal_Grav)
							player->setCurrentState(LFALL);
						else if (phy->CurrentGrav == phy->Reverse_Grav)
							player->setCurrentState(ULFALL);
						else if (phy->CurrentGrav == phy->Right_Grav)
							player->setCurrentState(RLFALL);
						else if (phy->CurrentGrav == phy->Left_Grav)
							player->setCurrentState(LLFALL);
					}
				}
			}
		}
			if (input->isKeyDownForFirstTime(SPACE_KEY) && player->onGround() && player->dead == false)
			{
				((BugginOutDataLoader*)game->getDataLoader())->remotePlaySound(((BugginOutDataLoader*)game->getDataLoader())->jumpSound);
				//float mass = body->GetMass();
				float impulse = 3.0f; 

				if (phy->CurrentGrav == phy->Normal_Grav)
				{
					body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -impulse));
				}
				if (phy->CurrentGrav == phy->Reverse_Grav)
				{
					body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, impulse));
				}
				if (phy->CurrentGrav == phy->Right_Grav)
				{
					body->SetLinearVelocity(b2Vec2(-impulse, body->GetLinearVelocity().y));
				}
				if (phy->CurrentGrav == phy->Left_Grav)
				{
					body->SetLinearVelocity(b2Vec2(impulse, body->GetLinearVelocity().y));
				}

				if (pp->facing == 0)
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
						player->setCurrentState(RJUMP);
					else if (phy->CurrentGrav == phy->Reverse_Grav)
						player->setCurrentState(URJUMP);
					else if (phy->CurrentGrav == phy->Right_Grav)
						player->setCurrentState(RRJUMP);
					else if (phy->CurrentGrav == phy->Left_Grav)
						player->setCurrentState(LRJUMP);
				}
				else
				{
					if (phy->CurrentGrav == phy->Normal_Grav)
						player->setCurrentState(LJUMP);
					else if (phy->CurrentGrav == phy->Reverse_Grav)
						player->setCurrentState(ULJUMP);
					else if (phy->CurrentGrav == phy->Right_Grav)
						player->setCurrentState(RLJUMP);
					else if (phy->CurrentGrav == phy->Left_Grav)
						player->setCurrentState(LLJUMP);
				}

				player->setGrounded(false);
			}
			if (input->isKeyDownForFirstTime(P_KEY))
			{
				game->getGSM()->getPhysics()->activated = !(game->getGSM()->getPhysics()->activated);
			}
			if (input->isKeyDownForFirstTime(R_KEY))
			{
				game->getGSM()->levelResetTrigger = true;
			}

			// NOW SET THE ACTUAL PLAYER VELOCITY
			pp->setVelocity(vX, vY);
		

		// 0X43 is HEX FOR THE 'C' VIRTUAL KEY
		// THIS CHANGES THE CURSOR IMAGE
		if ((input->isKeyDownForFirstTime(C_KEY)) && input->isKeyDown(VK_SHIFT))
		{
			Cursor *cursor = game->getGUI()->getCursor();
			unsigned int id = cursor->getActiveCursorID();
			id++;
			if (id == cursor->getNumCursorIDs())
				id = 0;
			cursor->setActiveCursorID(id);
		}

		// LET'S MESS WITH THE TARGET FRAME RATE IF THE USER PRESSES THE HOME OR END KEYS
		WindowsTimer *timer = (WindowsTimer*)game->getTimer();
		int fps = timer->getTargetFPS();

		// THIS SPEEDS UP OUR GAME LOOP AND THUS THE GAME, NOTE THAT WE COULD ALTERNATIVELY SCALE
		// DOWN THE GAME LOGIC (LIKE ALL VELOCITIES) AS WE SPEED UP THE GAME. THAT COULD PROVIDE
		// A BETTER PLAYER EXPERIENCE
		if (input->isKeyDown(VK_HOME) && (fps < MAX_FPS))
			timer->setTargetFPS(fps + FPS_INC);

		// THIS SLOWS DOWN OUR GAME LOOP, BUT WILL NOT GO BELOW 5 FRAMES PER SECOND
		else if (input->isKeyDown(VK_END) && (fps > MIN_FPS))
			timer->setTargetFPS(fps - FPS_INC);
	}

}
/******************************************************************************
* Copyright (C) Mario Löscher, Armin Felder
* This file is part of PenguinGame <https://git.felder-edv.at/uibkcpp18/game>.
*
* PenguinGame is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PenguinGame is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PenguinGame. If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


#include <iostream>
#include "CombatSystem.h"
#include "../events/KeyDownEvent.h"
#include "../managers/ComponentsManager.h"
#include "../managers/EntityManager.h"
#include "../entities/Projectile.h"
#include "../events/CollisionEvent.h"
#include "../events/HealthEvent.h"
#include "../events/EntityCanSee.h"

Systems::CombatSystem::CombatSystem(SDL_Renderer *pRenderer,Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {

    auto attackCallback = [system=this](const std::shared_ptr<Events::Event> &pEvent)->void{
        auto event = static_cast<Events::KeyDownEvent*>(pEvent.get());
        if(event->mKeyCode.sym == SDLK_LCTRL){
            auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(1);
            auto playerVisual = Managers::ComponentsManager::getVisualComponent(1);
            auto playerXp = Managers::ComponentsManager::getXp(1);
            int moveX = 200;
            if(playerVisual->mFlip){
                moveX *= -1;
            }
            int test = (playerVisual->mImageRect.w)+1;
            test = test*playerVisual->mFlip?-1:1;
            int x = playerSpatial->mPositionX+(((playerVisual->mImageRect.w)+1)*(playerVisual->mFlip?-1:1));
            int y = playerSpatial->mPositionY+(playerVisual->mImageRect.h/2);

            int bulletId = Managers::EntityManager::createEntity<Entities::Projectile>();
            Managers::ComponentsManager::createVisualComponent(bulletId,system->mBlueBullet, 10,5);
            Managers::ComponentsManager::createSpatialComponent(bulletId,x,y);
            Managers::ComponentsManager::createPathComponent(bulletId,{SDL_Point{moveX,0}},15);
            Managers::ComponentsManager::createDamageComponent(bulletId,10+playerXp->mXp);
            Managers::ComponentsManager::createTimeToLive(bulletId, 500+playerXp->mXp);
        }else if(event->mKeyCode.sym == SDLK_LALT){
            auto playerInventory = Managers::ComponentsManager::getInventory(1);
            if(playerInventory && playerInventory->hasItem(Components::Inventory::ItemTypes::ak47)) {
                auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(1);
                auto playerVisual = Managers::ComponentsManager::getVisualComponent(1);
                auto playerXp = Managers::ComponentsManager::getXp(1);
                int moveX = 200;
                if (playerVisual->mFlip) {
                    moveX *= -1;
                }
                int test = (playerVisual->mImageRect.w) + 1;
                int x = playerSpatial->mPositionX +
                        (((playerVisual->mImageRect.w) + 1) * (playerVisual->mFlip ? -1 : 1));
                int y = playerSpatial->mPositionY + (playerVisual->mImageRect.h / 2);

                auto texture  =playerVisual->mFlip?system->mAkBulletLeft:system->mAkBulletRight;
                int bulletId = Managers::EntityManager::createEntity<Entities::Projectile>();
                Managers::ComponentsManager::createVisualComponent(bulletId, texture, 10, 5);
                Managers::ComponentsManager::createSpatialComponent(bulletId, x, y);
                Managers::ComponentsManager::createPathComponent(bulletId, {SDL_Point{moveX, 0}}, 20);
                Managers::ComponentsManager::createDamageComponent(bulletId, 15 + playerXp->mXp);
                Managers::ComponentsManager::createTimeToLive(bulletId, 800 + playerXp->mXp);
            }
        }else if(event->mKeyCode.sym == SDLK_LSHIFT){

            auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(1);
            auto playerVisual = Managers::ComponentsManager::getVisualComponent(1);
            auto playerXp = Managers::ComponentsManager::getXp(1);
            int moveX = 20;
            if (playerVisual->mFlip) {
                moveX *= -1;
            }
            int x = playerSpatial->mPositionX +
                    (((playerVisual->mImageRect.w) + 1) * (playerVisual->mFlip ? -1 : 1));
            int y = playerSpatial->mPositionY + (playerVisual->mImageRect.h / 5);

            auto texture  =playerVisual->mFlip?system->mTextureHandRight:system->mTextureHandLeft;
            int bulletId = Managers::EntityManager::createEntity<Entities::Projectile>();
            Managers::ComponentsManager::createVisualComponent(bulletId, texture, 40, 40);
            Managers::ComponentsManager::createSpatialComponent(bulletId, x, y);
            Managers::ComponentsManager::createPathComponent(bulletId, {SDL_Point{moveX, 0},SDL_Point{-moveX,0}}, 5);
            Managers::ComponentsManager::createDamageComponent(bulletId, 15 + playerXp->mXp);
            Managers::ComponentsManager::createTimeToLive(bulletId, 180 + playerXp->mXp);

        }
    };

    auto bulletCollisionCallback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void{
        auto event = static_cast<Events::CollisionEvent*>(pEvent.get());
        if(event->mType == Events::collisionTypes::npc||event->mType == Events::collisionTypes::player){
            auto damage = Managers::ComponentsManager::getDamage(event->mMovingEntity);
            auto xp = Managers::ComponentsManager::getXp(event->mCollidingEntity);
            auto evadeCap = Managers::ComponentsManager::getEvadeCapability(event->mCollidingEntity);

            if(damage) {
                if(!evadeCap || (std::rand() % 100) < (100-evadeCap->mChance)) {
                    int damageValue = damage->mDamage;
                    if (xp) {
                        damageValue = damageValue - (xp->mXp / 5);
                    }
                    if (damageValue > 0) {
                        system->mEventsManager->addEvent(
                                std::make_shared<Events::HealthEvent>(event->mCollidingEntity, -damage->mDamage));
                    }
                }
                Managers::ComponentsManager::removeComponentsOfEntity(event->mMovingEntity);
                std::cout << "bullet coll" << std::endl;
            }
        }

    };

    auto canSeeEnemy = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void{
        auto event = static_cast<Events::EntityCanSee*>(pEvent.get());
        auto path = Managers::ComponentsManager::getPaths(event->mSeeingEntity);
        path->mPaused = true;

        auto enemySpatial = Managers::ComponentsManager::getSpatialComponent(event->mSeenEntity);

        auto entitySpatial = Managers::ComponentsManager::getSpatialComponent(event->mSeeingEntity);
        auto entityVisual = Managers::ComponentsManager::getVisualComponent(event->mSeeingEntity);
        auto entityInventory = Managers::ComponentsManager::getInventory(event->mSeeingEntity);
        int distributionSum = entityInventory->getDistributionSum(entityInventory);
        if(entityInventory && distributionSum > 0){ // test distributionSum for greater zero to prevent division by zero

            auto items = entityInventory->listItems<Components::Inventory::ItemTypes>();

            int randomAttack = rand() % distributionSum; //some random function from 0 to distributionSum



            int attackFinder = 0;
            for (const auto &item : items) { //find attack
                int distribution = entityInventory->getItemTypeDistribution(item); // get actual number from item
                if (attackFinder >= randomAttack || attackFinder < randomAttack+distribution)
                    switch (item){
                        case Components::Inventory::ItemTypes::ak47:{
                            int moveX = 200;
                            if (entityVisual->mFlip) {
                                moveX *= -1;
                            }
                            int test = (entityVisual->mImageRect.w) + 1;
                            int x = entitySpatial->mPositionX +
                                    (((entityVisual->mImageRect.w) + 1) * (entityVisual->mFlip ? -1 : 1));
                            int y = entitySpatial->mPositionY + (entityVisual->mImageRect.h / 2);

                            auto texture  =entityVisual->mFlip?system->mAkBulletLeft:system->mAkBulletRight;
                            int bulletId = Managers::EntityManager::createEntity<Entities::Projectile>();
                            Managers::ComponentsManager::createVisualComponent(bulletId, texture, 10, 5);
                            Managers::ComponentsManager::createSpatialComponent(bulletId, x, y);
                            Managers::ComponentsManager::createPathComponent(bulletId, {SDL_Point{moveX, 0}}, 20);
                            Managers::ComponentsManager::createDamageComponent(bulletId, 15 );
                            Managers::ComponentsManager::createTimeToLive(bulletId, 800 );
                            break;
                        }
                        default:{

                            int moveX = 200;
                            bool flip = false;
                            if (enemySpatial->mPositionX < entitySpatial->mPositionX) {
                                moveX *= -1;
                                flip = true;
                            }
                            int x = entitySpatial->mPositionX + (((entityVisual->mImageRect.w) + 1) * (flip ? -1 : 1));
                            int y = entitySpatial->mPositionY + (entityVisual->mImageRect.h / 2);

                            int bulletId = Managers::EntityManager::createEntity<Entities::Projectile>();
                            Managers::ComponentsManager::createVisualComponent(bulletId, system->mBlueBullet, 10, 5);
                            Managers::ComponentsManager::createSpatialComponent(bulletId, x, y);
                            Managers::ComponentsManager::createPathComponent(bulletId, {SDL_Point{moveX, 0}}, 15);
                            Managers::ComponentsManager::createDamageComponent(bulletId, 10);
                            Managers::ComponentsManager::createTimeToLive(bulletId, 500);
                        }


                    }
                else
                    attackFinder += distribution;
            }



        }else {

            int moveX = 200;
            bool flip = false;
            if (enemySpatial->mPositionX < entitySpatial->mPositionX) {
                moveX *= -1;
                flip = true;
            }
            int x = entitySpatial->mPositionX + (((entityVisual->mImageRect.w) + 1) * (flip ? -1 : 1));
            int y = entitySpatial->mPositionY + (entityVisual->mImageRect.h / 2);

            int bulletId = Managers::EntityManager::createEntity<Entities::Projectile>();
            Managers::ComponentsManager::createVisualComponent(bulletId, system->mBlueBullet, 10, 5);
            Managers::ComponentsManager::createSpatialComponent(bulletId, x, y);
            Managers::ComponentsManager::createPathComponent(bulletId, {SDL_Point{moveX, 0}}, 15);
            Managers::ComponentsManager::createDamageComponent(bulletId, 10);
            Managers::ComponentsManager::createTimeToLive(bulletId, 500);

        }
    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::KePressed ,attackCallback);
    mEventsManager->regsiterEventHandler(Events::EventTypes::Collision, bulletCollisionCallback);
    mEventsManager->regsiterEventHandler(Events::EventTypes::EntityCanSee, canSeeEnemy);
    std::shared_ptr<SDL_Surface> imageBlueBullet(SDL_LoadBMP("./res/new_bullet.bmp"), SDL_FreeSurface);
    mBlueBullet = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, imageBlueBullet.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageAkBulletLeft(SDL_LoadBMP("./res/BulletIcon_left.bmp"), SDL_FreeSurface);
    mAkBulletLeft = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, imageAkBulletLeft.get()), SDL_DestroyTexture);
    std::shared_ptr<SDL_Surface> imageAkBulletRight(SDL_LoadBMP("./res/BulletIcon_right.bmp"), SDL_FreeSurface);
    mAkBulletRight = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, imageAkBulletRight.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageHandRight(SDL_LoadBMP("./res/hand_cursor0000Fliped.bmp"), SDL_FreeSurface);
    mTextureHandRight=std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, imageHandRight.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageHandLeft(SDL_LoadBMP("./res/hand_cursor0000.bmp"), SDL_FreeSurface);
    mTextureHandLeft= std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, imageHandLeft.get()), SDL_DestroyTexture);

}

void Systems::CombatSystem::attackWithItem(const Components::Inventory::ItemTypes &pItem) {

}

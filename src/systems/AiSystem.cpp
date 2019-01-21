//
// Created by armin on 13.01.19.
//

#include "AiSystem.h"
#include "../managers/ComponentsManager.h"
#include "../events/MoveEntity.h"
#include "../events/EntityCanSee.h"

Systems::AiSystem::AiSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    auto callback = [system = this](const std::shared_ptr<Events::Event> &pEvent){

    };
}

void Systems::AiSystem::update(uint8_t pTimeDiff) {

    for(const auto &path: Managers::ComponentsManager::getPaths()){

        int diffX = path.second->mPath[path.second->mCurrPos].x - path.second->mXmovedCurStep;
        int diffY = path.second->mPath[path.second->mCurrPos].y - path.second->mYmovedCurStep;

        path.second->mTimeSinceLastStep += pTimeDiff;

        if(path.second->mRunning && !path.second->mPaused){
            int moveX = 0;
            int moveY = 0;
            if(!diffX &&!diffY){
                if(path.second->mCurrPos < path.second->mPath.size()-1){
                    path.second->mCurrPos++;
                    path.second->mXmovedCurStep = 0;
                    path.second->mYmovedCurStep = 0;
                    moveX = path.second->mPath[path.second->mCurrPos].x - path.second->mXmovedCurStep;
                    moveY = path.second->mPath[path.second->mCurrPos].y - path.second->mYmovedCurStep;
                }else if(path.second->mRepeat){
                    path.second->mCurrPos = 0;
                    path.second->mXmovedCurStep = 0;
                    path.second->mYmovedCurStep = 0;
                    moveX = path.second->mPath[path.second->mCurrPos].x - path.second->mXmovedCurStep;
                    moveY = path.second->mPath[path.second->mCurrPos].y - path.second->mYmovedCurStep;
                } else{
                    break;
                }
            }else{
                moveX = diffX;
                moveY = diffY;
            }

            if(diffX<0){
                moveX = std::clamp(moveX,-path.second->mStepsPerFrame,0);
            }else{
                moveX = std::clamp(moveX,0,path.second->mStepsPerFrame);
            }
            if(diffY<0){
                moveY = std::clamp(moveY,-path.second->mStepsPerFrame,0);
            }else{
                moveY = std::clamp(moveY,0,path.second->mStepsPerFrame);
            }
            path.second->mXmovedCurStep += moveX;
            path.second->mYmovedCurStep += moveY;

            mEventsManager->addEvent(std::make_shared<Events::MoveEntity>(path.first,moveX,moveY ));

        }
    }

    auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(1);
    auto playerVisual = Managers::ComponentsManager::getVisualComponent(1);
    int leftLimit = playerSpatial->mPositionX;
    int rightLimit = leftLimit+playerVisual->mImageRect.w;
    int topLimit = playerSpatial->mPositionY;
    int bottomLimit = topLimit+playerVisual->mImageRect.h;

    static int time = 0;
    time+=pTimeDiff;

if(time>=1000) {
    time = 0;
    for (const auto &viewRange: Managers::ComponentsManager::getViewRanges()) {
        auto spatialEntry = Managers::ComponentsManager::getSpatialComponent(viewRange.first);
        if(spatialEntry) {
            int leftLimitEntry = spatialEntry->mPositionX - viewRange.second->mX;
            int rightLimitEntry = spatialEntry->mPositionX + viewRange.second->mX;
            int topLimitEntry = spatialEntry->mPositionY;
            int bottomLimitEntry = spatialEntry->mPositionY + 50;

            bool collision = false;
            if (leftLimit >= leftLimitEntry && leftLimit <= rightLimitEntry) {
                if (topLimit >= topLimitEntry && topLimit <= bottomLimitEntry) {
                    collision = true;
                } else if (bottomLimit < topLimitEntry && bottomLimit > bottomLimitEntry) {
                    collision = true;
                }
            } else if (rightLimit <= leftLimitEntry && rightLimit >= rightLimitEntry) {
                if (topLimit >= topLimitEntry && topLimit <= bottomLimitEntry) {
                    collision = true;
                } else if (bottomLimit <= topLimitEntry && bottomLimit >= bottomLimitEntry) {
                    collision = true;
                }
            }
            if (collision) {
                mEventsManager->addEvent(std::make_shared<Events::EntityCanSee>(viewRange.first, 1));
            } else {
                auto path = Managers::ComponentsManager::getPaths(viewRange.first);
                path->mPaused = false;
            }
        }
    }
}
}


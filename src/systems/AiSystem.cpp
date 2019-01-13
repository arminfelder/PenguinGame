//
// Created by armin on 13.01.19.
//

#include "AiSystem.h"
#include "../managers/ComponentsManager.h"
#include "../events/MoveEntity.h"

Systems::AiSystem::AiSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    auto callback = [system = this](const std::shared_ptr<Events::Event> &pEvent){

    };
}

void Systems::AiSystem::update(uint8_t pTimeDiff) {
    auto paths = Managers::ComponentsManager::getPaths();

    for(const auto &path: paths){

        int diffX = path.second->mPath[path.second->mCurrPos].x - path.second->mXmovedCurStep;
        int diffY = path.second->mPath[path.second->mCurrPos].y - path.second->mYmovedCurStep;

        path.second->mTimeSinceLastStep += pTimeDiff;

        if(path.second->mRunning ){
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
}


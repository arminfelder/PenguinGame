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

#include <SDL_timer.h>
#include <SDL_events.h>
#include "MapViewer.h"
#include "../managers/ComponentsManager.h"

MapViewer::MapViewer() {
    SDL_Rect area1_room1{0,0,100,60};
    SDL_Rect area1_room2{120,0,200,60};
    SDL_Rect area1_room3{340,0,200,60};
    SDL_Rect area1_room4{560,0,100,60};
    SDL_Rect area1_room5{120,72,100,204};

    SDL_Rect area2_room1{240,72,300,204};
    SDL_Rect area2_room2{560,72,100,60};
    SDL_Rect area2_room3{560,144,220,60};
    SDL_Rect area2_room4{560,216,100,60};
    SDL_Rect area2_room5{680,72,100,60};

    SDL_Rect area3_room1{900,0,100,132};
    SDL_Rect area3_room2{800,144,200,60};
    SDL_Rect area3_room3{900,216, 100 ,180};
    SDL_Rect area3_room4{700,408,300, 60};
    SDL_Rect area3_room5{700, 336, 150, 60};

    SDL_Rect area1_room1_area1_room2{90,28,40,4};
    SDL_Rect area1_room2_area1_room3{310,28,40,4};
    SDL_Rect area1_room3_area1_room4{530,28,40,4};
    SDL_Rect area1_room1_area1_room5{148,48,4,36};
    SDL_Rect area1_room5_area2_room1{210,244,40,4};
    SDL_Rect area2_room1_area2_room2{530,100,40,4};
    SDL_Rect area2_room1_area2_room3{530,172,40,4};
    SDL_Rect area2_room1_area2_room4{530,244,40,4};
    SDL_Rect area2_room3_area2_room5{728,114,4,36};
    SDL_Rect area2_room3_area3_room2{770,172,40,4};
    SDL_Rect area3_room2_area3_room1{968,114,4,36};
    SDL_Rect area3_room2_area3_room3{968,192,4,36};
    SDL_Rect area3_room3_area3_room4{968,384,4,36};
    SDL_Rect area3_room4_area3_room5{728,384,4,36};

    SDL_Rect save_point_1{508,20,4,4};
    SDL_Rect save_point_2{168,122,4,4};
    SDL_Rect save_point_3{198,222,4,4};

    SDL_Rect save_point_4{418,182,4,4};
    SDL_Rect save_point_5{518,92,4,4};
    SDL_Rect save_point_6{758,164,4,4};

    SDL_Rect save_point_7{922,62,4,4};
    SDL_Rect save_point_8{982,432,4,4};
    SDL_Rect save_point_9{750,454,4,4};


    mSafePoints.emplace_back(save_point_1);
    mSafePoints.emplace_back(save_point_2);
    mSafePoints.emplace_back(save_point_3);
    mSafePoints.emplace_back(save_point_4);
    mSafePoints.emplace_back(save_point_5);
    mSafePoints.emplace_back(save_point_6);
    mSafePoints.emplace_back(save_point_7);
    mSafePoints.emplace_back(save_point_8);
    mSafePoints.emplace_back(save_point_9);



    mDoorways.emplace_back(area1_room1_area1_room2);
    mDoorways.emplace_back(area1_room2_area1_room3);
    mDoorways.emplace_back(area1_room3_area1_room4);
    mDoorways.emplace_back(area1_room1_area1_room5);
    mDoorways.emplace_back(area1_room5_area2_room1);
    mDoorways.emplace_back(area2_room1_area2_room2);
    mDoorways.emplace_back(area2_room1_area2_room3);
    mDoorways.emplace_back(area2_room1_area2_room4);
    mDoorways.emplace_back(area2_room3_area2_room5);
    mDoorways.emplace_back(area2_room3_area3_room2);
    mDoorways.emplace_back(area3_room2_area3_room1);
    mDoorways.emplace_back(area3_room2_area3_room3);
    mDoorways.emplace_back(area3_room2_area3_room3);
    mDoorways.emplace_back(area3_room2_area3_room3);
    mDoorways.emplace_back(area3_room2_area3_room3);
    mDoorways.emplace_back(area3_room3_area3_room4);
    mDoorways.emplace_back(area3_room4_area3_room5);


    mapComponents.emplace(11,std::make_shared<MapRoom>(area1_room1, "blue"));
    mapComponents.emplace(12,std::make_shared<MapRoom>(area1_room2, "blue"));
    mapComponents.emplace(13,std::make_shared<MapRoom>(area1_room3, "blue"));
    mapComponents.emplace(14,std::make_shared<MapRoom>(area1_room4, "blue"));
    mapComponents.emplace(15,std::make_shared<MapRoom>(area1_room5, "blue"));

    mapComponents.emplace(21,std::make_shared<MapRoom>(area2_room1, "green"));
    mapComponents.emplace(22,std::make_shared<MapRoom>(area2_room2, "green"));
    mapComponents.emplace(23,std::make_shared<MapRoom>(area2_room3, "green"));
    mapComponents.emplace(24,std::make_shared<MapRoom>(area2_room4, "green"));
    mapComponents.emplace(25,std::make_shared<MapRoom>(area2_room5, "green"));

    mapComponents.emplace(31,std::make_shared<MapRoom>(area3_room1, "red"));
    mapComponents.emplace(32,std::make_shared<MapRoom>(area3_room2, "red"));
    mapComponents.emplace(33,std::make_shared<MapRoom>(area3_room3, "red"));
    mapComponents.emplace(34,std::make_shared<MapRoom>(area3_room4, "red"));
    mapComponents.emplace(35,std::make_shared<MapRoom>(area3_room5, "red"));



    mMapMapping.emplace("./res/maps/area1/getDisk.txt",11);
    mMapMapping.emplace("./res/maps/area1/map.txt",12);
    mMapMapping.emplace("./res/maps/area1/map2.txt",13);
    mMapMapping.emplace("./res/maps/area1/boss.txt",14);
    mMapMapping.emplace("./res/maps/area1/downwards.txt",15);

    mMapMapping.emplace("./res/maps/area2/start.txt",21);
    mMapMapping.emplace("./res/maps/area2/boss.txt",22);
    mMapMapping.emplace("./res/maps/area2/map2.txt",23);
    mMapMapping.emplace("./res/maps/area2/getAK.txt",24);
    mMapMapping.emplace("./res/maps/area2/getShield.txt",25);

    mMapMapping.emplace("./res/maps/area3/returner.txt",31);
    mMapMapping.emplace("./res/maps/area3/start.txt",32);
    mMapMapping.emplace("./res/maps/area3/hellEntrance.txt",33);
    mMapMapping.emplace("./res/maps/area3/hell.txt",34);
    mMapMapping.emplace("./res/maps/area3/finalBoss.txt",35);

    mCurrentRoom.a = 255;
    mCurrentRoom.r = 255;
    mCurrentRoom.g = 83;
    mCurrentRoom.b = 255;


}

void MapViewer::render(SDL_Renderer *pRenderer) {
    mRunning = true;
    while (mRunning) {
        auto visited =  Managers::ComponentsManager::getVisitedMaps();
        auto currRoom = Managers::ComponentsManager::getMapName();
        auto currRoomStr = currRoom->getMapName();
        for (const auto &component : visited->getVisitedMaps()) {
            auto room = mapComponents[mMapMapping[component]];

            if(room) {
                auto colorStruct = room->matchColor(room->color);
                if(component == currRoomStr){
                    colorStruct = mCurrentRoom;
                }
                auto surface = room->getSurface();

                SDL_FillRect(surface.get(), nullptr,
                             SDL_MapRGB(surface.get()->format, colorStruct.r, colorStruct.g, colorStruct.b));
                auto texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, surface.get()),
                                                            SDL_DestroyTexture);

                SDL_RenderCopy(pRenderer, texture.get(), nullptr, &room->mRect);
            }
        }
        for(const auto &way:mDoorways){
            std::shared_ptr<SDL_Surface> surface(SDL_CreateRGBSurface(0, way.w, way.h ,32,0,0,0,0), SDL_FreeSurface);

            SDL_FillRect(surface.get(), nullptr,
                         SDL_MapRGB(surface.get()->format, 0,0,0));
            auto texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, surface.get()),
                                                        SDL_DestroyTexture);

            SDL_RenderCopy(pRenderer, texture.get(), nullptr, &way);
        }

        for(const auto &point:mSafePoints){
            std::shared_ptr<SDL_Surface> surface(SDL_CreateRGBSurface(0, point.w, point.h ,32,0,0,0,0), SDL_FreeSurface);

            SDL_FillRect(surface.get(), nullptr,
                         SDL_MapRGB(surface.get()->format, 62,62,62));
            auto texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, surface.get()),
                                                        SDL_DestroyTexture);

            SDL_RenderCopy(pRenderer, texture.get(), nullptr, &point);
        }

        SDL_RenderPresent(pRenderer);
        handleKeyEvent();
        SDL_Delay(static_cast<Uint32> (1000 / 60));
    }
}

void MapViewer::close() {
    mRunning = false;
}

void MapViewer::handleKeyEvent() {
    SDL_Event event;
    SDL_PumpEvents();
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_KEYDOWN)) {
        if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_m:
                case SDLK_p:
                case SDLK_n:
                case SDLK_ESCAPE:
                    this->close();
                    break;
                default: break;
            }
        }
    }

}

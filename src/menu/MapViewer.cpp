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

    SDL_Rect area3_room1{900,0,100,132};
    SDL_Rect area3_room2{800,144,200,60};
    SDL_Rect area3_room3{900,216, 100 ,180};
    SDL_Rect area3_room4{700,408,300, 60};
    SDL_Rect area3_room5{700, 336, 150, 60};

    mapComponents.emplace(11,std::make_shared<MapRoom>(area1_room1, "blue"));
    mapComponents.emplace(12,std::make_shared<MapRoom>(area1_room2, "blue"));
    mapComponents.emplace(13,std::make_shared<MapRoom>(area1_room3, "blue"));
    mapComponents.emplace(14,std::make_shared<MapRoom>(area1_room4, "blue"));
    mapComponents.emplace(15,std::make_shared<MapRoom>(area1_room5, "blue"));

    mapComponents.emplace(21,std::make_shared<MapRoom>(area2_room1, "green"));
    mapComponents.emplace(22,std::make_shared<MapRoom>(area2_room2, "green"));
    mapComponents.emplace(23,std::make_shared<MapRoom>(area2_room3, "green"));
    mapComponents.emplace(24,std::make_shared<MapRoom>(area2_room4, "green"));

    mapComponents.emplace(31,std::make_shared<MapRoom>(area3_room1, "red"));
    mapComponents.emplace(32,std::make_shared<MapRoom>(area3_room2, "red"));
    mapComponents.emplace(33,std::make_shared<MapRoom>(area3_room3, "red"));
    mapComponents.emplace(34,std::make_shared<MapRoom>(area3_room4, "red"));
    mapComponents.emplace(35,std::make_shared<MapRoom>(area3_room5, "red"));



    //mMapMapping.emplace();

}

void MapViewer::render(SDL_Renderer *pRenderer) {
    mRunning = true;
    while (mRunning) {
        for (const auto &component : mapComponents) {
            auto colorStruct = component.second->matchColor(component.second->color);
            auto surface = component.second->getSurface();

            SDL_FillRect(surface.get(),nullptr,SDL_MapRGB(surface.get()->format,colorStruct.r,colorStruct.g,colorStruct.b));
            auto texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, surface.get()), SDL_DestroyTexture);

            SDL_RenderCopy(pRenderer, texture.get(), nullptr, &component.second->mRect);
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

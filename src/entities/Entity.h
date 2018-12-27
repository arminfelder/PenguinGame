#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


#include <SDL_render.h>
#include <vector>
#include "../position.h"
#include "../Dimension.h"
#include "../components/Component.h"
namespace Entities {
    class Entity {
    public:
        Entity(int id);

        int getId() const;

    private:
        int mId;
    };
}

#endif //GAME_ENTITY_H

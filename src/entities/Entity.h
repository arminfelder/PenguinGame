#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


#include <SDL_render.h>
#include <vector>
#include "../position.h"
#include "../Dimension.h"
#include "../components/Component.h"
namespace Entities {
    enum class entityTypes{
        player,
        npc,
        wall,
        ladder,
        none
    };
    class Entity {
    public:
        Entity(int id, entityTypes pType = entityTypes::none);

        int getId() const;
        entityTypes getType();

    protected:
        int mId;
        entityTypes mEntityType;
    };
}

#endif //GAME_ENTITY_H

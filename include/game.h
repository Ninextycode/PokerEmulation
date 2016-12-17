#ifndef GAME_H
#define GAME_H

#include "headers.h"
#include "player.h"
#include "data_structures.h"

namespace pkr {  
    class Player;
    
    class Game {
    public:
        bool isActionValid(Action action);
        void setPlayers(std::vector<std::shared_ptr<Player>> players);
        virtual void PlayGame(std::vector<std::shared_ptr<Player>> players);
        std::vector<std::shared_ptr<Player>> getPlayerActions();
    };
}

#endif /* GAME_H */


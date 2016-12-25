#include "player.h"
#include "game.h"

using namespace pkr;
using namespace std;

void AllInPlayer::markAsWinner() {
    
}

Action AllInPlayer::preformAction(const Game& game) {
    return Action::ActionBuilder().setMoney(myMoney(game))
            .setPlayer(shared_from_this()).setStreet(game.getStreet()).build();
}

int AllInPlayer::myMoney(const Game& currentGame) {
    for(auto pd: currentGame.playersData) {
        if(pd->getPlayer() == shared_from_this()) {
            return pd->getMoney();
        }
    }
}
string AllInPlayer::getName() {
    return this->name;
}
#include "queen.h"
#include "board.h"


Queen::Queen(Pos pos, playingSide side)
    : Piece(pos, side, 9)
    {
        if(side == BLACK_PLAYER)
            this->side = BLACK_PLAYER;
        else
            this->side = WHITE_PLAYER;
    }

shared_ptr<Piece> Queen::add() const {
    return make_shared<Queen>(*this);
}

void Queen::getType() const {
    if(side == BLACK_PLAYER){
        printf("%s ", "♕");
        return ;
    }
    printf("%s ", "♛");
}

bool Queen::canMove(const Pos &newPos, Board & board, bool & isPawnInEnd) {
    if (isEnteredMoveInLine(newPos, board, 1, 0)
      || isEnteredMoveInLine(newPos, board, -1, 0)
      || isEnteredMoveInLine(newPos, board, 0, 1)
      || isEnteredMoveInLine(newPos, board, 0, -1)
      || isEnteredMoveInLine(newPos, board, 1, 1)
      || isEnteredMoveInLine(newPos, board, 1, -1)
      || isEnteredMoveInLine(newPos, board, -1, 1)
      || isEnteredMoveInLine(newPos, board, -1, -1))
        return true;
    return false;
}

string Queen::pieceName() const {
    return "queen";
}

void Queen::to_json(json &j) const {
    j = json{{"type", pieceName()},
             {"posY", pos.y},
             {"posX", pos.getX()}};
}
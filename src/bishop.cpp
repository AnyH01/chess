#include "bishop.h"
#include "board.h"


Bishop::Bishop(Pos pos, playingSide side)
    : Piece(pos, side,3)
    {
        if(side == BLACK_PLAYER)
            this->side = BLACK_PLAYER;
        else
            this->side = WHITE_PLAYER;
    }

shared_ptr<Piece> Bishop::add() const {
    return make_shared<Bishop>(*this);
}

void Bishop::getType() const {
    if(side == BLACK_PLAYER){
        printf("%s ", "♗");
        return ;
    }
    printf("%s ", "♝");
}

bool Bishop::canMove(const Pos &newPos, Board & board, bool & isPawnInEnd) {
    if (isEnteredMoveInLine(newPos, board, 1, 1)
     || isEnteredMoveInLine(newPos, board, 1, -1)
     || isEnteredMoveInLine(newPos, board, -1, 1)
     || isEnteredMoveInLine(newPos, board, -1, -1))
        return true;
    return false;
}

string Bishop::pieceName() const {
    return "bishop";
}

void Bishop::to_json(json &j) const {
    j = json{{"type", pieceName()}, {"posY", pos.y}, {"posX", pos.getX()}};
}

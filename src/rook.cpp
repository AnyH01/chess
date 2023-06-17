#include "rook.h"
#include "board.h"

Rook::Rook(Pos pos, playingSide side)
        : Piece(pos, side, 5)
        , castle(true)
    {
        if(side == BLACK_PLAYER)
            this->side = BLACK_PLAYER;
        else
            this->side = WHITE_PLAYER;


    }
Rook::Rook(Pos pos, playingSide side, bool canCastle)
    : Piece(pos, side, 5)
    , castle(canCastle){}

shared_ptr<Piece> Rook::add() const {
    return make_shared<Rook>(*this);
}

void Rook::getType() const {
    if(side == BLACK_PLAYER){
        printf("%s ", "♖");
        return ;
    }
    printf("%s ", "♜");
}

bool Rook::canMove(const Pos &newPos, Board & board, bool & isPawnInEnd) {
    if (isEnteredMoveInLine(newPos, board, 1, 0)
        || isEnteredMoveInLine(newPos, board, -1, 0)
        || isEnteredMoveInLine(newPos, board, 0, 1)
        || isEnteredMoveInLine(newPos, board, 0, -1)){
        castle = false;
        return true;
    }
    return false;
}

bool Rook::canCastle() const {
    return castle;
}

string Rook::pieceName() const {
    return "rook";
}

void Rook::to_json(json &j) const {
    j = json{{"type", pieceName()}, {"posY", pos.y}, {"posX", pos.getX()}, {"canCastle", castle}};
}



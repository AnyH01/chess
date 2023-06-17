#include "horse.h"
#include "board.h"

Horse::Horse(Pos pos, playingSide side)
    : Piece(pos, side, 3)
    {
        if(side == BLACK_PLAYER)
            this->side = BLACK_PLAYER;
        else
            this->side = WHITE_PLAYER;
    }

shared_ptr<Piece> Horse::add() const {
    return make_shared<Horse>(*this);
}

void Horse::getType() const {
    if(side == BLACK_PLAYER){
        printf("%s ", "♘");
        return ;
    }
    printf("%s ", "♞");
}

bool Horse::canMove(const Pos &newPos, Board & board, bool & isPawnInEnd) {
    if (isEnteredMove(Pos(pos.getX()+2, pos.getY()+1), newPos, board)
      || isEnteredMove(Pos(pos.getX()+1, pos.getY()+2), newPos, board)
      || isEnteredMove(Pos(pos.getX()-1, pos.getY()+2), newPos, board)
      || isEnteredMove(Pos(pos.getX()-2, pos.getY()+1), newPos, board)
      || isEnteredMove(Pos(pos.getX()-2, pos.getY()-1), newPos, board)
      || isEnteredMove(Pos(pos.getX()-1, pos.getY()-2), newPos, board)
      || isEnteredMove(Pos(pos.getX()+1, pos.getY()-2), newPos, board)
      || isEnteredMove(Pos(pos.getX()+2, pos.getY()-1), newPos, board))
        return true;
    return false;
}

string Horse::pieceName() const {
    return "horse";
}

void Horse::to_json(json &j) const {
    j = json{{"type", pieceName()}, {"posY", pos.y}, {"posX", pos.getX()}};
}

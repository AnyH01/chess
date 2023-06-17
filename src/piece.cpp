#include "piece.h"
#include "board.h"


Piece::Piece(Pos pos, playingSide side, int value)
    : pos(pos)
    , side(side)
    , value(value)
    {}

void Piece::getType() const {
    return;
}

shared_ptr<Piece> Piece::add() const {
    return shared_ptr<Piece>();
}

bool Piece::canMove(const Pos &newPos, Board & board, bool & isPawnInEnd) {
    return false;
}

bool Piece::isEnteredMove(const Pos &currPos, const Pos &enteredPos, const Board &board) const {
    if (board.isPosOnBoard(currPos) && currPos == enteredPos)
        return true;
    return false;
}

bool Piece::isEnteredMoveInLine(const Pos &newPos, const Board &board, int xLine, int yLine) const {
    Pos currPos(pos.getX(), pos.getY());
    while (true){
        currPos.setPos(currPos.getX()+xLine, currPos.getY()+yLine);
        if(!board.isPosOnBoard(currPos))
            break;
        if(currPos == newPos)
            return true;
        if (board.board[currPos.XInBoard()][currPos.YInBoard()] != nullptr)
            break;
    }
    return false;
}

bool Piece::isKing() {
    if (value == INT_MAX)
        return true;
    return false;
}

bool Piece::isPawn() {
    if (value == 1)
        return true;
    return false;
}

bool Piece::isDoubleMoved() const{
    return false;
}

void Piece::setPawnDoubleMove() {

}

bool Piece::canCastle() const {
    return false;
}

string Piece::pieceName() const {
    return std::string();
}

void Piece::to_json(json &j) const {

}

Piece::Piece() {

}

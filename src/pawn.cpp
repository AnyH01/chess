#include "pawn.h"
#include "board.h"
using namespace std;

Pawn::Pawn(Pos pos, playingSide side)
    : Piece(pos, side, 1)
    , doubleMove(false)
    , isNotMove(true)
    {
        if(side == BLACK_PLAYER)
            this->side = BLACK_PLAYER;
        else
            this->side = WHITE_PLAYER;
    }

Pawn::Pawn(Pos pos, playingSide side, bool notMove, bool notDoubleMove) : Piece(pos, side, 1), doubleMove(notDoubleMove), isNotMove(notMove){
    this->side = side;
}
shared_ptr<Piece> Pawn::add() const {
    return make_shared<Pawn>(*this);
}

void Pawn::getType() const {
    if(side == BLACK_PLAYER){
        printf("%s ", "♙");
        return;
    }
    printf("%s ", "♟︎");
}

bool Pawn::success(const Pos & pos, const Board & board, bool & isPawnInEnd) {
    isNotMove = false;
    if (pos.getX() == 1 || pos.getX() == board.size)
        isPawnInEnd = true;
    return true;
}

bool Pawn::canMove(const Pos& newPos, Board & board, bool & isPawnInEnd) {
    if (side == WHITE_PLAYER){
        if (pos.getY() == newPos.getY() && board.isPosOnBoard(Pos(pos.getX()+1, pos.getY())) && board.board[pos.XInBoard()+1][pos.YInBoard()] == nullptr){
            if (pos.getX()+1 == newPos.getX()){
                return success(newPos, board, isPawnInEnd);
            }
            if(isNotMove && isEnteredMove(Pos(pos.getX()+2, pos.getY()), newPos, board) && board.board[pos.XInBoard()+2][pos.YInBoard()] == nullptr){
                doubleMove = true;
                return success(newPos, board, isPawnInEnd);
            }
            return false;
        }
        if (pos.getY() != newPos.getY()) {
            if(isEnteredMove(Pos(pos.getX()+1, pos.getY()+1), newPos, board) && board.board[pos.XInBoard()+1][pos.YInBoard()+1] != nullptr){
                return success(newPos, board, isPawnInEnd);
            }
            if(isEnteredMove(Pos(pos.getX()+1, pos.getY()-1), newPos, board) && board.board[pos.XInBoard()+1][pos.YInBoard()-1] != nullptr) {
                return success(newPos, board, isPawnInEnd);
            }
            if (canEnPassant(Pos(pos.getX()+1, pos.getY()+1), newPos, board, -1)
              || canEnPassant(Pos(pos.getX()+1, pos.getY()-1), newPos, board, -1))
                return success(newPos, board, isPawnInEnd);
            return false;
        }
        return false;
    }
    if (side == BLACK_PLAYER){
        if (pos.getY() == newPos.getY() && board.isPosOnBoard(Pos(pos.getX()-1, pos.getY())) && board.board[pos.XInBoard()-1][pos.YInBoard()] == nullptr){
            if (pos.getX()-1 == newPos.getX()){
                return success(newPos, board, isPawnInEnd);
            }
            if(isNotMove && isEnteredMove(Pos(pos.getX()-2, pos.getY()), newPos, board) && board.board[pos.XInBoard()-2][pos.YInBoard()] == nullptr){
                doubleMove = true;
                return success(newPos, board, isPawnInEnd);
            }
            return false;
        }
        if (pos.getY() != newPos.getY()) {
            if(isEnteredMove(Pos(pos.getX()-1, pos.getY()+1), newPos, board) && board.board[pos.XInBoard()-1][pos.YInBoard()+1] != nullptr){
                return success(newPos, board, isPawnInEnd);
            }
            if(isEnteredMove(Pos(pos.getX()-1, pos.getY()-1), newPos, board) && board.board[pos.XInBoard()-1][pos.YInBoard()-1] != nullptr) {
                return success(newPos, board, isPawnInEnd);
            }
            if (canEnPassant(Pos(pos.getX()-1, pos.getY()+1), newPos, board, 1)
              || canEnPassant(Pos(pos.getX()-1, pos.getY()-1), newPos, board, 1)) {
                return success(newPos, board, isPawnInEnd);
            }
            return false;
        }
        return false;
    }
    return false;
}

void Pawn::setPawnDoubleMove() {
    doubleMove = false;
}

bool Pawn::canEnPassant(const Pos &currPos, const Pos &newPos, Board & board, const int player) {
    if(isEnteredMove(currPos, newPos, board) && board.board[currPos.XInBoard()][currPos.YInBoard()] == nullptr) {
        if (board.board[currPos.XInBoard()+player][currPos.YInBoard()] != nullptr) {
            if (board.board[currPos.XInBoard()+player][currPos.YInBoard()]->side != side) {
                if (board.board[currPos.XInBoard()+player][currPos.YInBoard()]->isDoubleMoved()) {

                    board.board[currPos.XInBoard()+player][currPos.YInBoard()].reset();
                    return true;
                }
            }
        }
    }
    return false;
}

bool Pawn::isDoubleMoved() const {
    return doubleMove;
}

string Pawn::pieceName() const {
    return "pawn";
}

void Pawn::to_json(json &j) const {
    cout << pos.y << endl;
    j = json{{"type", pieceName()}, {"posY",char(pos.y)}, {"posX", pos.getX()}, {"doubleMove", doubleMove}, {"isNotMove", isNotMove}};
}





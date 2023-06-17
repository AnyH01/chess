#include "king.h"
#include "board.h"


King::King(Pos pos, playingSide side)
    : Piece(pos, side, INT_MAX)
    , castle(true)
    {
        if(side == BLACK_PLAYER)
            this->side = BLACK_PLAYER;
        else
            this->side = WHITE_PLAYER;
    }

King::King(Pos pos, playingSide side, bool canCanCastle)
        : Piece(pos, side, INT_MAX)
        , castle(canCanCastle)
    {
        this->side = side;
    }

shared_ptr<Piece> King::add() const {
    return make_shared<King>(*this);
}

void King::getType() const {
    if(side == BLACK_PLAYER){
        printf("%s ", "♔");
        return;
    }
    printf("%s ", "♚");
}

bool King::canMove(const Pos &newPos, Board & board, bool & isPawnInEnd) {
    if ((isEnteredMove(Pos(pos.getX()+1, pos.getY()-1), newPos, board) && !isOtherKingNextTo(newPos, board))
        || (isEnteredMove(Pos(pos.getX()+1, pos.getY()), newPos, board) && !isOtherKingNextTo(newPos, board))
        || (isEnteredMove(Pos(pos.getX()+1, pos.getY()+1), newPos, board) && !isOtherKingNextTo(newPos, board))
        || (isEnteredMove(Pos(pos.getX(), pos.getY()+1), newPos, board) && !isOtherKingNextTo(newPos, board))
        || (isEnteredMove(Pos(pos.getX()-1, pos.getY()+1), newPos, board) && !isOtherKingNextTo(newPos, board))
        || (isEnteredMove(Pos(pos.getX()-1, pos.getY()), newPos, board) && !isOtherKingNextTo(newPos, board))
        || (isEnteredMove(Pos(pos.getX()-1, pos.getY()-1), newPos, board) && !isOtherKingNextTo(newPos, board))
        || (isEnteredMove(Pos(pos.getX(), pos.getY()-1), newPos, board) && !isOtherKingNextTo(newPos, board))
        || IsCastle(pos, newPos, board, 1)
        || IsCastle(pos, newPos, board, -1)){
        castle = false;
        return true;
    }
    return false;
}

bool King::IsCastle(const Pos &from, const Pos &to, Board &board, int castleSide) {
    if(castle && Pos(from.getX(), from.getY()+(castleSide*2)) == to && !isPosUnderAttack(from, side, board)){
        for (int y = from.YInBoard()+castleSide; y < board.size; y+=castleSide) {
            if (isPosUnderAttack(Pos(from.XInBoard(), y), side, board))
                return false;
            if(board.board[from.XInBoard()][y] != nullptr && board.board[from.XInBoard()][y]->canCastle()) {
                board.board[from.XInBoard()][y] = nullptr;
                board.addPiece(Rook(Pos(to.getX(), to.getY()-castleSide), side));
                return true;
            }
            if(board.board[from.XInBoard()][y] != nullptr)
                return false;
        }
    }
    return false;
}

bool King::isPosUnderAttack(const Pos &pos, const playingSide & side, Board &board) {
    bool b = false;
    for (int x = 0; x < board.size; x++) {
        for (int y = 0; y < board.size; y++) {
            if (board.board[x][y] != nullptr && board.board[x][y]->side != side && board.board[x][y]->canMove(pos, board, b))
                return true;
        }
    }
    return false;
}

string King::pieceName() const {
    return "king";
}

void King::to_json(json &j) const {j = json{{"type", pieceName()}, {"posY", pos.y}, {"posX", pos.getX()}, {"castle", castle}};
}

bool King::isOtherKingNextTo(const Pos & pos, const Board & board) {
    if (isKingOnPos(Pos(pos.getX()+1, pos.getY()-1), board)
        || isKingOnPos(Pos(pos.getX()+1, pos.getY()), board)
        || isKingOnPos(Pos(pos.getX()+1, pos.getY()+1), board)
        || isKingOnPos(Pos(pos.getX(), pos.getY()+1), board)
        || isKingOnPos(Pos(pos.getX()-1, pos.getY()+1), board)
        || isKingOnPos(Pos(pos.getX()-1, pos.getY()), board)
        || isKingOnPos(Pos(pos.getX()-1, pos.getY()-1), board)
        || isKingOnPos(Pos(pos.getX(), pos.getY()-1), board))
        return true;
    return false;
}

bool King::isKingOnPos(const Pos &pos, const Board &board) {
    if (board.isPosOnBoard(Pos(pos.XInBoard(), pos.YInBoard()))
    && board.board[pos.XInBoard()][pos.YInBoard()] != nullptr
    && board.board[pos.XInBoard()][pos.YInBoard()]->isKing()
    && board.board[pos.XInBoard()][pos.YInBoard()]->side != side)
        return true;
    return false;
}




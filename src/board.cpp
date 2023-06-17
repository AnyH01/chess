#include <iostream>
#include "board.h"

using namespace std;




/*
3|
2|
1|
0|
 +_ _ _ _ _ _ _
  a b c d e f g
  0 1 2 3 4 5 6
  a2 -> board[1][0]
  board[rádek - čísla][sloupeček - písmenka]
 */
Board::Board(): size(8){
    board.resize(8);
    for(size_t i = 0; i < 8; i++)
        board[i].resize(8);
}

Board::Board(int size): size(size){
    board.resize(size);
    for(int16_t i = 0; i < size; i++)
        board[i].resize(size);
}


Board::Board(const Board& oldBoard) {
    size = oldBoard.size;
    board.resize(oldBoard.size);
    for(int i = 0; i < oldBoard.size; i++)
        this->board[i].resize(oldBoard.size);

    for(int i = 0; i < oldBoard.size; i++){
        for(int j = 0; j < oldBoard.size; j++){
            if(oldBoard.board[i][j])
                this->board[i][j] = oldBoard.board[i][j]->add();
        }
    }
}

Board& Board::operator=(const Board& oldBoard) {
    size = oldBoard.size;
    board.clear();
    board.resize(oldBoard.size);
    for(int i = 0; i < oldBoard.size; i++)
        this->board[i].resize(oldBoard.size);

    for(int i = 0; i < oldBoard.size; i++){
        for(int j = 0; j < oldBoard.size; j++){
            if(oldBoard.board[i][j])
                this->board[i][j] = oldBoard.board[i][j]->add();
        }
    }

    return *this;
}

void Board::setSize(int boardSize) {
    size = boardSize;
    board.resize(size);
    for(int i = 0; i < size; i++)
        board[i].resize(size);
}

Board & Board::addPiece(const Piece &piece) {
    //berme v potaz souřadnici c2 a pozici figurky je x jako '2' a y jako 'c' ale
    // protože to potřebujeme přenést do pole tak v poli jsou to indexy [1][2]
    board[piece.pos.getX() - 1][piece.pos.getY() - 97] = piece.add();
    return *this;
}

void Board::print() {
    cout << "   ";
    for(int i = 0; i < size; i++)
        cout << " " << char('a' + i) << "  ";
    cout << endl;
    cout << " ";
    for (size_t i = 0; i < board.size() * 3 + board.size() + 1; i++) {
        if (i == 0 || i == board.size() * 3 + board.size())
            cout << "+";
        else
            cout << "-";
    }
    cout << endl;
    int x = 1;
    for (auto & i : board) {
        cout << x << " |";
        for (auto & j : i) {
            cout << " ";
            if (j) {
                j->getType();
            } else {
                cout << "  ";
            }
            cout << "|";
        }
        cout << endl;
        cout << "  ";
        for (size_t k = 0; k < board.size() * 3 + board.size() + 1; k++) {
            if (k == 0 || k == board.size() * 3 + board.size())
                cout << "+";
            else
                cout << "-";
        }
        cout << endl;
        x++;
    }
}

bool Board::isPosOnBoard(const Pos &pos) const {
    if (pos.XInBoard() < 0 || pos.XInBoard() >= size || pos.YInBoard() < 0 || pos.YInBoard() >= size)
        return false;
    return true;
}

void Board::isPossibleEnPassant(const Pos &lastMove) {
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            if (board[x][y] != nullptr && (Pos(x, y) != Pos(lastMove.XInBoard(), lastMove.YInBoard())))
                board[x][y]->setPawnDoubleMove();
        }
    }
}

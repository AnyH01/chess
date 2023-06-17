#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <vector>
#include <memory>
#include <cstdio>
#include "piece.h"

using namespace std;


/**
 * Class that represents chessboard with all pieces on it.
**/
class Board {
public:
    /**
     * @brief Length of the one side of the board.
    **/
    int size;

    /**
     * @brief All pieces on the board on their positions.
    **/
    vector<vector<shared_ptr<Piece>>> board;

    
    /**
     * @brief Constructor initialize length of the board on eight.
     **/
    Board();

    /**
     * @brief Copy constructor.
     * @param oldboard Board from witch creates a copy.
     **/
    Board(const Board& oldBoard);

    /**
     * @brief Constructor initialize length of the board on size.
     * @param size Length of the side of the board.
     **/
    Board(int size);

    
    Board& operator=(const Board& oldBoard);

    /**
     * @brief Method that set size of the board to the entered value.
     * @param boardSize Length of the side of the board.
     **/
    void setSize(int boardSize);

    /**
     * @brief Method that add piece to the board.
     * @param piece Piece that will be add.
     * @return Returns board with add piece.
     **/
    Board & addPiece(const Piece & piece);

    /**
     * @brief Method that print the board.
     **/
    void print();

    /**
     * @brief Method that controls if entered pozition is on the board.
     * @param pos Entered position.
     * @return Returns true if the position is on board, false otherwise.
     **/
    bool isPosOnBoard(const Pos &pos) const;

    /**
     * @brief Method that deletes doubleMove flags from pawns expect the last one.
     * @param lastMove Position of last moved piece.
     **/
    void isPossibleEnPassant (const Pos & lastMove);
};

#endif //CHESS_BOARD_H

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include <memory>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <limits.h>
#include "pos.h"
#include "../libs/json.hpp"

//#include "board.h"
#include "playingSide.h"
#include "string"

using json = nlohmann::json;
using namespace std;


class Board;

/**
* Class represents piece.
**/
class Piece {
public:
    /**
    * @brief Position of piece.
    **/
    Pos pos;

    /**
    * @brief Playing side of piece.
    **/
    playingSide side;

    /**
    * @brief Default constructor.
    **/
    Piece();

    /**
    * @brief Constructor that sets all variables.
    * @param pos Position of the piece.
    * @param side Playing side of the piece.
    * @param value Value of the playing piece.
    **/
    Piece(Pos pos, playingSide side, int value);

    /**
     * @brief Virtual method that creates shared pointer from piece.
     * @return Returns shared pointer of piece.
     **/
    virtual shared_ptr<Piece> add () const;

    /**
     * @brief Virtual method that displays piece.
     **/
    virtual void getType() const;
    
    /**
     * @brief Virtual method that finds out if the piece can move on the entered posotion.
     * @param newPos Position of the piece to be move to.
     * @param board Board with all pieces on it.
     * @param isPawnInEnd Checks if piece is pawn and if is in the end of the board.
     * @return Returns true if the piece can make the move, false otherwise.
     **/
    virtual bool canMove(const Pos & newPos, Board & board, bool & isPawnInEnd);

    /**
     * @brief Method that checks if the piece is king.
     * @return Returns true if the piece is king, false otherwise.
     **/
    bool isKing();

    /**
     * @brief Method that checks if the piece is pawn.
     * @return Returns true if the piece is pawn, false otherwise.
     **/
    bool isPawn();

    /**
     * @brief Virtual method that sets pawn's doubleMove flag on false.
     **/
    virtual void setPawnDoubleMove();

    /**
     * @brief Virtual method that finds out if the pawn moved double in last round.
     * @return Returns true if the pawn moved double, false otherwise.
     **/
    virtual bool isDoubleMoved() const;

    /**
     * @brief Virtual method that finds out if the piece can castle.
     * @return Returns true if the piece can castle, false otherwise.
     **/
    virtual bool canCastle() const;

    /**
     * @brief Virtual method that returns type of the piece.
     * @return Returns name of the piece.
     **/
    virtual string pieceName() const;

    /**
     * @brief Virtual method that sets piece to the json.
     * @param j Json file for write piece.
     **/
    virtual void to_json(json& j) const;

protected:
    /**
     * @brief Value of the piece.
     **/
    int value;

    /**
     * @brief Method that checks if the positions are equal.
     * @param currPos Current position to compare with.
     * @param newPos Position to try.
     * @param board Board with all pieces on it.
     * @return Returns true if the positions are equal, false otherwise.
     **/
    bool isEnteredMove (const Pos &currPos, const Pos & newPos, const Board & board) const;

    /**
     * @brief Method that checks if the position is on the line.
     * @param newPos Position to try.
     * @param board Board with all pieces on it.
     * @param xLine Says which direction the x-axis line will go.
     * @param yLine Says which direction the y-axis line will go.
     * @return Returns true if the position is on the line, false otherwise.
     **/
    bool isEnteredMoveInLine (const Pos & newPos, const Board & board, int xLine, int yLine) const;
};

#endif //CHESS_PIECE_H

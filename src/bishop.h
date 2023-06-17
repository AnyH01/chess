#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "piece.h"
#include "string"


/**
 * Class bishop.
**/
class Bishop : public Piece {
public:
    /**
     * @brief Constructor that initialize all variebles.
     * @param pos Position of the creates bishop.
     * @param side Side of the creates bishop.
    **/
    Bishop(Pos pos, playingSide side);

    /**
     * @brief Method that creates shared pointer from bishop.
     * @return Returns shared pointer of bishop.
     **/
    shared_ptr<Piece> add () const override;

    /**
     * @brief Method that displays bishop.
     **/
    void getType() const override;

    /**
     * @brief Method that finds out if the bishop can move on the entered posotion.
     * @param newPos Position of the bishop to be move to.
     * @param board Board with all pieces on it.
     * @param isPawnInEnd Checks if piece is pawn and if is in the end of the board.
     * @return Returns true if the bishop can make the move, false otherwise.
     **/
    bool canMove(const Pos & newPos, Board & board, bool & isPawnInEnd) override;

    /**
     * @brief Method that returns type of the piece.
     * @return Returns bishop.
     **/
    string pieceName() const override;

    /**
     * @brief Method that sets bishop to the json.
     * @param j Json file for write piece.
     **/
    void to_json(json& j) const override;

};

#endif //CHESS_BISHOP_H

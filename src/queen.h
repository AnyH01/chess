#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "piece.h"
#include "string"


/**
 * Class queen.
**/
class Queen : public Piece {
public:
    /**
     * @brief Constructor that initialize all variebles.
     * @param pos Position of the creates queen.
     * @param side Side of the creates queen.
    **/
    Queen(Pos pos, playingSide side);

    /**
     * @brief Method that creates shared pointer from queen.
     * @return Returns shared pointer of queen.
     **/
    shared_ptr<Piece> add() const override;

    /**
     * @brief Method that displays queen.
     **/
    void getType() const override;

    /**
     * @brief Method that finds out if the queen can move on the entered posotion.
     * @param newPos Position of the queen to be move to.
     * @param board Board with all pieces on it.
     * @param isPawnInEnd Checks if piece is pawn and if is in the end of the board.
     * @return Returns true if the queen can make the move, false otherwise.
     **/
    bool canMove(const Pos & newPos, Board & board, bool & isPawnInEnd) override;

    /**
     * @brief Method that returns type of the piece.
     * @return Returns queen.
     **/
    string pieceName() const override;

    /**
     * @brief Method that sets queen to the json.
     * @param j Json file for write piece.
     **/
    void to_json(json& j) const override;


};

#endif //CHESS_QUEEN_H

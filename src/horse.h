#ifndef CHESS_HORSE_H
#define CHESS_HORSE_H
#include "piece.h"
#include "string"


/**
 * Class horse.
**/
class Horse : virtual public Piece {
public:
    /**
     * @brief Constructor that initialize all variebles.
     * @param pos Position of the creates horse.
     * @param side Side of the creates horse.
    **/
    Horse(Pos pos, playingSide side);

    /**
     * @brief Method that creates shared pointer from horse.
     * @return Returns shared pointer of horse.
     **/
    shared_ptr<Piece> add() const override;

    /**
     * @brief Method that displays horse.
     **/
    void getType() const override;

    /**
     * @brief Method that finds out if the horse can move on the entered posotion.
     * @param newPos Position of the horse to be move to.
     * @param board Board with all pieces on it.
     * @param isPawnInEnd Checks if piece is pawn and if is in the end of the board.
     * @return Returns true if the horse can make the move, false otherwise.
     **/
    bool canMove(const Pos & newPos, Board & board, bool & isPawnInEnd) override;

    /**
     * @brief Method that returns type of the piece.
     * @return Returns horse.
     **/
    string pieceName() const override;

    /**
     * @brief Method that sets horse to the json.
     * @param j Json file for write piece.
     **/
    void to_json(json& j) const override;


};

#endif //CHESS_HORSE_H

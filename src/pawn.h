#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "piece.h"
#include "string"


/**
 * Class pawn.
**/
class Pawn : public Piece {
public:
    /**
     * @brief Constructor that initialize all variebles.
     * @param pos Position of the creates pawn.
     * @param side Side of the creates pawn.
    **/
    Pawn(Pos pos, playingSide side);

    /**
     * @brief Constructor that initialize all variebles.
     * @param pos Position of the creates pawn.
     * @param side Side of the creates pawn.
     * @param notMove Bool if the pawn already moved or don't
     * @param notDoubleMoved Bool if the pawn moved double in last round.
    **/
    Pawn(Pos pos, playingSide side, bool notMove, bool notDoubleMove);

    /**
     * @brief Method that creates shared pointer from pawn.
     * @return Returns shared pointer of pawn.
     **/
    shared_ptr<Piece> add() const override;

    /**
     * @brief Method that displays pawn.
     **/
    void getType() const override;

    /**
     * @brief Method that finds out if the pawn can move on the entered posotion.
     * @param newPos Position of the pawn to be move to.
     * @param board Board with all pieces on it.
     * @param isPawnInEnd Checks if piece is pawn and if is in the end of the board.
     * @return Returns true if the pawn can make the move, false otherwise.
     **/
    bool canMove(const Pos & newPos, Board & board, bool & isPawnInEnd) override;

    /**
     * @brief Method that sets variable doubleMove on false.
     **/
    void setPawnDoubleMove() override;

    /**
     * @brief Method that finds out if the pawn moved double in the last round.
     * @return Returns true if the pawn moved double, false otherwise.
     **/
    bool isDoubleMoved() const override;

    /**
     * @brief Method that returns type of the piece.
     * @return Returns pawn.
     **/
    string pieceName() const override;

    /**
     * @brief Method that sets pawn to the json.
     * @param j Json file for write piece.
     **/
    void to_json(json& j) const override;


private:
    /**
     * @brief Pawn moved double in the last round.
     **/
    bool doubleMove;

    /**
     * @brief Pawn doesn't already moved.
     **/
    bool isNotMove;

    /**
     * @brief Method that sets all variables.
     * @param pos Position of the pawn.
     * @param board Board with all pieces on it.
     * @param isPawnInEnd Checks if piece is pawn and if is in the end of the board.
     * @return Returns true.
     **/
    bool success(const Pos & pos, const Board & board, bool & isPawnInEnd);

    /**
     * @brief Method that finds out if the entered move was en passant.
     * @param currPos Start position of the pawn.
     * @param newPos End position of the pawn.
     * @param board Board with all pieces on it.
     * @param player Set on 1 if plays black player, -1 if the white one.
     * @return Returns true if the en passant is possible, false otherwise.
     **/
    bool canEnPassant (const Pos &currPos, const Pos &newPos, Board &board, const int player);
};

#endif //CHESS_PAWN_H

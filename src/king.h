#ifndef CHESS_KING_H
#define CHESS_KING_H
#include "piece.h"
#include "string"
#include "rook.h"


/**
 * Class kin.
**/
class King : public Piece {
public:
    /**
     * @brief Constructor that initialize all variebles.
     * @param pos Position of the creates king.
     * @param side Side of the creates king.
    **/
    King(Pos pos, playingSide side);

    /**
     * @brief Constructor that initialize all variebles.
     * @param pos Position of the creates king.
     * @param side Side of the creates king.
     * @param canCastle Bool if the king can do castle or not.
    **/
    King(Pos pos, playingSide side, bool canCastle);

    /**
     * @brief Method that creates shared pointer from king.
     * @return Returns shared pointer of king.
     **/
    shared_ptr<Piece> add() const override;

    /**
     * @brief Method that displays king.
     **/
    void getType() const override;

    /**
     * @brief Method that finds out if the king can move on the entered posotion.
     * @param newPos Position of the king to be move to.
     * @param board Board with all pieces on it.
     * @param isPawnInEnd Checks if piece is pawn and if is in the end of the board.
     * @return Returns true if the king can make the move, false otherwise.
     **/
    bool canMove(const Pos & newPos, Board & board, bool & isPawnInEnd) override;

    /**
     * @brief Method that finds out if the king can castle.
     * @param from Position of the king to be move from.
     * @param to Position of the king to be move to.
     * @param board Board with all pieces on it.
     * @param castleSide On which side will king do the castle.
     * @return Returns true if the king can make the castle, false otherwise.
     **/
    bool IsCastle(const Pos & from,const Pos & to, Board & board, int castleSide);

    /**
     * @brief Method that returns type of the piece.
     * @return Returns king.
     **/
    string pieceName() const override;

    /**
     * @brief Method that sets king to the json.
     * @param j Json file for write piece.
     **/
    void to_json(json& j) const override;

private:
    /**
     * @brief If king can do the castle or not.
     **/
    bool castle;

    /**
     * @brief Method that finds out if the position is under attack.
     * @param pos Position to be try to.
     * @param side Side of player.
     * @param board Board with all pieces on it.
     * @return Returns true if the position is under attack, false otherwise.
     **/
    bool isPosUnderAttack(const Pos & pos, const playingSide & side, Board & board);

    /**
     * @brief Method that finds out if the other king is in next position.
     * @param pos Position to be try to.
     * @param board Board with all pieces on it.
     * @return Returns true if the other king is next to, false otherwise.
     **/
    bool isOtherKingNextTo(const Pos & pos, const Board & board);

    /**
     * @brief Method that finds out if the other king is on position.
     * @param pos Position to be try to.
     * @param board Board with all pieces on it.
     * @return Returns true if the other king is on position, false otherwise.
     **/
    bool isKingOnPos (const Pos & pos, const Board & board);
};

#endif //CHESS_KING_H

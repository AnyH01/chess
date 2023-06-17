#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H
#include "piece.h"
#include "string"
using namespace std;

/**
 * Class rook.
**/
class Rook : public Piece {
public:
    /**
     * @brief Constructor that initialize all variebles.
     * @param pos Position of the creates rook.
     * @param side Side of the creates rook.
    **/
    Rook(Pos pos, playingSide side);

    /**
     * @brief Constructor that initialize all variebles.
     * @param pos Position of the creates rook.
     * @param side Side of the creates rook.
     * @param canCastle Bool if the rook can do castle or not.
    **/
    Rook(Pos pos, playingSide side, bool canCastle);

    /**
     * @brief Method that creates shared pointer from rook.
     * @return Returns shared pointer of rook.
     **/
    shared_ptr<Piece> add() const override;

    /**
     * @brief Method that displays rook.
     **/
    void getType() const override;

    /**
     * @brief Method that finds out if the rook can move on the entered posotion.
     * @param newPos Position of the rook to be move to.
     * @param board Board with all pieces on it.
     * @param isPawnInEnd Checks if piece is pawn and if is in the end of the board.
     * @return Returns true if the rook can make the move, false otherwise.
     **/
    bool canMove(const Pos & newPos, Board & board, bool & isPawnInEnd) override;

    /**
     * @brief Method that finds out if the rook can castle.
     * @return Returns true if the piece can castle, false otherwise.
     **/
    bool canCastle() const override;

    /**
     * @brief Method that returns type of the piece.
     * @return Returns rook.
     **/
    string pieceName() const override;

    /**
     * @brief Method that sets rook to the json.
     * @param j Json file for write piece.
     **/
    void to_json(json& j) const override;


private:
    bool castle;
};

#endif //CHESS_ROOK_H

#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include <limits>
#include "gameManager.h"
#include "board.h"
#include "pos.h"
#include "bishop.h"
#include "horse.h"
#include "king.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include "../libs/json.hpp"
using json = nlohmann::json;
using namespace std;


/**
 * Class contains common methods and variables for game2P and gameAI.
 **/
class Game{
public:

    /**
     * @brief An class board instance.
     **/
    Board board;

    /**
     * @brief Position on board of the white king.
     **/
    Pos posWhiteKing;

    /**
     * @brief Position on board of the black king.
     **/
    Pos posBlackKing;

    /**
     * @brief String that resets color to the original one.
    */
    const string ANSI_RESET = "\033[0m";

    /**
     * @brief String that sets color to the red.
    */
    const string ANSI_RED = "\033[31m";
    

    /**
     * Constructor initialize all variables.
     **/
    Game();

    /**
     * @brief Method loads a number from user.
     * @param maxInput Number with the maximum number of choices.
     * @return Returns number of choice.
     **/
    int loadInput(int maxInput);

    /**
     * @brief Method that loads size of the board and placement of pieces.
     * @param configPath Path to configuration file.
     * @return Returns true if the file load was successful and false otherwise.
     **/
    bool loadConfig(const string & configPath);

    /**
     * @brief Method that configurates the board according to the data from json file.
     * @param js Json file with saved data.
     * @param side Designations current player.
     * @param player String that matches the one in the file.
     **/
    bool configBoard(const json & js, const playingSide & side, const string & player);

    /**
     * @brief Method loads from json file game layout.
     * @param js Json file with saved game.
     * @param side Designations current player.
     * @param player String that matches the one in the file.
     **/
    bool configSavedBoard(const json &js, playingSide side, const string &player);

    /**
     * @brief Method that makes a player's move.
     * @param player Designations current player.
     * @return Returns true if the game is over (current player wins).
     **/
    bool playerMove(const playingSide & player);

    /**
     * @brief Method that checks that entered move is valid.
     * @param from Position of piece that player wants to move.
     * @param to Position the player wants to move to.
     * @param player Designations current player.
     * @return Returns true if the move is valid.
     **/
    bool isValidMove(const Pos & from, const Pos & to, const playingSide & player);

    /**
     * @brief Method that projects players move to the board.
     * @param board Board with all pieces on it.
     * @param from Position of piece that player moved.
     * @param to Position the player moved to.
     * @param player Designations current player.
     **/
    void deletePiece(Board &board, const Pos & from, const Pos & to, const playingSide & player);

    /**
     * @brief Method that changes pawn to the other piece if is in the end of the board.
     * @param pos Position of the pawn id the board.
     * @param player Designations current player.
     **/
    void pawnTransformation(const Pos & pos, const playingSide & player);

    /**
     * @brief Method that finds out if the king is check.
     * @param board Board with all pieces on it.
     * @param player Designations current player.
     * @return Returns true if the king is check, false otherwise.
     **/
    bool isKingCheck(Board & board, const playingSide & player);

    /**
     * @brief Method that finds out if the current player is in check.
     * @param myBoard Board with all pieces on it.
     * @param from Position of piece that player moved.
     * @param to Position the player moved to.
     * @param player Designations current player.
     * @return Returns true if the player is in check, false otherwise.
     **/
    bool isPlayerCheck(Board & board, const Pos & from, const Pos & to, const playingSide & player);

    /**
     * @brief Method that finds out if the current player is in checkmate.
     * @param player Designations current player.
     * @return Returns true if the player is in checkmate, false otherwise.
     **/
    bool isPlayerCheckmate(const playingSide & player);
};


#endif //CHESS_GAME_H
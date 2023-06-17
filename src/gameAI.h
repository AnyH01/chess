#ifndef CHESS_GAMEAI_H
#define CHESS_GAMEAI_H
#include <string>
#include "game.h"
#include "ai.h"

using namespace std;

/**
     * @brief A.
     * @param name B.
     * @return C.
     **/

/**
 * Class for game against computer.
**/
class GameAI{
public:
    /**
     * Constructor initialize all variables.
     **/
    GameAI();

    /**
     * @brief Method for game against computer.
     **/
    void startGame();

private:
    /**
     * @brief Includes path to the configuration file.
     **/
    string configPath;

    /**
     * @brief Instance of class Game.
     **/
    Game game;

    /**
     * @brief Depth of the search tree.
     **/
    uint treeDepth;

    /**
     * @brief Instance of class AI which represents the computer.
     **/
    AI ai;

    /**
     * @brief Says witch one of players is on the move.
     **/
    playingSide currPlayer;


    /**
     * @brief Method that shows a menu of ai level choices.
     **/
    void printAiMenu();

    /**
     * @brief Method that manage the option selection.
     * @return Returns the level of ai (tree depth).
     **/
    uint chooseLevelOfAI();

    /**
     * @brief Method that managing game against ai.
     **/
    void playGame();

    /**
     * @brief Method that makes an ai move.
     * @return Returns true if the game is over (computer wins).
     **/
    bool aiMove();
};

#endif //CHESS_GAMEAI_H

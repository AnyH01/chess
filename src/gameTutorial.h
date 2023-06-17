#ifndef CHESS_GAMETUTORIAL_H
#include <string>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include <cctype>
#include <chrono>
#include <ctime>
#include <sstream>
#include "game.h"
#define CHESS_GAMETUTORIAL_H

using namespace std;


/**
 * Class for game tutorial.
**/
class GameTutorial {
public:
    /**
     * @brief Method for geme tutorial.
     **/
    void startGame();

private:
    /**
     * @brief Code for resets color of text.
     **/
    const string ANSI_RESET = "\033[0m";

    /**
     * @brief Code for red color of text.
     **/
    const string ANSI_RED = "\033[31m";

    /**
     * @brief Instance of class Game.
     **/
    Game manager;
    
    /**
     * @brief Method that loads configuration file.
     * @param game
    **/
    bool loadGame(Game& game, const string& filePath);

    /**
     * @brief Method that displays tutorial main menu.
    **/
    void printTutorialMenu();
    
    
    /**
     * @brief Method that displays pieces move menu.
    **/
    void basicMoveMenu();

    /**
     * @brief Method that manages pieces moves.
    */
    void basicMoveTutorial();

    /**
     * @brief Method that creates tutorial for horse moves.
    **/
    void horseTutorial();

    /**
     * @brief Method that creates tutorial for bishop moves.
    **/
    void bishopTutorial();

    /**
     * @brief Method that creates tutorial for rook moves.
    **/
    void rookTutorial();

    /**
     * @brief Method that creates tutorial for queen moves.
    **/
    void queenTutorial();

    /**
     * @brief Method that displays check and checkmate menu.
    **/
    void checkMenu();

    /**
     * Method that manages check and checkmate.
    */
    void checkTutorial();
    
    /**
     * @brief Method that creates tutorial for check.
    **/
    void basicCheckTutorial();

    /**
     * @brief Method that creates tutorial for checkmate.
    **/
    void checkMateTutorial();
    
    /**
     * @brief Method that displays special moves menu.
    **/
    void specialMenu();

    /**
     * Method that manages special moves.
    */
    void specialMoveTutorial();

    /**
     * @brief Method that creates tutorial for promote pawn.
    **/
    void promotePawnTutorial();

    /**
     * @brief Method that creates tutorial for en Passant.
    **/
    void enPassantTutorial();

    /**
     * @brief Method that creates tutorial for castle.
    **/
    void canCastleTutuorial();

    /**
     * @brief Method that handles moves.
     * @param board Board with all pieces on it.
     * @return Return pair of positions from and to.
    **/
    pair<Pos,Pos> moveLoader(Board& board);

};

#endif //CHESS_GAMETUTORIAL_H
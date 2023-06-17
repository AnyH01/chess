#ifndef CHESS_GAME2P_H
#define CHESS_GAME2P_H
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include <chrono>
#include <ctime>
#include <sstream>
#include <string>
#include "game.h"
using namespace std;


/**
 * Class for game two players.
**/
class Game2P {
public:
    /**
     * @brief Constructor which sets game, configPath and currPlayer.
     **/
    Game2P();

    /**
     * @brief Method for geme two players.
     **/
    void startGame();

private:
    /**
     * @brief Instance of class Game.
     **/
    Game game;
    /**
     * @brief Includes path to the configuration file.
     **/
    string configPath;
    /**
     * @brief Says witch one of players is on the move.
     **/
    playingSide currPlayer;

    /**
     * @brief Method for playing game two players.
     **/
    void gamePlayers();
    /**
     * @brief Method for save current status of the board, if you want to.
     * @return Returns true if a player wants to save game, false otherwise.
     **/
    bool saveGame();
    /**
     * @brief Method loads game from the file.
     * @param fileName The name of the saved game file.
     **/
    bool loadGame(const string& fileName);
    /**
     * @brief Method to selects a save game file.
     **/
    bool choseGame();
    /**
     * @brief Method finds the current time.
     * @return Returns strig creates from current time.
     **/
    string getCurrentDate()const;
};

#endif //CHESS_GAME2P_H

#ifndef CHESS_GAMEMANAGER_H
#define CHESS_GAMEMANAGER_H
#include <string>
using namespace std;

/**
 * Main class for game managing.
 */
class gameManager {
public:
    /**
     * @brief Displays main menu and starts selected game.
     **/
    void mainMenu();
    /**
     * @brief Draw the main menu.
     **/
    void drawMenu();

private:
    /**
     * @brief Loads a number of option from user.
     * @return Returns number of selected option.
     **/
    int loadInput();
    const string ANSI_RESET = "\033[0m";
    const string ANSI_RED = "\033[31m";

};

#endif //CHESS_GAMEMANAGER_H

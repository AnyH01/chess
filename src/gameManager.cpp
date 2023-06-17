#include "iostream"
#include "gameManager.h"
#include "game2P.h"
#include "gameAI.h"
#include "gameTutorial.h"

void gameManager::drawMenu() {
    cout << "+------------------------------------------------+" << endl;
    for(int i = 2 ; i < 11; i++){
        if(i == 3)
            cout << "|            1.Hra pro dva hrace                 |" << endl;
        else if(i == 5)
            cout << "|            2.Hra proti AI                      |" << endl;
        else if(i == 7)
            cout << "|            3.Tutorial                          |" << endl;
        else if(i == 9)
            cout << "|            4.Konec hry                         |" << endl;
        else
            cout << "|                                                |" << endl;
    }
    cout << "+------------------------------------------------+" << endl;
}

int gameManager::loadInput(){
    string input;
    int number;
    cout << endl << "Vyberte svoji volbu: " << endl;
    getline(cin, input);

    istringstream iss(input);
    if (iss >> number && number <= 4 && number > 0) {
        return number;
    } else {
        system("clear");
        cout << ANSI_RED << "Nevalidní vstup zkuste to znovu" << ANSI_RESET<< endl;
        return -1;
    }
}

void gameManager::mainMenu() {
    system("clear");
    while (true){
        drawMenu();
        int option = loadInput();
        switch (option) {
            case 1:{
                Game2P game2p;
                game2p.startGame();
                break;
            }
            case 2:{
                GameAI gameAi;
                gameAi.startGame();
                break;
            }
            case 3:{
                GameTutorial tutorial;
                tutorial.startGame();
                break;
            } 
            case 4:
                return;
        }
        system("clear");
    }
}

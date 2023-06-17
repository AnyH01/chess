#include "gameAI.h"


GameAI::GameAI()
    : configPath("examples/configFiles/configAI/configAI.json")
    , game()
    , treeDepth(0)
    , ai(game.board, BLACK_PLAYER, chooseLevelOfAI())
    , currPlayer(WHITE_PLAYER){
    
}

void GameAI::startGame() {
    if (treeDepth == 4)
        return;

    if(!game.loadConfig(configPath)){
        system("clear");
        cout  << "Chyba v konfiguračním souboru " << endl;        
        return;
    }
    system("clear");
    game.board.print();
    playGame();
}

void GameAI::printAiMenu(){
    system("clear");
    cout << "Vitejte ve hre proti pocitaci" << endl;
    cout << "Vyberte si uroven:" << endl << endl;   
    cout << "1. zacatecnik" << endl;
    cout << "2. pokrocily" << endl;
    cout << "3. expert" << endl;
    cout << "4. zpatky do hlavniho menu" << endl;
}

uint GameAI::chooseLevelOfAI(){
    printAiMenu();
    int option = game.loadInput(4);
    treeDepth = uint(option);
    
    return treeDepth;
}

void GameAI::playGame(){
    while (true){
        if (currPlayer == WHITE_PLAYER && game.playerMove(currPlayer))
            break;
        if (currPlayer == BLACK_PLAYER && aiMove())
            break;
        
        (currPlayer == WHITE_PLAYER) ? currPlayer = BLACK_PLAYER : currPlayer = WHITE_PLAYER;
        system("clear");
        game.board.print();
    }

    (currPlayer == WHITE_PLAYER) ? cout << "VYHRAL HRAC!" << endl : cout << "VYHRAL POCITAC!" << endl;
}

bool GameAI::aiMove(){
    Pos from;
    Pos to;

    while (true){
        auto pos = ai.playNext();
        from.setPos(pos.first);
        to.setPos(pos.second);
        if (game.isValidMove(from, to, currPlayer) && !game.isPlayerCheck(game.board, from, to, currPlayer))
            break;
        cout << "pohyb ia neni validni" << endl;
    }

    game.deletePiece(game.board, from, to, currPlayer);

    //delete doubleMove flags from pawns expect the last one
    game.board.isPossibleEnPassant(to);

    //control, if king is not in check or checkmate
    playingSide oppositePlayer = (currPlayer == WHITE_PLAYER) ? BLACK_PLAYER : WHITE_PLAYER;
    if (game.isKingCheck(game.board, oppositePlayer)) {
        if (game.isPlayerCheckmate(oppositePlayer)) {
            cout << "Checkmate!" << endl;
            return true;
        } else {
            cout << "Check!" << endl;
            return false;
        }
    }

    return false;
}

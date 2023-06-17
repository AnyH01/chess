#include "gameTutorial.h"
using namespace std;


pair<Pos,Pos> GameTutorial::moveLoader(Board& board){
    pair<Pos, Pos> returnPos;    

    while (true){
        string input;
        getline(cin, input);

        istringstream iss(input);
        vector<string> words;
        string word;

        while (std::getline(iss, word, ' ')) {
            words.push_back(word);
        }

        if(words.size() == 2 
            && words[0].length() == 2 && isdigit(words[0][1]) && (words[0][0] >= 'a' &&  words[0][0] <= 'a' + board.size) && words[0][1] > '0' &&  words[0][1] <= ('0' + board.size) 
            && words[1].length() == 2 && isdigit(words[1][1]) && (words[1][0] >= 'a' &&  words[1][0] <= 'a' + board.size) && words[1][1] > '0' &&  words[1][1] <= ('0' + board.size)) {
                returnPos.first = Pos(words[0][1] - '0', words[0][0]);
                returnPos.second = Pos(words[1][1] - '0', words[1][0]);
                break;
            }
        system("clear");
        cout << ANSI_RED << "Nevalidni vstup zkuste to znovu" << ANSI_RESET<< endl;        
        board.print();
    }
    return returnPos;
}

void GameTutorial::printTutorialMenu(){
    cout << "Vitejte v tutorialu" << endl;
    cout << "Vyberte si co byste se radi naucili:" << endl << endl;   
    cout << "1. zakladni pohyby figurek" << endl;
    cout << "2. specialni pohyby" << endl;
    cout << "3. sach / sach mat" << endl;
    cout << "4. zpatky do hlavniho menu" << endl;
}


void GameTutorial::basicMoveMenu(){
    cout << "--Zakladní tahy--" << endl;
    cout << "Vyberte si co byste se radi naucili:" << endl << endl;   
    cout << "1. kun" << endl;
    cout << "2. strelec" << endl;
    cout << "3. vez" << endl;
    cout << "4. dama" << endl;
    cout << "5. zpet" << endl;
}

void GameTutorial::horseTutorial(){
    Game game;
    system("clear");
    if(!game.loadConfig("examples/configFiles/configTutorial/horseConfig.json")){
        cout << ANSI_RED << "v konfiguracnim souboru je chyba"  << ANSI_RESET<< endl;
        return;
    }

    while(true){
        cout << "Nasledujici ukazka nas nauci hrat s konem" << endl;
        cout << "Kun se pohybuje do tvaru L" << endl;
        cout << "neboli ve tvaru dva bloky jednim smerem a jeden do jine strany" << endl;
        cout << "najdete na nasledujici sachovnici pohyb bilym konem ktery ziska vyznamny material(ne pesec)" << endl;
        game.board.print();
        auto move = moveLoader(game.board);

        if(move.first == Pos(5, 'd') && move.second == Pos(7, 'e')){
            system("clear");
            cout << "Vyborny tah kralovna je tvoje" << endl;
            cout << "Zmackni enter pro pechod do menu tutorialu" << endl;
            game.board.board[move.first.XInBoard()][move.first.YInBoard()].reset();
            game.board.board[move.second.XInBoard()][move.second.YInBoard()].reset();
            game.board.board[move.second.XInBoard()][move.second.YInBoard()] = Horse(move.second, WHITE_PLAYER).add();
            game.board.print();
            string emptyLine;
            getline(cin,emptyLine);
            return;
        }
        system("clear");
        cout << ANSI_RED << "Toto ten spravny tah nebyl zkus to znovu!" << ANSI_RESET<< endl;
    }
}

void GameTutorial::bishopTutorial(){
    Game game;
    system("clear");

    if(!game.loadConfig("examples/configFiles/configTutorial/bishopConfig.json")){
        cout << ANSI_RED << "v konfiguracnim souboru je chyba"  << ANSI_RESET<< endl;
        return;
    }

    while(true){
        cout << "Nasledujici ukazka nas nauci hrat s strelce" << endl;
        cout << "Strelec se pohybuje po diagonale" << endl;
        cout << "najdete na nasledujici sachovnici pohyb cernym strlcem ktery ziska vyznamny material(ne pesce)" << endl;
        game.board.print();
        auto move = moveLoader(game.board);

        if(move.first == Pos(7, 'g') && move.second == Pos(4, 'd')){
            system("clear");
            cout << "Vyborny tah kralovna je tvoje" << endl;
            cout << "Zmackni enter pro pechod do menu tutorialu" << endl;
            game.board.board[move.first.XInBoard()][move.first.YInBoard()].reset();
            game.board.board[move.second.XInBoard()][move.second.YInBoard()].reset();
            game.board.board[move.second.XInBoard()][move.second.YInBoard()] = Bishop(move.second, BLACK_PLAYER).add();
            game.board.print();
            string emptyLine;
            getline(cin,emptyLine);
            return;
        }
        system("clear");
        cout << ANSI_RED << "Toto ten spravny tah nebyl zkus to znovu!" << ANSI_RESET<< endl;
    }
}

void GameTutorial::rookTutorial(){
    Game game;

    system("clear");
    if(!game.loadConfig("examples/configFiles/configTutorial/rookConfig.json")){
        cout << ANSI_RED << "v konfiguracnim souboru je chyba"  << ANSI_RESET<< endl;
        return;
    }

    while(true){
        cout << "Nasledujici ukazka nas nauci hrat s vez" << endl;
        cout << "Vez se pohybuje do vsech ctyr stran" << endl;
        cout << "najdete na nasledujici sachovnici pohyb bilou vezi, ktery ziska vyznamny material(ne pesce)" << endl;
        game.board.print();
        auto move = moveLoader(game.board);

        if(move.first == Pos(1, 'e') && move.second == Pos(4, 'e')){
            system("clear");
            cout << "Vyborny tah kun je tvuj" << endl;
            cout << "Zmackni enter pro pechod do menu tutorialu" << endl;
            game.board.board[move.first.XInBoard()][move.first.YInBoard()].reset();
            game.board.board[move.second.XInBoard()][move.second.YInBoard()].reset();
            game.board.board[move.second.XInBoard()][move.second.YInBoard()] = Rook(move.second, WHITE_PLAYER).add();
            game.board.print();
            string emptyLine;
            getline(cin,emptyLine);
            return;
        }
        system("clear");
        cout << ANSI_RED << "Toto ten spravny tah nebyl zkus to znovu!" << ANSI_RESET<< endl;
    }
}

void GameTutorial::queenTutorial(){
    system("clear");
    cout << "Nasledujici text by měl dostacujicne vysvetlit pohyb damy" << endl;
    cout << "dama spojuje pohyb veze a strelce takze muze do stran a po diagonale" << endl;
    cout << "najdete na nasledujici sachovnici pohyb cernou damou ktery ziska vyznamny material(ne pesce)" << endl;
    cout << "Zmackni enter pro pechod do menu tutorialu" << endl;
    string emptyLine;
    getline(cin,emptyLine);
}

void GameTutorial::basicMoveTutorial(){
    
    while(true){
        basicMoveMenu();
        int choice = manager.loadInput(5);
        if(choice < 6 && choice > 0){
            switch (choice){
                case 1:
                    horseTutorial();
                    break;
                case 2:
                    bishopTutorial();
                    break;
                case 3:
                    rookTutorial();
                    break;
                case 4:
                    queenTutorial();
                    break;
                case 5:
                    return;
                    break;
                default:
                    break;
            }
        }
        system("clear");
    }
}

void GameTutorial::specialMenu(){
    cout << "Vyberte si co byste se radi naucili:" << endl << endl;   
    cout << "1. Promotnout pesaka" << endl;
    cout << "2. Brani mimochodem" << endl;
    cout << "3. Rosada" << endl;
    cout << "4. Zpet" << endl;
}

void GameTutorial::promotePawnTutorial(){
    Game game;
    if(!game.loadConfig("examples/configFiles/configTutorial/promotePawnConfig.json")){
        cout << ANSI_RED << "v konfiguracnim souboru je chyba"  << ANSI_RESET<< endl;
        return;
    }
    system("clear");

    while(true){
        cout << "Nasledujici ukazka nas nauci promotnout pesaka" << endl;
        cout << "kdyz dojde pesak na konec sachovnice tak ma na vyber na jakou figurku promotne" << endl;
        cout << "dojdete pesakem na konec sachovnice" << endl;
        game.board.print();
        auto move = moveLoader(game.board);

        if(move.first == Pos(2,'d') && move.second == Pos(1, 'd')){
            game.deletePiece(game.board,move.first, move.second, BLACK_PLAYER);
            game.pawnTransformation(move.second, BLACK_PLAYER);
            system("clear");
            cout << "Pesak byl promotnut" << endl;
            cout << "Zmackni enter pro pechod do menu tutorialu" << endl;
            game.board.print();
            string emptyLine;
            getline(cin,emptyLine);
            return;
        }
        system("clear");
        cout << ANSI_RED << "Toto ten spravny tah nebyl zkus to znovu!" << ANSI_RESET<< endl;
    }
}

bool GameTutorial::loadGame(Game& game, const string& filePath){
    ifstream ifs(filePath);
    if (!ifs.is_open()){
        cout << "Konfiguracni soubor neexistuje." << endl;
        return false;
    }
    json js;
    try{
        js = json::parse(ifs);

    } catch (const json::parse_error& e) {
        return false;
    }
    
    if(!js.contains("size") || !js.contains("whitePieces") || !js.contains("blackPieces"))
        return false;
    int size = js["size"];
    
    game.board.setSize(size);
    if(!game.configSavedBoard(js, WHITE_PLAYER, "whitePieces") || !game.configSavedBoard(js, BLACK_PLAYER, "blackPieces")){
        return false;
    }
    return true;
}

void GameTutorial::enPassantTutorial(){
    system("clear");
    while(true){
        Game game;
        if(!loadGame(game, "examples/configFiles/configTutorial/enPassantConfig.json")){
            cout << ANSI_RED << "v konfiguracnim souboru je chyba"  << ANSI_RESET<< endl;
            return;
        }   
        cout << "Nasledujici ukazka nas nauci brani mimochodem" << endl;
        cout << "k tomu dojde kdyz souperici pesak se posune o dve dopredu, pro nas to je ale jako by se \"posunul o jednu\"" << endl;
        cout << "udelejte s pescem na b5 mrani mimochodem" << endl;
        game.board.print();
        auto move = moveLoader(game.board);
        bool tmp = false;
        if(game.board.board[move.first.XInBoard()][move.first.YInBoard()].get()->canMove(Pos(move.second.getX(), move.second.getY()), game.board, tmp) && move.second == Pos(6,'a')){
            game.deletePiece(game.board,move.first, move.second, BLACK_PLAYER);
            game.board.board[move.second.XInBoard()-1][move.second.YInBoard()].reset();
            system("clear");
            cout << "Uspesne jsi zahral brani mimochodem" << endl;
            cout << "Zmackni enter pro pechod do menu tutorialu" << endl;
            game.board.print();
            string emptyLine;
            getline(cin,emptyLine);
            return;
        }
        system("clear");
        cout << ANSI_RED << "Toto ten spravny tah nebyl zkus to znovu!" << ANSI_RESET<< endl;
    }
}

void GameTutorial::canCastleTutuorial(){
    system("clear");
    while(true){
        Game game;
        if(!loadGame(game, "examples/configFiles/configTutorial/castleConfig.json")){
            cout << ANSI_RED << "v konfiguracnim souboru je chyba"  << ANSI_RESET<< endl;
            return;
        }

        cout << "Nasledujici ukazka nas nauci rosadu" << endl;
        cout << "to znamena ze se kral posune o dve na jednu stranu a vedle nej se postavi vez" << endl;
        cout << "podminkou je ze zadne pole nesmi byt sachovane" << endl;
        cout << "udelejte rosadu s bilym kralem" << endl;
        game.board.print();
        auto move = moveLoader(game.board);
        bool tmp = false;
        if(game.board.board[move.first.XInBoard()][move.first.YInBoard()].get()->canMove(Pos(move.second.getX(), move.second.getY()), game.board, tmp) 
        && game.board.board[move.first.XInBoard()][move.first.YInBoard()].get()->isKing()
        && move.second == Pos(1,'g')){
            game.deletePiece(game.board,move.first, move.second, WHITE_PLAYER);
            system("clear");
            cout << "uspesna rosada :)" << endl;
            cout << "Zmackni enter pro pechod do menu tutorialu" << endl;
            game.board.print();
            string emptyLine;
            getline(cin,emptyLine);
            return;
        }
        system("clear");
        cout << ANSI_RED << "Toto ten spravny tah nebyl zkus to znovu!" << ANSI_RESET<< endl;
    }
}

void GameTutorial::specialMoveTutorial(){
    while(true){
        specialMenu();
        int choice = manager.loadInput(4);
        if(choice < 5 && choice > 0){
            switch (choice){
                case 1:
                    promotePawnTutorial();
                    break;
                case 2:
                    enPassantTutorial();
                    break;
                case 3:
                    canCastleTutuorial();
                    break;
                case 4: 
                    return;
                    break;
            }
        }
        system("clear");
    }
}

void GameTutorial::checkMenu(){
    cout << "Vyberte si co byste se radi naucili:" << endl << endl;   
    cout << "1. Zakladni sach" << endl;
    cout << "2. Sach mat" << endl;
    cout << "3. Zpet" << endl;
}

void GameTutorial::checkMateTutorial(){
    cout << "Nasledujici ukazka nas nauci jak vyhrat hru" << endl;
    cout << "To se stane pokud hrac nema jak blokovat utok nebo se mu vyhnout" << endl;
    cout << "Vyhraj v nasledujici ukazce hru!!!" << endl;
    while(true){
        Game game;
        if(!game.loadConfig("examples/configFiles/configTutorial/checkMate.json")){
            cout << ANSI_RED << "v konfiguracnim souboru je chyba"  << ANSI_RESET<< endl;
            return;
        }   
        game.board.print();
        auto move = moveLoader(game.board);
        game.deletePiece(game.board, move.first, move.second, BLACK_PLAYER);
        if(game.isPlayerCheckmate(BLACK_PLAYER)){
            system("clear");
            cout << "SACH MAT" << endl;
            cout << "Zmackni enter pro pechod do menu tutorialu" << endl;
            game.board.print();
            string emptyLine;
            getline(cin,emptyLine);
            return;
        }
        system("clear");
        cout << ANSI_RED << "Toto ten spravny tah nebyl zkus to znovu!" << ANSI_RESET<< endl;
    }
}
void GameTutorial::basicCheckTutorial(){
    cout << "Nasledujici ukazka nas nauci jak sachovat(ohrozit krale)" << endl;
    cout << "To se stane pokud nejaka nase figurka utoci na soupericiho krale" << endl;
    cout << "udelej sach v nasledujici ukazce!!!" << endl;
    
    while(true){
        Game game;
        if(!game.loadConfig("examples/configFiles/configTutorial/check.json")){
            cout << ANSI_RED << "v konfiguracnim souboru je chyba"  << ANSI_RESET<< endl;
            return;
        }
        game.board.print();
        auto move = moveLoader(game.board);
        game.deletePiece(game.board, move.first, move.second, BLACK_PLAYER);
        if(game.isKingCheck(game.board, BLACK_PLAYER)){
            system("clear");
            cout << "ŠACH" << endl;
            cout << "Zmackni enter pro pechod do menu tutorialu" << endl;
            game.board.print();
            string emptyLine;
            getline(cin,emptyLine);
            return;
        }
        system("clear");
        cout << ANSI_RED << "Toto ten spravny tah nebyl zkus to znovu!" << ANSI_RESET<< endl;
    }
}

void GameTutorial::checkTutorial(){
   while(true){
        checkMenu();
        int choice = manager.loadInput(3);
        if(choice < 4 && choice > 0){
            system("clear");
            switch (choice){
                case 1:
                    basicCheckTutorial();
                    break;
                case 2:
                    checkMateTutorial();
                    break;
                case 3:
                    return;
                    break;
            }
        }
        system("clear");
    }
}

void GameTutorial::startGame() {
    while (true){
        int choice;
        bool error = false;
        while (true){
            system("clear");
            if(error)
                cout << ANSI_RED << "Nevalidní vstup zkuste to znovu" << ANSI_RESET << endl;
            printTutorialMenu();
            choice = manager.loadInput(4);
            if(choice != -1)
                break;
            error = true;
        }
        system("clear");
        switch(choice){
            case 1: 
                basicMoveTutorial();
                break;
            case 2: 
                specialMoveTutorial();
                break;
            case 3: 
                checkTutorial();
                break;
            case 4:
                return; 
        }
    }
}

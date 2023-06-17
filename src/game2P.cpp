#include "game2P.h"


Game2P::Game2P()
    : game()
    , configPath("examples/configFiles/config2P/config2P.json")
    , currPlayer(WHITE_PLAYER)
    {}

string Game2P::getCurrentDate() const{
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    tm localTime = *localtime(&time);

    ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d-%H-%M-%S");

    return oss.str();
}

bool Game2P::saveGame(){
    char res;
    cout << "chcete uložit hru? A/N" << endl;
    cin >> res;

    if(res != 'A')
        return false;

    json blackPieces;
    json whitePieces;
    for(auto& i : game.board.board){
        for (auto& j : i) {
            if(j != nullptr && j->side == BLACK_PLAYER){
                json piece;
                j->to_json(piece);
                blackPieces.push_back(piece);
            }
            else if(j != nullptr && j->side == WHITE_PLAYER){
                json piece;
                j->to_json(piece);
                whitePieces.push_back(piece);
            }
        }
    }
    json outputJson = {{"size" , game.board.size}, {"turn", currPlayer}};
    outputJson["whitePieces"] = whitePieces;
    outputJson["blackPieces"] = blackPieces;
    cout << outputJson << endl;
    ofstream o("examples/savedGames/" + getCurrentDate() + ".json");
    o << setw(4) << outputJson << endl;
    return true;
}

bool Game2P::loadGame(const string& fileName){
    cout << fileName << endl;
    ifstream ifs(fileName);
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
    if(!js.contains("size") || !js.contains("turn") || !js.contains("whitePieces") || !js.contains("blackPieces"))
        return false;
    int size = js["size"];
    currPlayer = js["turn"];
    game.board.setSize(size);
    cout << fileName << endl;
    if(!game.configSavedBoard(js, WHITE_PLAYER, "whitePieces") || !game.configSavedBoard(js, BLACK_PLAYER, "blackPieces"))
        return false;
    return true;
}

bool Game2P::choseGame(){
    filesystem::path folderpath = "examples/savedGames";
    int fileNumber;
    vector<string> fileNames;
    while(true){
        int i = 1;

        cout << "vyberte číslo souboru co si přejete načíst" << endl;
        if(filesystem::exists(folderpath) && filesystem::is_directory(folderpath)){
            for(const auto& entry : filesystem::directory_iterator(folderpath)){
                if(filesystem::is_regular_file(entry.path())){
                    fileNames.push_back(entry.path().filename());
                    cout << i << ": " << entry.path().filename() << endl;
                }
                i++;
            }
        }
    
        fileNumber = game.loadInput(i-1);
        if(fileNumber != -1)
                break;
        fileNames.clear();
        system("clear");
    }
    if(!loadGame(folderpath += "/" + fileNames[fileNumber - 1]))
        return false;
    return true;
}

void Game2P::startGame() {
    system("clear");
    int input;
    while (true){
        cout << "co si prejete udelat" << endl;
        cout << "1. zacit novou hru" << endl;
        cout << "2. nacist ulozenou hru" << endl;
        cout << "3. konec" << endl;
        input = game.loadInput(3);
        system("clear");
        switch (input) {
            case 1:
                if(game.loadConfig(configPath)){
                    game.board.print();
                    gamePlayers();
                }
                else 
                    cout << "v konfiguracnim souboru je chyba" << endl;

                break;
            case 2:
                if(choseGame()){
                    system("clear");
                    game.board.print();
                    gamePlayers();
                }
                else 
                    cout << "v konfiguracnim souboru je chyba" << endl;
                break;
            case 3:
                return;
        }
    }

}

void Game2P::gamePlayers() {
    while (true){
        if (game.playerMove(currPlayer))
            break;

        (currPlayer == WHITE_PLAYER) ? currPlayer = BLACK_PLAYER : currPlayer = WHITE_PLAYER;
        game.board.print();
        if(saveGame())
            return;
        system("clear");
    }
    cout << "VYHRAL ";
    (currPlayer == WHITE_PLAYER) ? cout << "BILY HRAC!" << endl : cout << "CERNY HRAC!" << endl;
    cout << "Zmacknete enter pro prechod do menu hry dvou hracu." << endl;
    string emptyLine;
    getline(cin,emptyLine);
    system("clear");
}


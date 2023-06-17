#include "game.h"

Game::Game()
    : board()
    , posWhiteKing(1, 'd')
    , posBlackKing(8, 'e')
    {}

int Game::loadInput(int maxInput){
    string input;
    int number;
    cout << endl << "Vyberte svoji volbu: " << endl;
    getline(cin, input);

    istringstream iss(input);
    if (iss >> number && number <= maxInput && number > 0) {
        return number;
    } else {
        system("clear");
        cout << ANSI_RED << "Nevalidní vstup zkuste to znovu" << ANSI_RESET<< endl;
        return -1;
    }
}

bool Game::loadConfig(const string &configPath){
    ifstream ifs(configPath);
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

    string white = "white_piece";
    string black = "black_piece";
    if(!js.contains("board") || !js.at("board").contains("size") 
    || !js.contains(white) || !js.contains(black))
        return false;
    string size = js.at("board").at("size");
    board.setSize(stoi(size));
    
    if(!configBoard(js, WHITE_PLAYER, white) || !configBoard(js, BLACK_PLAYER, black))
        return false;
    
    return true;
}

bool Game::configBoard(const json &js, const playingSide & side, const string & player) {
    for (auto x : js.at(player)) {
        if(!x.contains("posX") || !x.contains("posY") || !x.contains("type"))
            return false;
        string posX = x.at("posY");
        string posY = x.at("posX");

        if(x.at("type") == "bishop"){
            Bishop piece(Pos(stoi(posX), posY[0]), side);
            board.addPiece(piece);
        }else if(x.at("type") == "horse"){
            Horse piece(Pos(stoi(posX), posY[0]), side);
            board.addPiece(piece);
        }else if(x.at("type") == "king"){
            King piece(Pos(stoi(posX), posY[0]), side);
            board.addPiece(piece);
            (side == WHITE_PLAYER) ? posWhiteKing.setPos(stoi(posX), posY[0]) : posBlackKing.setPos(stoi(posX), posY[0]);
        }else if(x.at("type") == "pawn"){
            Pawn piece(Pos(stoi(posX), posY[0]), side);
            board.addPiece(piece);
        }else if(x.at("type") == "queen"){
            Queen piece(Pos(stoi(posX), posY[0]), side);
            board.addPiece(piece);
        }else if(x.at("type") == "rook"){
            Rook piece(Pos(stoi(posX), posY[0]), side);
            board.addPiece(piece);
        }
    }
    return true;
}

bool Game::configSavedBoard(const json &js, playingSide side, const string& player) {
    for (auto x : js[player]) {
        if(!x.contains("posX") || !x.contains("posY") || !x.contains("type"))
            return false;
        int posX = x["posX"];
        int posY = x["posY"];
        if(x["type"] == "bishop"){
            Bishop piece(Pos(posX, posY), side);
            board.addPiece(piece);
        }else if(x["type"] == "horse"){
            Horse piece(Pos(posX, posY), side);
            board.addPiece(piece);
        }else if(x["type"] == "king"){
            if(!x.contains("castle"))
                return false;
            King piece(Pos(posX, posY), side,x["castle"]);
            board.addPiece(piece);
            (side == WHITE_PLAYER) ? posWhiteKing.setPos(posX, posY) : posBlackKing.setPos(posX, posY);
        }else if(x["type"] == "pawn"){
            if(!x.contains("isNotMove") || !x.contains("doubleMove"))
                return false;
            Pawn piece(Pos(posX, posY), side, "isNotMove", "doubleMove");
            board.addPiece(piece);
        }else if(x["type"] == "queen"){
            Queen piece(Pos(posX, posY), side);
            board.addPiece(piece);
        }else if(x["type"] == "rook"){
            if(!x.contains("canCastle"))
                return false;
            Rook piece(Pos(posX, posY), side, "canCastle");
            board.addPiece(piece);
        }
    }
    return true;
}

bool Game::playerMove(const playingSide & player) {
    int fromX;
    char fromY;
    int toX;
    char toY;
    while (true){
        (player == WHITE_PLAYER) ? cout << "Je na tahu bily hrac." << endl : cout << "Je na tahu cerny hrac." << endl;
        cout << "Zadejte odkud a kam chcete tahnout figurkou pr:\"a2 a3\"." << endl;
        bool flag = false;
        string input;
        getline(cin, input);
        istringstream iss(input);
        vector<string> words;
        string word;

        while (std::getline(iss, word, ' ')) {
            words.push_back(word);
        }

        if(words.size() == 2 && words[0].length() == 2 && words[1].length() == 2){
            fromY = words[0][0];
            fromX = words[0][1] - '0';

            toY = words[1][0];
            toX = words[1][1] - '0';
            flag = true;
        }
        if (flag && isValidMove(Pos(fromX,fromY), Pos(toX, toY), player)&& !isPlayerCheck(board, Pos(fromX,fromY), Pos(toX, toY), player))
                break;
        system("clear");
        cout << "Nespravny vstup. Zadejte znovu." << endl;
        board.print();
    }

    deletePiece(board, Pos(fromX,fromY), Pos(toX, toY), player);

    //delete doubleMove flags from pawns expect the last one
    board.isPossibleEnPassant(Pos(toX, toY));

    //control, if king is not in check or checkmate
    playingSide oppositePlayer = (player == WHITE_PLAYER) ? BLACK_PLAYER : WHITE_PLAYER;
    if (isKingCheck(board, oppositePlayer)) {
        if (isPlayerCheckmate(oppositePlayer)) {
            cout << "Checkmate!" << endl;
            return true;
        } else {
            cout << "Check!" << endl;
            return false;
        }
    }

    return false;
}

bool Game::isValidMove(const Pos & from, const Pos & to,const playingSide & player) {
    bool isPawnInEnd = false;
    if (!board.isPosOnBoard(from)
      || !board.isPosOnBoard(to)
      || board.board[from.XInBoard()][from.YInBoard()] == nullptr
      || board.board[from.XInBoard()][from.YInBoard()]->side != player
      || (board.board[to.XInBoard()][to.YInBoard()] != nullptr && board.board[to.XInBoard()][to.YInBoard()]->side == player)
      || !board.board[from.XInBoard()][from.YInBoard()]->canMove(to, board, isPawnInEnd))
        return false;
    if (isPawnInEnd)
        pawnTransformation(from, player);
    return true;
}

void Game::deletePiece(Board &board, const Pos & from, const Pos & to, const playingSide & player) {
    if (board.board[to.XInBoard()][to.YInBoard()] != nullptr)
        board.board[to.XInBoard()][to.YInBoard()].reset();

    if (board.board[from.XInBoard()][from.YInBoard()]->isKing())
        (player == WHITE_PLAYER) ? posWhiteKing.setPos(to.getX(), to.getY()) : posBlackKing.setPos(to.getX(), to.getY());
    
    board.board[from.XInBoard()][from.YInBoard()]->pos.setPos(to.getX(), to.getY());
    board.addPiece(*board.board[from.XInBoard()][from.YInBoard()]);
    board.board[from.XInBoard()][from.YInBoard()].reset(); 
}

void Game::pawnTransformation(const Pos & pos, const playingSide & player) {
    char cPiece;
    cout << "Zadejte symbol figurky, na kterou se ma pesec promenit (rook - r, horse - h, bishop - b, queen - q)." << endl;
    while (true){
        string input;
        getline(cin, input);

        istringstream iss(input);
        vector<string> words;
        string word;

        while (std::getline(iss, word, ' ')) {
            words.push_back(word);
        }
        cPiece = words[0][0];
        if(words.size() == 1 && words[0].length() == 1){
            board.board[pos.XInBoard()][pos.YInBoard()] = nullptr;
            switch (cPiece) {
                case 'r': board.addPiece(Rook(pos, player)); return;
                    break;
                case 'h': board.addPiece(Horse(pos, player)); return;
                    break;
                case 'b': board.addPiece(Bishop(pos, player)); return;
                    break;
                case 'q': board.addPiece(Queen(pos, player)); return;
                    break;
            }

      }
    }       
    system("clear");
    cout << "Nevalidni vstup zkuste to znovu" << endl;        
    board.print();
}

bool Game::isKingCheck(Board &board, const playingSide & player) {
    bool b = false;
    Pos kingPos = (player == WHITE_PLAYER) ? posWhiteKing : posBlackKing;

    for (int x = 0; x < board.size; x++) {
        for (int y = 0; y < board.size; y++) {
            if (board.board[x][y] != nullptr && board.board[x][y]->side != player && board.board[x][y]->canMove(kingPos, board, b)){
                return true;
            }
        }
    }
    return false;
}

bool Game::isPlayerCheck(Board& board, const Pos & from, const Pos & to, const playingSide & player){
    Board myBoard = board;
    deletePiece(myBoard, from, to, player);
    return isKingCheck(myBoard, player);
}

bool Game::isPlayerCheckmate(const playingSide& player) {
    for (int fromX = 0; fromX < board.size; fromX++) {
        for (int fromY = 0; fromY < board.size; fromY++) {
            if (board.board[fromX][fromY] != nullptr && board.board[fromX][fromY]->side == player) {
                for (int toX = 0; toX < board.size; toX++) {
                    for (int toY = 0; toY < board.size; toY++) {
                        Pos from(fromX+1, fromY+97);
                        Pos to(toX+1, toY+97);
                        bool king = board.board[fromX][fromY]->isKing();
                        if (king)
                            (player == WHITE_PLAYER) ? posWhiteKing = to : posBlackKing = to;
                            
                        if (isValidMove(from, to, player) && !isPlayerCheck(board, from, to, player)) {
                            if (king)
                                (player == WHITE_PLAYER) ? posWhiteKing = from : posBlackKing = from;
                            return false;
                        }
                        if (king)
                            (player == WHITE_PLAYER) ? posWhiteKing = from : posBlackKing = from;
                    }
                }
            }
        }
    }
    return true;
}
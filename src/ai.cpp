#include "ai.h"

AI::AI(const Board& board, playingSide side, uint level)
    : mainBoard(board), mainSide(side), treeDepth(level) {}

AI::Move::Move() {}

AI::Move::Move(const Pos& from, const Pos& to) : from(from), to(to) {}

AI::Record::Record(shared_ptr<Piece> first, Pos firstPos, shared_ptr<Piece> second, Pos secondPos)
    : first(first), firstPos(firstPos), second(second), secondPos(secondPos) {}

pair<Pos, Pos> AI::playNext() {
    board = mainBoard;
    counter = 0;

    if (treeDepth <= 0) {
        vector<Move> moves = getAllPossibleMoves(mainSide);
        Move bestMove = moves[rand() % moves.size()];

        return make_pair(bestMove.from, bestMove.to);
    } else {
        minimax(treeDepth, mainSide);
        cout << "From: [" << lastBestMove.from.x << ", " << lastBestMove.from.y << "]  to: [" <<  lastBestMove.to.x << ", "<<  lastBestMove.to.y << "]" << endl;
        return make_pair(lastBestMove.from, lastBestMove.to);
    }
}

void AI::setLevel(uint level) {
    treeDepth = level;
}

int AI::minimax(int depth, playingSide side) {
    if (depth == 0) {
        return getBoardWeight(side,false);
    }

    counter++;
    
    vector<Move> moves = getAllPossibleMoves(side);

    int bestWeight = INT_MIN;
    Move bestMove;

    for (auto move : moves) {
        if (!makeMove(move)) continue;

        int weight = -minimax(depth-1, getOppositeSide(side));

        unmakeMove();

        if (weight > bestWeight) {
            bestWeight = weight;
            bestMove = move;
        }
    }

    lastBestMove = bestMove;
    return bestWeight;
}

bool AI::makeMove(Move move) {
    if (!board.isPosOnBoard(move.from) || !board.isPosOnBoard(move.to)) {
        return false;
    }
    if (board.board[move.from.XInBoard()][move.from.YInBoard()] == nullptr) {
        return false;
    }

    history.push({
        (board.board[move.from.XInBoard()][move.from.YInBoard()] != nullptr) ? board.board[move.from.XInBoard()][move.from.YInBoard()]->add() : nullptr, 
        move.from,
        (board.board[move.to.XInBoard()][move.to.YInBoard()] != nullptr) ? board.board[move.to.XInBoard()][move.to.YInBoard()]->add() : nullptr,
        move.to
    });

    board.board[move.from.XInBoard()][move.from.YInBoard()]->pos.setPos(move.to.getX(), move.to.getY());
    board.addPiece(*board.board[move.from.XInBoard()][move.from.YInBoard()]);
    board.board[move.from.XInBoard()][move.from.YInBoard()] = nullptr;

    return true;
}

bool AI::unmakeMove() {
    if (history.empty()) {
        return false;
    }

    auto record = history.top();
    history.pop();

    board.board[record.firstPos.XInBoard()][record.firstPos.YInBoard()] = record.first;
    board.board[record.secondPos.XInBoard()][record.secondPos.YInBoard()] = record.second;

    return true;
}

vector<AI::Move> AI::getAllPossibleMoves(playingSide side) {
    vector<AI::Move> moves;

    auto pieces = getPlayingSidePieces(board, side);
    for (auto piece : pieces) {

        for (int x = 0; x < board.size; x++) {
            for (int y = 0; y < board.size; y++) {
                Pos pos(x + 1, y + 97); 

                if (board.board[pos.XInBoard()][pos.YInBoard()] == nullptr
                        || board.board[pos.XInBoard()][pos.YInBoard()]->side != side) {

                    bool _;
                    if (piece->canMove(pos, board, _)) {
                        moves.emplace_back(piece->pos, pos);
                    }
                }
            }
        }
    }

    return moves;
}

int AI::getBoardWeight(playingSide side, bool print) const {
    int boardWeight = 0;
    
    auto pieces = getAllPieces(board);
    for (auto piece : pieces) {

        auto pieceWeightIt = pieceWeights.find(piece->pieceName());
        if (pieceWeightIt == pieceWeights.end())
            continue;

        int weight = pieceWeightIt->second.weight;

        Pos pos(piece->pos.XInBoard(), piece->pos.YInBoard());

        if (piece->side == WHITE_PLAYER) {
            weight += pieceWeightIt->second.positionWeight[pos.x][pos.y];
        } else {
            weight += pieceWeightIt->second.positionWeight[board.size - (pos.x+1)][board.size - (pos.y+1)];
        }  

        if (print) {
            cout << "Piece: " << piece->pieceName() << "Side: " << piece->side << ", Pos: (" << piece->pos.x << ", " << piece->pos.y << "), " 
                << "Weight: " << weight << endl; 
        }

        if (piece->side == side) {
            boardWeight += weight;
        } else {
            boardWeight -= weight;
        }
    } 

    if (print) {
        cout << " TOTAL: " << boardWeight << endl;
    }

    return boardWeight;
}

vector<shared_ptr<Piece>> AI::getAllPieces(const Board& board) const {
    vector<shared_ptr<Piece>> pieces;

    for (int x = 0; x < board.size; x++) {
        for (int y = 0; y < board.size; y++) {
            auto piece = board.board[x][y];
            if (piece != nullptr) {
                pieces.push_back(piece);
            }
        }
    }

    return pieces;
}

vector<shared_ptr<Piece>> AI::getPlayingSidePieces(const Board& board, playingSide side) const {
     vector<shared_ptr<Piece>> pieces;

    for (int x = 0; x < board.size; x++) {
        for (int y = 0; y < board.size; y++) {
            auto piece = board.board[x][y];
            if (piece != nullptr && piece->side == side) {
                pieces.push_back(piece);
            }
        }
    } 

    return pieces;
}

playingSide AI::getOppositeSide(playingSide side)
{
    if (side == WHITE_PLAYER)
        return BLACK_PLAYER;
    return WHITE_PLAYER;
}

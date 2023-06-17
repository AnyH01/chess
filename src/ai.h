#ifndef CHESS_AI_H
#define CHESS_AI_H
#include <unordered_map>
#include <memory>
//#include <iostream>
#include <vector>
#include <stack>
#include "pos.h"
#include "board.h" 
#include "piece.h" 

using namespace std;

/**
 * Class for game against the computer.
**/
class AI {
public:
    /**
     * @brief Constructor that sets all variables.
    **/
    AI(const Board& board, playingSide side, uint level = 0);

    /**
     * @brief Method that manages ai move.
     * @return Returns pair of positions from and to choosen piece move.
    **/
    pair<Pos, Pos> playNext();

    /**
     * @brief Method that sets level of ai.
     * @param level Level of selected ai.
    **/
    void setLevel(uint level);

private:
    /**
     * Struct with weight of piece.
    **/
    struct Weight {
        /**
        * @brief Primary weight of the piece.
        **/
        int weight;

        /**
        * @brief Weight depending on positis in board.
        **/
        vector<vector<int>> positionWeight;
    };

    /**
     * Struct represents move defined py positions from and to.
    **/
    struct Move {
        /**
        * @brief Position to be move from.
        **/
        Pos from;

        /**
        * @brief Position to be move to.
        **/
        Pos to;

        /**
         * @brief Default constructor.
        **/
        Move();

        /**
         * @brief Constructor that sest positions.
         * @param from Position to be move from.
         * @param to Position to be move to.
        **/
        Move(const Pos& from, const Pos& to);
    };

    /**
     * Struct represents record of the piece before and after move.
    **/
    struct Record {
        /**
         * @brief Piece before move.
        **/
        shared_ptr<Piece> first;

        /**
         * @brief Position of the piece before move.
        **/
        Pos firstPos;

        /**
         * @brief Piece after move.
        **/
        shared_ptr<Piece> second;

        /**
         * @brief Position of the piece after move.
        **/
        Pos secondPos;

        /**
         * @brief Constructor that inicialize variables in record.
        **/
        Record(shared_ptr<Piece> first, Pos firstPos, shared_ptr<Piece> second, Pos secondPos);
    };
    

    /**
     * Map of pieces with specific weights.
     * The key is name of the piece.
    */
    const unordered_map<string, Weight> pieceWeights = 
        {
            {"pawn", 
                {
                    100,
                    {
                        { 0,  0,  0,  0,  0,  0,  0,  0},
                        { 5, 10, 10,-20,-20, 10, 10,  5},
                        { 5, -5,-10,  0,  0,-10, -5,  5},
                        { 0,  0,  0, 20, 20,  0,  0,  0},
                        { 5,  5, 10, 25, 25, 10,  5,  5},
                        {10, 10, 20, 30, 30, 20, 10, 10},
                        {50, 50, 50, 50, 50, 50, 50, 50},
                        { 0,  0,  0,  0,  0,  0,  0,  0},
                    }
                }
            },
            {"horse",
                {
                    320,
                    {
                        {-50,-40,-30,-30,-30,-30,-40,-50},
                        {-40,-20,  0,  5,  5,  0,-20,-40},
                        {-30,  5, 10, 15, 15, 10,  5,-30},
                        {-30,  0, 15, 20, 20, 15,  0,-30},
                        {-30,  5, 15, 20, 20, 15,  5,-30},
                        {-30,  0, 10, 15, 15, 10,  0,-30},
                        {-40,-20,  0,  0,  0,  0,-20,-40},
                        {-50,-40,-30,-30,-30,-30,-40,-50},
                    }
                }
            },
            {"bishop",
                {
                    330,
                    {
                        {-20,-10,-10,-10,-10,-10,-10,-20},
                        {-10,  5,  0,  0,  0,  0,  5,-10},
                        {-10, 10, 10, 10, 10, 10, 10,-10},
                        {-10,  0, 10, 10, 10, 10,  0,-10},
                        {-10,  5,  5, 10, 10,  5,  5,-10},
                        {-10,  0,  5, 10, 10,  5,  0,-10},
                        {-10,  0,  0,  0,  0,  0,  0,-10},
                        {-20,-10,-10,-10,-10,-10,-10,-20},
                    }
                }
            },
            {"rook",
                {
                    500,
                    {
                        { 0,  0,  0,  5,  5,  0,  0,  0},
                        {-5,  0,  0,  0,  0,  0,  0, -5},
                        {-5,  0,  0,  0,  0,  0,  0, -5},
                        {-5,  0,  0,  0,  0,  0,  0, -5},
                        {-5,  0,  0,  0,  0,  0,  0, -5},
                        {-5,  0,  0,  0,  0,  0,  0, -5},
                        { 5, 10, 10, 10, 10, 10, 10,  5},
                        { 0,  0,  0,  0,  0,  0,  0,  0},
                    }
                }
            },
            {"queen",
                {
                    900,
                    {
                        {-20,-10,-10, -5, -5,-10,-10,-20},
                        {-10,  0,  5,  0,  0,  0,  0,-10},
                        {-10,  5,  5,  5,  5,  5,  0,-10},
                        {  0,  0,  5,  5,  5,  5,  0, -5},
                        { -5,  0,  5,  5,  5,  5,  0, -5},
                        {-10,  0,  5,  5,  5,  5,  0,-10},
                        {-10,  0,  0,  0,  0,  0,  0,-10},
                        {-20,-10,-10, -5, -5,-10,-10,-20},
                    }
                }
            },
            {"king",
                {
                    20000,
                    {
                        { 20, 30, 10,  0,  0, 10, 30, 20},
                        { 20, 20,  0,  0,  0,  0, 20, 20},
                        {-10,-20,-20,-20,-20,-20,-20,-10},
                        {-20,-30,-30,-40,-40,-30,-30,-20},
                        {-30,-40,-40,-50,-50,-40,-40,-30},
                        {-30,-40,-40,-50,-50,-40,-40,-30},
                        {-30,-40,-40,-50,-50,-40,-40,-30},
                        {-30,-40,-40,-50,-50,-40,-40,-30},
                    }
                }
            }
        };

    /**
    * @brief Board from playAI with all pieces on it.
    **/
    const Board& mainBoard;

    /**
    * @brief Playing side of the ai.
    **/
    playingSide mainSide;

    /**
     * @brief Depth of the search tree.
    **/
    uint treeDepth;

    /**
    * @brief Copy of the mainBoard.
    **/
    Board board;

    /**
    * @brief Counts number of possible moves.
    **/
    size_t counter = 0;

    /**
    * @brief Stack with redords history for backtracking moves.
    **/
    stack<Record> history;

    /**
    * @brief Best move from one round.
    **/
    Move lastBestMove;

    /**
     * @brief Method that finds the best board evaluete.
     * @param depth Depth of the search tree.
     * @param side Current player side.
     * @return Returns weigth of the board.
    */
    int minimax(int depth, playingSide side);
    
    /**
     * @brief Method that makes move on the board.
     * @param move Move to be try.
     * @return Returns true if the move was all right, false otherwise.
    */
    bool makeMove(Move move);

    /**
     * @brief Method that return back last maked move.
     * @return Returns true if the return back was all right, false otherwise.
    */
    bool unmakeMove();

    /**
     * @brief Method that gets all possible moves.
     * @param side Player's side.
     * @return Returns vector of all possible moves.
    */
    vector<Move> getAllPossibleMoves(playingSide side);

    /**
     * @brief Method that gets current board evaluation.
     * @param side Player's side.
     * @param print True if the board should be print, false otherwise.
     * @return Returns weigth of the board.
    */
    int getBoardWeight(playingSide side, bool print) const;

    /**
     * @brief Method that gets the opopsite side.
     * @param side Current player's side.
     * @return Returns opposite side.
    */
    playingSide getOppositeSide(playingSide side);
    
    /**
     * @brief Method that gets all pieces from the board.
     * @param board Board with the all pieces on it.
     * @return Returns vector of all pieces.
    */
    vector<shared_ptr<Piece>> getAllPieces(const Board& board) const;

    /**
     * @brief Method that gets all pieces of one side from the board.
     * @param board Board with the all pieces on it.
     * @param player Side which pieces you wants.
     * @return Returns vector of all pieces from one side.
    */
    vector<shared_ptr<Piece>> getPlayingSidePieces(const Board& board, playingSide player) const;
};

#endif //CHESS_AI_H

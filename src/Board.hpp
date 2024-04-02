#pragma once

#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#include "Move.hpp"
#include "Piece.hpp"

class Board {
   private:
    class State {
       public:
        uint8_t flags = 0;
        int plySinceLastPawnMoveOrCapture;
    };

    void setUpKingSquares();
    void setUpAttackedSquares();


    uint64_t attackedByWhite = 0;
    uint64_t attackedByBlack = 0;

   public:
    Board();
    ~Board();
    uint8_t pieces[64] = {0};

    State state;
    std::stack<State> stateHistory;

    int fullMoveCounter;
    int enPassentSquare;
    bool whiteActive;

    int whiteKingSquare = 0;
    int blackKingSquare = 0;

    void readFen(const std::string& fen);
    std::string getFen();

    void make(Move move);
    void unmake(Move move);

    bool isAttacked(int square, bool white);

    static std::string fieldToString(int square);
    static int stringToField(const std::string& str);

    bool isInCheck(bool white);

    void printBoard();

    static const int WHITE_KING_SIDE_CASTLE = 1;
    static const int WHITE_QUEEN_SIDE_CASTLE = 1 << 1;
    static const int BLACK_KING_SIDE_CASTLE = 1 << 2;
    static const int BLACK_QUEEN_SIDE_CASTLE = 1 << 3;
    static constexpr int rank(int square) { return square / 8; }
    static constexpr int file(int square) { return square % 8; }
};

#pragma once

#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#include "Move.hpp"
#include "Piece.hpp"

class Board {
    class State {
       public:
        uint8_t flags = 0;
        int plySinceLastPawnMoveOrCapture;
    };

   public:
    Board();
    ~Board();
    uint8_t pieces[64] = {0};
    State state;
    std::stack<State> stateHistory;
    int fullMoveCounter;
    int enPassentSquare;
    bool whiteActive;
    void readFen(const std::string& fen);
    std::string getFen();
    void make(Move move);
    void unmake(Move move);
    bool isAttacked(int square, bool white);
    bool isInCheck(bool white);
    void printBoard();
    static std::string fieldToString(int square);
    static int stringToField(const std::string& str);

    static const int WHITE_KING_SIDE_CASTLE = 1;
    static const int WHITE_QUEEN_SIDE_CASTLE = 1 << 1;
    static const int BLACK_KING_SIDE_CASTLE = 1 << 2;
    static const int BLACK_QUEEN_SIDE_CASTLE = 1 << 3;
    static constexpr int rank(int square) { return square / 8; }
    static constexpr int file(int square) { return square % 8; }
};

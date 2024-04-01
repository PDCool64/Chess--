#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "Piece.hpp"
#include "Move.hpp"

class Board {
   public:
    Board();
    ~Board();
    // 0: empty, 1: white, 2: black
    uint8_t pieces[64] = {0};
    uint8_t flags = 0;
    bool whiteActive;
    int plySinceLastPawnMoveOrCapture;
    int fullMoveCounter;
    int enPassentSquare;
    void readFen(const std::string& fen);
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

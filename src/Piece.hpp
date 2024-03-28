#pragma once

#include <array>

class Piece {
   private:
   public:
    Piece();
    ~Piece();
    /*
    WBPPP 
    000 -> Empty
    001 -> Rook
    010 -> Knight
    011 -> Bishop
    100 -> Queen
    101 -> King
    110 -> Pawn
    */
    static const int EMPTY = 0;
    static const int ROOK = 1;
    static const int KNIGHT = 2;
    static const int BISHOP = 3;
    static const int QUEEN = 4;
    static const int KING = 5;
    static const int PAWN = 6;
    static const int BLACK = 8;
    static const int WHITE = 16;
    static const std::array<int, 8> offsets;

    static int fromChar(char c);
    static char toChar(int piece);
};

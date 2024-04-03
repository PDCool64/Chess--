#pragma once

#include <bitset>
#include <list>

#include "Board.hpp"
#include "Move.hpp"

class MoveGenerator {
   private:
   public:
    MoveGenerator();
    ~MoveGenerator();
    static std::list<Move> generateMoves(Board board);
    static std::list<Move> generatePawnMoves(Board board, char square);
    static std::list<Move> generateKnightMoves(Board board, char square);
    static std::list<Move> generateKingMoves(Board board, char square);
    static std::list<Move> generateLegalMoves(Board board);
    static std::list<Move> generateSlidingMoves(Board board, bool diagonal,
                                                bool straight, bool oneSquare,
                                                char square);
};

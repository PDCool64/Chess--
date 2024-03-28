#include <bitset>
#include <iostream>
#include <map>
#include <string>

#include "Board.hpp"
#include "Move.hpp"
#include "MoveGenerator.hpp"
#include "Piece.hpp"

void printBoard(Board board) {
    for (int i = 7; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            std::cout << board.pieces[i * 8 + j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    Move move(8, 24);
    std::string startpos =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Board board;
    board.readFen(startpos);
    printBoard(board);
    for (Move m : MoveGenerator::generateMoves(board)) {
        std::cout << m.toString() << std::endl;
    }
}
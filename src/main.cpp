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
        for (int j = 0; j < 8; j++) {
            std::cout << Piece::toChar(board.pieces[i * 8 + j]) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    Move move(8, 24);
    std::string startpos =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string pawnCapturePos =
        "rnbqkbnr/ppppp1pp/8/5p2/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2";
    Board board;
    board.readFen(pawnCapturePos);
    printBoard(board);
    std::list<Move> moves = MoveGenerator::generateMoves(board);
    std::cout << "Generated " << moves.size() << " moves" << std::endl;
    for (Move m : moves) {
        std::cout << m.toString() << std::endl;
    }
}
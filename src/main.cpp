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
    std::cout << board.flags << std::endl;
    std::cout << "Color to move " << (board.whiteActive ? "white" : "black")
              << std::endl;
    std::cout << "En passent square "
              << Board::fieldToString(board.enPassentSquare) << std::endl;
    std::cout << "Ply since last pawn move or capture "
              << board.plySinceLastPawnMoveOrCapture << std::endl;
    std::cout << "Full move counter " << board.fullMoveCounter << std::endl;
    std::cout << "Castling rights: ";
    std::cout << ((board.flags & Board::WHITE_KING_SIDE_CASTLE) ? "K" : "");
    std::cout << ((board.flags & Board::WHITE_QUEEN_SIDE_CASTLE) ? "Q" : "");
    std::cout << ((board.flags & Board::BLACK_KING_SIDE_CASTLE) ? "k" : "");
    std::cout << ((board.flags & Board::BLACK_QUEEN_SIDE_CASTLE) ? "q" : "");
    std::cout << std::endl;
}

int main() {
    Move move(8, 24);
    std::string startpos =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string pawnCapturePos =
        "rnbqkbnr/ppppp1pp/8/5p2/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2";
    std::string pawnCapturePos2 =
        "rnbqkbnr/ppppp1pp/8/5p2/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 4 4";
    std::string enPassenPos =
        "rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 5";
    std::string castlingPos =
        "rnbqkbn1/ppp1p1pr/8/3pPp1p/8/8/PPPP1PPP/RNBQKBNR w q - 2 7";
    Board board;
    board.readFen(castlingPos);
    printBoard(board);
    std::list<Move> moves = MoveGenerator::generateMoves(board);
    std::cout << "Generated " << moves.size() << " moves" << std::endl;
    for (Move m : moves) {
        std::cout << m.toString() << std::endl;
    }
}
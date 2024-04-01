#include <bitset>
#include <iostream>
#include <map>
#include <string>

#include "Board.hpp"
#include "Move.hpp"
#include "MoveGenerator.hpp"
#include "Piece.hpp"



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
    std::string castlingPos2 =
        "rnbqk1nr/pppp1ppp/8/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 "
        "4";
    std::string castlingPos3 =
        "rn1qkbnr/ppp1pppp/B2p4/1b6/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4";
    Board board;
    board.readFen(castlingPos3);
    board.printBoard();
    std::list<Move> moves = MoveGenerator::generateLegalMoves(board);
    std::cout << "Generated " << moves.size() << " moves" << std::endl;
    for (Move m : moves) {
        std::cout << m.toString() << std::endl;
    }
}
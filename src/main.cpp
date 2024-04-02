#include <bitset>
#include <cassert>
#include <iostream>
#include <map>
#include <string>

#include "Board.hpp"
#include "Move.hpp"
#include "MoveGenerator.hpp"
#include "Piece.hpp"

int test(Board board, int depth) {
    if (depth == 0) {
        return 1;
    }
    std::list<Move> moves = MoveGenerator::generateLegalMoves(board);
    int sum = 0;
    for (Move m : moves) {
        board.make(m);
        int score = test(board, depth - 1);
        sum += score;
        board.unmake(m);
    }
    return sum;
}

void fn(Board board, int depth) {
    std::list<Move> moves = MoveGenerator::generateLegalMoves(board);
    int i = 1;
    int sum = 0;
    for (Move m : moves) {
        board.make(m);
        int score = test(board, depth - 1);
        sum += score;
        std::cout << m.toString() << ": " << score << std::endl;
        board.unmake(m);
        i++;
    }
    std::cout << "Total: " << sum << std::endl;
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
    std::string castlingPos2 =
        "rnbqk1nr/pppp1ppp/8/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 2 "
        "4";
    std::string castlingPos3 =
        "rn1qkbnr/ppp1pppp/B2p4/1b6/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4";
    std::string castlingPos4 =
        "rn1qkbnr/ppp1pppp/B2p4/1b2P3/8/5N2/PPPP1PPP/RNBQK2R b KQkq - 0 4";
    std::string castlingPos5 =
        "rn1qkbnr/ppp1pppp/B2p4/4P3/8/5N2/PPPP1PPP/RNBQKb1R w KQkq - 1 5";
    std::string castlingPos6 =
        "rn1qkbnr/ppp1pppp/B2p4/4P3/8/3b1N2/PPPP1PPP/RNBQK2R w KQkq - 1 5";
    std::string trickyPos =
        "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
    std::string trickyPos2 =
        "rnbq1k1r/pp1Pbppp/2p5/8/2B5/P7/1PP1NnPP/RNBQK2R b KQ - 0 8";
    std::string promotedPos =
        "rnNq1k1r/pp2bppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R b KQ - 0 8";
    std::string trickyPos3 =
        "rnbq1k1r/pp1Pbppp/2p5/8/2B5/P7/1PP1NnPP/RNBQK2R b KQ - 0 8";
    std::string trickyPos4 =
        "rnb2k1r/pp1Pbppp/1qp5/8/2B5/P7/1PP1NnPP/RNBQK2R w KQ - 1 9";
    std::string trickyPos_h2h3 =
        "rnbq1k1r/pp1Pbppp/2p5/8/2B5/7P/PPP1NnP1/RNBQK2R b KQ - 0 8";
    std::string trickyPos_h2h3_c6c5 =
        "rnbq1k1r/pp1Pbppp/8/2p5/2B5/7P/PPP1NnP1/RNBQK2R w KQ - 0 9";
    std::string trickyPos_h2h4 =
        "rnbq1k1r/pp1Pbppp/2p5/8/2B4P/8/PPP1NnP1/RNBQK2R b KQ - 0 8";
    std::string trickyPos_h2h4_a7a5 =
        "rnbq1k1r/1p1Pbppp/2p5/p7/2B4P/8/PPP1NnP1/RNBQK2R w KQ - 0 9";
    std::string trickyPos_h2h4_d8a5 =
        "rnb2k1r/pp1Pbppp/2p5/q7/2B4P/8/PPP1NnP1/RNBQK2R w KQ - 1 9";
    std::string trickyPos_h2h4_d8a5_c2c3 =
        "rnb2k1r/pp1Pbppp/2p5/q7/2B4P/2P5/PP2NnP1/RNBQK2R b KQ - 0 9";
    Board board;
    board.readFen(startpos);
    board.printBoard();
    fn(board, 4);
}

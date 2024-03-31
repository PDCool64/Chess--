#include "../MoveGenerator.hpp"

std::list<Move> MoveGenerator::generateKnightMoves(Board board, char square) {
   std::list<Move> moves;
    int offsets[] = {-17, -15, -10, -6, 6, 10, 15, 17};

    for (int offset : offsets) {
        int targetSquare = square + offset;
        // Make sure the target square is on the board
        if (targetSquare < 0 || targetSquare > 63) {
            continue;
        }
       // Make sure the target square did not jump over the edge of the board
        if (std::abs(targetSquare % 8 - square % 8) +
                std::abs(targetSquare / 8 - square / 8) !=
            3) {
            continue;
        }
        // Moves to empty squares
        if (board.pieces[targetSquare] == Piece::EMPTY) {
            Move move = Move(square, targetSquare);
            moves.push_back(move);
        } else if (((board.pieces[targetSquare] & Piece::WHITE) ==
                    Piece::WHITE) != board.whiteActive) {
            Move move = Move(square, targetSquare);
            move.setCapturedPiece(board.pieces[targetSquare]);
            moves.push_back(move);
        }
    }
    return moves;
}
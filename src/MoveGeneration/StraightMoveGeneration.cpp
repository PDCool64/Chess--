#include "../MoveGenerator.hpp"

std::list<Move> MoveGenerator::generateStraightMoves(Board board, char square) {
    return generateStraightMoves(board, square, 8);
}

// limit is the maximum number of squares the move can go
// the king can only move one square in any direction so the limit is 1
std::list<Move> MoveGenerator::generateStraightMoves(Board board, char square,
                                                     int limit) {
    std::list<Move> moves;
    int offsets[] = {-8, -1, 8, 1};
    char piece = board.pieces[square];
    for (int offset : offsets) {
        for (int i = 1; i <= limit; ++i) {
            int targetSquare = square + offset * i;
            // Make sure the target square is on the board
            if (targetSquare < 0 || targetSquare > 63) {
                continue;
            }
            // Make sure the target square is on one axis the same 
            // because otherwise it would have been over the edge of the board
            // and wrapped around in another row
            if ((targetSquare % 8 != square % 8) &&
                (targetSquare / 8 != square / 8)) {
                continue;
            }
            // Moves to empty squares
            if (board.pieces[targetSquare] == Piece::EMPTY) {
                Move move = Move(square, targetSquare);
                moves.push_back(move);
            } else {
                if (!Piece::isSameColor(piece, board.pieces[targetSquare])) {
                    Move move =
                        Move(square, targetSquare, board.pieces[targetSquare]);
                    move.setCapturedPiece(board.pieces[targetSquare]);
                    moves.push_back(move);
                }
                break;
            }
        }
    }
    return moves;
}
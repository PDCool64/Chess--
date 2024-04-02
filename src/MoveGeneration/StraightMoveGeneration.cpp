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
            
            // Make sure that each offset iteration 
            // does not wrap around and go to the other side of the board
            // in case it hits a valid square 
            // which would then be counted twice
            if (offset == -1 && targetSquare % 8 == 7) {
                break;
            }
            if (offset == 1 && targetSquare % 8 == 0) {
                break;
            }
            if (offset == -8 && targetSquare < 0) {
                break;
            }
            if (offset == 8 && targetSquare > 63) {
                break;
            }
            // Make sure the target square is on the board
            if (targetSquare < 0 || targetSquare > 63) {
                continue;
            }
            // Moves to empty squares
            if (board.pieces[targetSquare] == Piece::EMPTY) {
                Move move = Move(square, targetSquare);
                moves.push_back(move);
            } else {
                if (!Piece::isSameColor(piece, board.pieces[targetSquare])) {
                    Move move(square, targetSquare, board.pieces[targetSquare]);
                    move.setCapturedPiece(board.pieces[targetSquare]);
                    moves.push_back(move);
                }
                break;
            }
        }
    }
    return moves;
}
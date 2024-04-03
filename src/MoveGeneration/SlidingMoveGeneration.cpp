#include "../MoveGenerator.hpp"

std::list<Move> MoveGenerator::generateSlidingMoves(Board board, bool diagonal,
                                                    bool straight,
                                                    bool oneSquare,
                                                    char square) {
    std::list<Move> moves;
    int offsets[] = {-9, -7, 7, 9, -8, 1, 8, -1};

    int start = diagonal ? 0 : 4;
    int end = straight ? 8 : 4;
    int limit = oneSquare ? 1 : 8;

    char piece = board.pieces[square];
    for (int i = start; i < end; ++i) {
        for (int j = 1; j <= limit; ++j) {
            int targetSquare = square + offsets[i] * j;

            // Make sure that each offsets[i] iteration
            // does not wrap around and go to the other side of the board
            // in case it hits a valid square
            // which would then be counted twice
            if (std::abs(Board::rank(targetSquare) -
                         Board::rank(targetSquare - offsets[i])) > 1) {
                break;
            }
            if (std::abs(Board::file(targetSquare) -
                         Board::file(targetSquare - offsets[i])) > 1) {
                break;
            }

            // Make sure the target square is on the board
            if (targetSquare < 0 || targetSquare > 63) {
                break;
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
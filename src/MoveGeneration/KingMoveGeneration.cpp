#include "../MoveGenerator.hpp"

std::list<Move> MoveGenerator::generateKingMoves(Board board, char square) {
    std::list<Move> moves;
    // add the straight moves but only one square in each direction
    moves.splice(moves.end(), generateStraightMoves(board, square, 1));
    // add the diagonal moves but only one square in each direction
    moves.splice(moves.end(), generateDiagonalMoves(board, square, 1));
    return moves;
}
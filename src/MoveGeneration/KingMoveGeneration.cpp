#include "../MoveGenerator.hpp"

std::list<Move> MoveGenerator::generateKingMoves(Board board, char square) {
    std::list<Move> moves;
    // add the straight moves but only one square in each direction
    moves.splice(moves.end(), generateStraightMoves(board, square, 1));
    // add the diagonal moves but only one square in each direction
    moves.splice(moves.end(), generateDiagonalMoves(board, square, 1));

    // castling
    char piece = board.pieces[square];
    bool white = piece & Piece::WHITE;
    char flags = board.state.flags;
    // if the color is black, then we need to shift the flags to the right so we
    // can use the same masks for both colors
    if (!white)
        flags = flags >> 2;
    // check if there are any castling rights
    if (!(flags & 3))
        return moves;

    int rank = Board::rank(square);

    // king side castle
    if (flags & Board::WHITE_KING_SIDE_CASTLE) {
        // check if the squares between the king and the rook are empty
        if (board.pieces[5 + rank * 8] == Piece::EMPTY &&
            board.pieces[6 + rank * 8] == Piece::EMPTY) {
            // check if the squares are attacked
            if (!board.isAttacked(4 + rank * 8, white) &&
                !board.isAttacked(5 + rank * 8, white) &&
                !board.isAttacked(6 + rank * 8, white)) {
                Move move = Move(square, 6 + rank * 8);
                move.setIsKingSideCastle(true);
                moves.push_back(move);
            }
        }
    }
    if (flags & Board::WHITE_QUEEN_SIDE_CASTLE) {
        // check if the squares between the king and the rook are empty
        if (board.pieces[1 + rank * 8] == Piece::EMPTY &&
            board.pieces[2 + rank * 8] == Piece::EMPTY &&
            board.pieces[3 + rank * 8] == Piece::EMPTY) {
            // check if the squares are attacked
            if (!board.isAttacked(4 + rank * 8, white) &&
                !board.isAttacked(3 + rank * 8, white) &&
                !board.isAttacked(2 + rank * 8, white)) {
                Move move = Move(square, 2 + rank * 8);
                move.setIsQueenSideCastle(true);
                moves.push_back(move);
            }
        }
    }
    return moves;
}
#include "MoveGenerator.hpp"

MoveGenerator::MoveGenerator() {}

MoveGenerator::~MoveGenerator() {}

std::list<Move> MoveGenerator::generateMoves(Board board) {
    for (char i = 0; i < 64; ++i) {
        if (board.pieces[i] == Piece::EMPTY) {
            continue;
        }
        std::cout << "Generating moves for " << board.pieces[i]
                  << " at square " << i << std::endl;
        switch (board.pieces[i]) {
            case Piece::PAWN:
                return generatePawnMoves(board, i);
                break;
            case Piece::KNIGHT:
                return generateKnightMoves(board, i);
                break;
            case Piece::BISHOP:
                return generateDiagonalMoves(board, i);
                break;
            case Piece::ROOK:
                return generateStraightMoves(board, i);
            case Piece::QUEEN: {
                std::list<Move> moves =
                    generateDiagonalMoves(board, i);
                moves.merge(generateStraightMoves(board, i));
                return moves;
            }
            case Piece::KING:
                return generateKingMoves(board, i);
            default:
                break;
        }
    }
    std::list<Move> moves;
    return moves;
}

std::list<Move> MoveGenerator::generatePawnMoves(Board board,
                                                 char square) {
    char piece = board.pieces[square];
    std::list<Move> moves;
    // White pawn
    bool white = piece & Piece::WHITE;

    int direction = white ? 1 : -1;
    // check one square infront of the pawn
    if (board.pieces[square + 8 * direction] == Piece::EMPTY) {
        moves.push_back(Move(square, square + 8 * direction));
    }
}
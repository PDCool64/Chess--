#include "MoveGenerator.hpp"
MoveGenerator::MoveGenerator() {}

MoveGenerator::~MoveGenerator() {}

std::list<Move> MoveGenerator::generateMoves(Board board) {
    std::list<Move> moves;
    for (char i = 0; i < 64; ++i) {
        if (board.pieces[i] == Piece::EMPTY) {
            continue;
        }
        if (((board.pieces[i] & Piece::WHITE) == Piece::WHITE) !=
            board.whiteActive) {
            continue;
        }
        std::list<Move> temp;
        switch (board.pieces[i] & Piece::PIECE_MASK) {
            case Piece::PAWN:
                temp = generatePawnMoves(board, i);
                for (Move& move : temp) {
                    move.setPieceType(Piece::PAWN);
                }
                moves.splice(moves.begin(), temp);
                break;
            case Piece::KNIGHT:
                temp = generateKnightMoves(board, i);
                for (Move& move : temp) {
                    move.setPieceType(Piece::KNIGHT);
                }
                moves.splice(moves.end(), temp);
                break;
            case Piece::BISHOP:
                temp = generateSlidingMoves(board, true, false, false, i);
                for (Move& move : temp) {
                    move.setPieceType(Piece::BISHOP);
                }
                moves.splice(moves.end(), temp);
                break;
            case Piece::ROOK:
                temp = generateSlidingMoves(board, false, true, false, i);
                for (Move& move : temp) {
                    move.setPieceType(Piece::ROOK);
                }
                moves.splice(moves.end(), temp);
                break;
            case Piece::QUEEN:
                temp = generateSlidingMoves(board, true, true, false, i);
                for (Move& move : temp) {
                    move.setPieceType(Piece::QUEEN);
                }
                moves.splice(moves.end(), temp);
                break;
            case Piece::KING:
                temp = generateKingMoves(board, i);
                for (Move& move : temp) {
                    move.setPieceType(Piece::KING);
                }
                moves.splice(moves.end(), temp);
                break;
            default:
                break;
        }
    }
    return moves;
}

std::list<Move> MoveGenerator::generateLegalMoves(Board board) {
    std::list<Move> moves = generateMoves(board);
    std::list<Move> legalMoves;
    for (Move move : moves) {
        Board newBoard = board;
        newBoard.make(move);
        if (!newBoard.isInCheck(board.whiteActive)) {
            legalMoves.push_back(move);
        }
    }
    return legalMoves;
}
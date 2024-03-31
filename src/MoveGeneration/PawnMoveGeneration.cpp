#include "../MoveGenerator.hpp"

std::list<Move> MoveGenerator::generatePawnMoves(Board board, char square) {
    char piece = board.pieces[square];
    std::list<Move> moves;
    // White pawn
    bool white = piece & Piece::WHITE;

    int direction = white ? 1 : -1;
    // check one square infront of the pawn
    int targetSquare = square + 8 * direction;
    if (board.pieces[targetSquare] == Piece::EMPTY) {
        Move move = Move(square, targetSquare);
        moves.push_back(move);
        // if pawn is white and on rank 2 or black and on rank 7
        // they can move two squares
        int bigPawnRank = white ? 1 : 6;
        // checks for the rank since
        // if you divide by 8 you get the rank
        if ((square / 8) == bigPawnRank &&
            board.pieces[targetSquare] == Piece::EMPTY) {
            // two square jump
            targetSquare = square + 16 * direction;
            Move move = Move(square, targetSquare);
            moves.push_back(move);
        }
    }

    // check for captures
    // left capture
    // if the square is not on the left edge of the board
    if (square % 8 != 0) {
        // goes one row in the move direction and then left
        targetSquare = square + 8 * direction - 1;
        if (board.pieces[targetSquare] != Piece::EMPTY &&
            ((board.pieces[targetSquare] & Piece::WHITE) == Piece::WHITE) !=
                white) {
            Move move = Move(square, targetSquare);
            move.setCapturedPiece(board.pieces[targetSquare]);
            moves.push_back(move);
        }
    }

    // right capture
    // if the square is not on the right edge of the board
    if (square % 8 != 7) {
        // goes one row in the move direction and then right
        targetSquare = square + 8 * direction + 1;
        if (board.pieces[targetSquare] != Piece::EMPTY &&
            ((board.pieces[targetSquare] & Piece::WHITE) == Piece::WHITE) !=
                white) {
            Move move = Move(square, targetSquare);
            move.setCapturedPiece(board.pieces[targetSquare]);
            moves.push_back(move);
        }
    }

    // std::cout << "Generated " << moves.size() << " moves for pawn at square "
    //           << Board::fieldToString(square) << std::endl;

    // TODO: Implement promotion
    // TODO: Implement en passant
    return moves;
}
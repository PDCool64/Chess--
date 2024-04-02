#include "Move.hpp"

#include "Board.hpp"

Move::Move() {}

Move::Move(int startSqare, int targetSqare) {
    state |= (startSqare & STARTSQUARE_MASK);
    state |= (targetSqare << 6) & TARGET_SQUARE_MASK;
}

Move::Move(int startSqare, int targetSqare, int pieceType) {
    state |= (startSqare & STARTSQUARE_MASK);
    state |= (targetSqare << 6) & TARGET_SQUARE_MASK;
    state |= (pieceType << 29) & PIECE_TYPE_MASK;
}

Move::~Move() {}

int Move::getStartSquare() { return state & STARTSQUARE_MASK; }

int Move::getTargetSquare() {
    return (state & TARGET_SQUARE_MASK) >> TARGET_SQUARE_SHIFT;
}

bool Move::getIsBigPawnMove() {
    return (state & IS_BIG_PAWN_MOVE_MASK) >> IS_BIG_PAWN_MOVE_SHIFT;
}

bool Move::getIsEnPassent() {
    return (state & IS_EN_PASSENT_MASK) >> IS_EN_PASSENT_SHIFT;
}

bool Move::getIsKingSideCastle() {
    return (state & KING_SIDE_CASTLE_MASK) >> KING_SIDE_CASTLE_SHIFT;
}

bool Move::getIsQueenSideCastle() {
    return (state & QUEEN_SIDE_CASTLE_MASK) >> QUEEN_SIDE_CASTLE_SHIFT;
}

int Move::getPromotionPiece() {
    return (state & PROMOTION_MASK) >> PROMOTION_SHIFT;
}

std::string Move::toString() {
    std::string str = "";
    if (getIsKingSideCastle())
        return "O-O";
    if (getIsQueenSideCastle())
        return "O-O-O";
    // if(getPieceType() != Piece::PAWN) {
    //     str += Piece::toChar(getPieceType());
    // }

    str += Board::fieldToString(getStartSquare());
    str += Board::fieldToString(getTargetSquare());
    if (getPromotionPiece() != Piece::EMPTY) {
        str += Piece::toChar(getPromotionPiece()) + 32;
        return str;
    }
    return str;
}

int Move::getPieceType() {
    return (state & PIECE_TYPE_MASK) >> PIECE_TYPE_SHIFT;
}

int Move::getCapturedPiece() {
    return (state & CAPTURED_PIECE_MASK) >> CAPTURED_PIECE_SHIFT;
}

void Move::setPromotionPiece(char piece) {
    // clear the promotion bits
    state &= ~PROMOTION_MASK;
    // set the promotion bits
    state = state | ((piece << PROMOTION_SHIFT) & PROMOTION_MASK);
}

void Move::setIsBigPawnMove(int square) {
    // clear the big pawn move bit
    state &= ~IS_BIG_PAWN_MOVE_MASK;
    // shift the square to the correct position and set the bit
    state |= (square << IS_BIG_PAWN_MOVE_SHIFT) & IS_BIG_PAWN_MOVE_MASK;
}

void Move::setIsEnPassent(bool isEnPassent) {
    state &= ~IS_EN_PASSENT_MASK;
    state |= isEnPassent << IS_EN_PASSENT_SHIFT;
}

void Move::setIsQueenSideCastle(bool isQueenSideCastle) {
    state &= ~QUEEN_SIDE_CASTLE_MASK;
    state |= isQueenSideCastle << QUEEN_SIDE_CASTLE_SHIFT;
}

void Move::setIsKingSideCastle(bool isKingSideCastle) {
    // clear the king side castle bit
    state &= ~KING_SIDE_CASTLE_MASK;
    // shift the isKingSideCastle to the correct position and set the bit
    state |= isKingSideCastle << KING_SIDE_CASTLE_SHIFT;
}

void Move::setStartSquare(int square) {
    state &= ~STARTSQUARE_MASK;
    state |= square & STARTSQUARE_MASK;
}

void Move::setTargetSquare(int square) {
    state &= ~TARGET_SQUARE_MASK;
    state |= (square << TARGET_SQUARE_SHIFT) & TARGET_SQUARE_MASK;
}

void Move::setCapturedPiece(int piece) {
    state &= ~CAPTURED_PIECE_MASK;
    state |= (piece << CAPTURED_PIECE_SHIFT) & CAPTURED_PIECE_MASK;
}

void Move::setPieceType(int piece) {
    state &= ~PIECE_TYPE_MASK;
    state |= (piece << PIECE_TYPE_SHIFT) & PIECE_TYPE_MASK;
}

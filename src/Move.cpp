#include "Move.hpp"

Move::Move() {}

Move::Move(int startSqare, int targetSqare) {
    state |= (startSqare & STARTSQUARE_MASK);
    state |= (targetSqare << 6) & TARGET_SQUARE_MASK;
}

Move::~Move() {}

int Move::getStartSqare() { return state & STARTSQUARE_MASK; }

int Move::getTargetSquare() { return (state & TARGET_SQUARE_MASK) >> 6; }

int Move::getEnPassentSquare() {
    return (state & EN_PASSENT_SQUARE_MASK) >> 12;
}

int Move::getIsKingSideCastle() {
    return (state & KING_SIDE_CASTLE_MASK) >> 19;
}

int Move::getIsQueenSideCastle() {
    return (state & QUEEN_SIDE_CASTLE_MASK) >> 18;
}

int Move::getPromotionPiece() { return (state & PROMOTION_MASK) >> 20; }

int Move::getIsEnPassent() { return getEnPassentSquare() != 0; }

std::string Move::toString() {
    std::string str = "";
    str += std::to_string(getStartSqare());
    str += " ";
    str += std::to_string(getTargetSquare());
    return str;
}

int Move::getIsCapture() { return (state & IS_CAPTURE_MASK) >> 29; }

int Move::getCapturedPiece() { return (state & CAPTURED_PIECE_MASK) >> 24; }

void Move::setPromotionPiece(char piece) {
    // clear the promotion bits
    state &= ~PROMOTION_MASK;
    // set the promotion bits
    state = state | ((piece << 20) & PROMOTION_MASK);
}

void Move::setEnPassentSquare(int square) {
    // clear the en passent bits
    state &= ~EN_PASSENT_SQUARE_MASK;
    // set the en passent bits
    state |= (square << 12) & EN_PASSENT_SQUARE_MASK;
}

void Move::setQueenSideCastle(bool isQueenSideCastle) {
    state &= ~QUEEN_SIDE_CASTLE_MASK;
    state |= isQueenSideCastle << 18;
}

void Move::setKingSideCastle(bool isKingSideCastle) {
    // clear the king side castle bit
    state &= ~KING_SIDE_CASTLE_MASK;
    // shift the isKingSideCastle to the correct position and set the bit
    state |= isKingSideCastle << 19;
}

void Move::setStartSquare(int square) {
    state &= ~STARTSQUARE_MASK;
    state |= square & STARTSQUARE_MASK;
}

void Move::setTargetSquare(int square) {
    state &= ~TARGET_SQUARE_MASK;
    state |= (square << 6) & TARGET_SQUARE_MASK;
}

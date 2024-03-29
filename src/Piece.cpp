#include "Piece.hpp"

// clang-format off
const std::array<int, 8> Piece::offsets = {-9, -7, 7,  9, 8,  1,  -1, -8};
// clang-format on

Piece::Piece() {}
Piece::~Piece() {}

int Piece::fromChar(char c) {
    int res = 0;
    if (c > 'Z') {
        res |= Piece::BLACK;
        c -= 32;
    } else {
        res |= Piece::WHITE;
    }
    switch (c) {
        case 'P':
            res |= Piece::PAWN;
            break;
        case 'N':
            res |= Piece::KNIGHT;
            break;
        case 'B':
            res |= Piece::BISHOP;
            break;
        case 'R':
            res |= Piece::ROOK;
            break;
        case 'Q':
            res |= Piece::QUEEN;
            break;
        case 'K':
            res |= Piece::KING;
            break;
    }
    return res;
}

char Piece::toChar(int piece) {
    bool black = piece & Piece::BLACK;
    // remove color from piece
    switch (piece & Piece::PIECE_MASK) {
        case Piece::PAWN:
            return 'P' + (black ? 32 : 0);
        case Piece::KNIGHT:
            return 'N' + (black ? 32 : 0);
        case Piece::BISHOP:
            return 'B' + (black ? 32 : 0);
        case Piece::ROOK:
            return 'R' + (black ? 32 : 0);
        case Piece::QUEEN:
            return 'Q' + (black ? 32 : 0);
        case Piece::KING:
            return 'K' + (black ? 32 : 0);
    }
    return ' ';
}
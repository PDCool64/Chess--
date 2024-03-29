#include "Board.hpp"

#include <iostream>

Board::Board() {}

Board::~Board() {}

void Board::readFen(const std::string& fen) {
    std::istringstream iss(fen);
    std::string field;
    int rank = 7;
    int file = 0;

    // 1. Parse piece placement
    std::getline(iss, field, ' ');
    for (char c : field) {
        if (c == '/') {
            --rank;
            file = 0;
        } else if (isdigit(c)) {
            file += c - '0';
        } else {
            // Add piece to board
            pieces[rank * 8 + file] = Piece::fromChar(c);
            ++file;
        }
    }

    // 2. Parse active color
    iss >> field;
    whiteActive = (field == "w");

    // 3. Parse castling availability
    iss >> field;
    // Set flags based on field

    // 4. Parse en passant target square
    iss >> field;
    // Set enPassentSquare based on field

    // 5. Parse halfmove clock
    iss >> plySinceLastPawnMoveOrCapture;

    // 6. Parse fullmove number
    iss >> fullMoveCounter;
}

std::string Board::fieldToString(int square) {
    std::string str = "";
    str += 'a' + square % 8;
    str += '1' + square / 8;
    return str;
}
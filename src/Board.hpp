#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "Piece.hpp"

class Board {
   public:
    Board();
    ~Board();
    // 0: empty, 1: white, 2: black
    uint8_t pieces[64] = {0};
    uint8_t flags = 0;
    bool whiteActive;
    int plySinceLastPawnMoveOrCapture;
    int fullMoveCounter;
    int enPassentSquare;
    void readFen(const std::string& fen);
};

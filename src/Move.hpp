#pragma once

#include <iostream>
#include <string>

class Move {
   public:
    Move();
    Move(int startSquare, int targetSquare);
    Move(int startSquare, int targetSquare, int piece);
    ~Move();
    // 0000 0000 PPPP KQEE EEEE TTTT TTSS SSSS
    //  P -> Promotion Piece
    //  K -> King Side Castle
    //  Q -> Queen Side Castle
    //  E -> en passent square (since you can't en passent on a1 if all six bits
    //  are zero en passent is not possible) T = Target Square S = Start Square
    //  6 bits for the square means 2^6 = 64 options
    uint32_t state = 0;
    static const int STARTSQUARE_MASK = 0b111111;
    static const int TARGET_SQUARE_MASK = 0b111111 << 6;
    static const int EN_PASSENT_SQUARE_MASK = 0b111111 << 12;
    static const int QUEEN_SIDE_CASTLE_MASK = 0b1 << 18;
    static const int KING_SIDE_CASTLE_MASK = 0b1 << 19;
    static const int PROMOTION_MASK = 0b1111 << 20;
    static const int CAPTURED_PIECE_MASK = 0b11111 << 24;
    static const int PIECE_TYPE_MASK = 0b111 << 29;

    int getStartSqare();

    int getTargetSquare();

    int getEnPassentSquare();

    int getIsKingSideCastle();

    int getIsQueenSideCastle();

    int getPromotionPiece();

    int getIsEnPassent();

    int getPieceType();

    int getCapturedPiece();

    void setPromotionPiece(char piece);

    void setEnPassentSquare(int square);

    void setQueenSideCastle(bool isQueenSideCastle);

    void setKingSideCastle(bool isKingSideCastle);

    void setStartSquare(int square);

    void setTargetSquare(int square);

    void setCapturedPiece(int piece);

    void setPieceType(int piece);

    std::string toString();
};

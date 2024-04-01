#pragma once

#include <iostream>
#include <string>

class Move {
   public:
    Move();
    Move(int startSquare, int targetSquare);
    Move(int startSquare, int targetSquare, int piece);
    ~Move();
    // 0000 0000 PPPP KQEE RRRE TTTT TTSS SSSS
    //  P -> Promotion Piece
    //  K -> King Side Castle
    //  Q -> Queen Side Castle
    //  E -> en passent square (since you can't en passent on a1 if all six bits
    //  are zero en passent is not possible) T = Target Square S = Start Square
    //  6 bits for the square means 2^6 = 64 options
    uint32_t state = 0;
    static const int STARTSQUARE_MASK = 0b111111;

    static const int TARGET_SQUARE_SHIFT = 6;
    static const int TARGET_SQUARE_MASK = 0b111111 << TARGET_SQUARE_SHIFT;

    static const int IS_BIG_PAWN_MOVE_SHIFT = TARGET_SQUARE_SHIFT + 6;
    static const int IS_BIG_PAWN_MOVE_MASK = 0b1 << IS_BIG_PAWN_MOVE_SHIFT;

    static const int IS_EN_PASSENT_SHIFT = IS_BIG_PAWN_MOVE_SHIFT + 1;
    static const int IS_EN_PASSENT_MASK = 0b1 << IS_EN_PASSENT_SHIFT;

    static const int QUEEN_SIDE_CASTLE_SHIFT = IS_EN_PASSENT_SHIFT + 1;
    static const int QUEEN_SIDE_CASTLE_MASK = 0b1 << QUEEN_SIDE_CASTLE_SHIFT;

    static const int KING_SIDE_CASTLE_SHIFT = QUEEN_SIDE_CASTLE_SHIFT + 1;
    static const int KING_SIDE_CASTLE_MASK = 0b1 << KING_SIDE_CASTLE_SHIFT;

    static const int PROMOTION_SHIFT = KING_SIDE_CASTLE_SHIFT + 1;
    static const int PROMOTION_MASK = 0b111 << PROMOTION_SHIFT;

    static const int CAPTURED_PIECE_SHIFT = PROMOTION_SHIFT + 3;
    static const int CAPTURED_PIECE_MASK = 0b111 << CAPTURED_PIECE_SHIFT;

    static const int PIECE_TYPE_SHIFT = CAPTURED_PIECE_SHIFT + 3;
    static const int PIECE_TYPE_MASK = 0b111 << PIECE_TYPE_SHIFT;



    int getStartSqare();

    int getTargetSquare();

    int getEnPassentSquare();

    bool getIsKingSideCastle();

    bool getIsQueenSideCastle();

    int getPromotionPiece();

    bool getIsBigPawnMove();

    bool getIsEnPassent();

    int getPieceType();

    int getCapturedPiece();

    void setPromotionPiece(char piece);

    void setIsBigPawnMove(int square);

    void setIsEnPassent(bool);

    void setIsQueenSideCastle(bool isQueenSideCastle);

    void setIsKingSideCastle(bool isKingSideCastle);

    void setStartSquare(int square);

    void setTargetSquare(int square);

    void setCapturedPiece(int piece);

    void setPieceType(int piece);

    std::string toString();
};

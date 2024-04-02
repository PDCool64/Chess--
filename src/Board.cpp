#include "Board.hpp"

#include <iostream>

#include "MoveGenerator.hpp"

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
    if (field == "-")
        state.flags = 0;
    else {
        state.flags = 0;
        for (char c : field) {
            switch (c) {
                case 'K':
                    state.flags |= WHITE_KING_SIDE_CASTLE;
                    break;
                case 'Q':
                    state.flags |= WHITE_QUEEN_SIDE_CASTLE;
                    break;
                case 'k':
                    state.flags |= BLACK_KING_SIDE_CASTLE;
                    break;
                case 'q':
                    state.flags |= BLACK_QUEEN_SIDE_CASTLE;
                    break;
            }
        }
    }

    // 4. Parse en passant target square
    iss >> field;
    // Set enPassentSquare based on field
    if (field == "-")
        enPassentSquare = 0;
    else
        enPassentSquare = stringToField(field);

    // 5. Parse halfmove clock
    iss >> state.plySinceLastPawnMoveOrCapture;

    // 6. Parse fullmove number
    iss >> fullMoveCounter;
}

std::string Board::getFen() {
    std::string fen = "";
    int emptyCounter = 0;
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; j++) {
            if (pieces[i * 8 + j] == Piece::EMPTY) {
                emptyCounter++;
            } else {
                if (emptyCounter != 0) {
                    fen += std::to_string(emptyCounter);
                    emptyCounter = 0;
                }
                fen += Piece::toChar(pieces[i * 8 + j]);
            }
        }
        if (emptyCounter != 0) {
            fen += std::to_string(emptyCounter);
            emptyCounter = 0;
        }
        if (i != 0) {
            fen += "/";
        }
    }
    fen += whiteActive ? " w " : " b ";
    if (state.flags == 0) {
        fen += "-";
    } else {
        if (state.flags & WHITE_KING_SIDE_CASTLE) {
            fen += "K";
        }
        if (state.flags & WHITE_QUEEN_SIDE_CASTLE) {
            fen += "Q";
        }
        if (state.flags & BLACK_KING_SIDE_CASTLE) {
            fen += "k";
        }
        if (state.flags & BLACK_QUEEN_SIDE_CASTLE) {
            fen += "q";
        }
    }
    fen += " ";
    if (enPassentSquare == 0) {
        fen += "-";
    } else {
        fen += fieldToString(enPassentSquare);
    }
    fen += " ";
    fen += std::to_string(state.plySinceLastPawnMoveOrCapture);
    fen += " ";
    fen += std::to_string(fullMoveCounter);
    return fen;

}

std::string Board::fieldToString(int square) {
    return std::string(1, 'a' + Board::file(square)) +
           std::to_string(1 + Board::rank(square));
}

int Board::stringToField(const std::string& str) {
    return (str[0] - 'a') + 8 * (str[1] - '1');
}

bool Board::isAttacked(int square, bool white) {
    // invert the color since we want to check if the square is attacked by the
    // opposite color
    bool temp = whiteActive;
    whiteActive = !white;
    std::list<Move> moves = MoveGenerator::generateMoves(*this);
    for (Move m : moves) {
        if (m.getTargetSquare() == square) {
            whiteActive = !whiteActive;
            return true;
        }
    }
    whiteActive = temp;
    return false;
}

bool Board::isInCheck(bool white) {
    int kingSquare = 0;
    for (int i = 0; i < 64; i++) {
        if (pieces[i] ==
            (white ? Piece::KING | Piece::WHITE : Piece::KING | Piece::BLACK)) {
            kingSquare = i;
            break;
        }
    }
    return isAttacked(kingSquare, white);
}

void Board::make(Move move) {
    stateHistory.push(state);

    pieces[move.getTargetSquare()] = pieces[move.getStartSquare()];
    pieces[move.getStartSquare()] = Piece::EMPTY;

    int direction = whiteActive ? 1 : -1;

    // en passent
    if (move.getIsBigPawnMove()) {
        enPassentSquare = move.getTargetSquare() - 8 * direction;
    } else {
        enPassentSquare = 0;
    }

    // castling
    if (move.getIsKingSideCastle()) {
        int rank = Board::rank(move.getTargetSquare());
        pieces[5 + rank * 8] = pieces[7 + rank * 8];
        pieces[7 + rank * 8] = Piece::EMPTY;
    } else if (move.getIsQueenSideCastle()) {
        int rank = Board::rank(move.getTargetSquare());
        pieces[3 + rank * 8] = pieces[0 + rank * 8];
        pieces[0 + rank * 8] = Piece::EMPTY;
    }

    // castling rights
    if (move.getStartSquare() == 0 || move.getTargetSquare() == 0) {
        state.flags &= ~WHITE_QUEEN_SIDE_CASTLE;
    }
    if (move.getStartSquare() == 7 || move.getTargetSquare() == 7) {
        state.flags &= ~WHITE_KING_SIDE_CASTLE;
    }
    if (move.getStartSquare() == 56 || move.getTargetSquare() == 56) {
        state.flags &= ~BLACK_QUEEN_SIDE_CASTLE;
    }
    if (move.getStartSquare() == 63 || move.getTargetSquare() == 63) {
        state.flags &= ~BLACK_KING_SIDE_CASTLE;
    }

    // update game state
    whiteActive = !whiteActive;
    state.plySinceLastPawnMoveOrCapture++;
    fullMoveCounter += whiteActive;

    // promotion
    if (move.getPromotionPiece() != Piece::EMPTY) {
        pieces[move.getTargetSquare()] = move.getPromotionPiece() | (whiteActive ? Piece::BLACK : Piece::WHITE);
    }
    // check for pawn move
    if (pieces[move.getTargetSquare()] == Piece::PAWN) {
        state.plySinceLastPawnMoveOrCapture = 0;
    }
    // check for capture
    if (move.getCapturedPiece() != Piece::EMPTY) {
        state.plySinceLastPawnMoveOrCapture = 0;
    }
}

void Board::printBoard() {
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; j++) {
            std::cout << Piece::toChar(pieces[i * 8 + j]) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << state.flags << std::endl;
    std::cout << "Color to move " << (whiteActive ? "white" : "black")
              << std::endl;
    std::cout << "En passent square "
              << (enPassentSquare != 0 ? Board::fieldToString(enPassentSquare)
                                       : " - ")
              << std::endl;
    std::cout << "Ply since last pawn move or capture "
              << state.plySinceLastPawnMoveOrCapture << std::endl;
    std::cout << "Full move counter " << fullMoveCounter << std::endl;
    std::cout << "Castling rights: ";
    std::cout << ((state.flags & Board::WHITE_KING_SIDE_CASTLE) ? "K" : "");
    std::cout << ((state.flags & Board::WHITE_QUEEN_SIDE_CASTLE) ? "Q" : "");
    std::cout << ((state.flags & Board::BLACK_KING_SIDE_CASTLE) ? "k" : "");
    std::cout << ((state.flags & Board::BLACK_QUEEN_SIDE_CASTLE) ? "q" : "");
    std::cout << std::endl;
    std::cout << "Fen: " << getFen() << std::endl;
}

void Board::unmake(Move move) {
    state = stateHistory.top();
    stateHistory.pop();

    pieces[move.getStartSquare()] = pieces[move.getTargetSquare()];
    pieces[move.getTargetSquare()] = move.getCapturedPiece();
    bool white = !whiteActive;
     
    if (move.getPromotionPiece() != Piece::EMPTY) {
        pieces[move.getStartSquare()] = Piece::PAWN | (white ? Piece::WHITE : Piece::BLACK);
    }

    if (move.getCapturedPiece() != Piece::EMPTY) {
        pieces[move.getTargetSquare()] |= (white ? Piece::BLACK : Piece::WHITE);
    }

    int direction = white ? 1 : -1;
    // en passent
    if (move.getIsEnPassent()) {
        // set the en passent square
        enPassentSquare = move.getTargetSquare();
        // reset the captured pawn
        pieces[enPassentSquare - 8 * direction] =
            Piece::PAWN | (white ? Piece::BLACK : Piece::WHITE);
    }

    // castling

    if (move.getIsKingSideCastle()) {
        int rank = Board::rank(move.getTargetSquare());
        pieces[7 + rank * 8] = pieces[5 + rank * 8];
        pieces[5 + rank * 8] = Piece::EMPTY;
    } else if (move.getIsQueenSideCastle()) {
        int rank = Board::rank(move.getTargetSquare());
        pieces[0 + rank * 8] = pieces[3 + rank * 8];
        pieces[3 + rank * 8] = Piece::EMPTY;
    }

        
    fullMoveCounter -= whiteActive;
    whiteActive = !whiteActive;
}
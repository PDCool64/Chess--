# Chess

## Move
32 bits:  
_0000 000T TTCC CPPP kqeb TTTT TTSS SSSS_  
upper case -> number
lower case -> boolean 
from end to start:
- 6 bits: start square: 0-63
- 6 bits: end square: 0-63
- 1 bit: if the move is a double pawn push 
- 1 bit: if the move is an enpassent capture move 
- 2 bits Castling: first bit is king side, second bit is queen side
- 3 bits: promotion -> 
    - 0: no promotion
    - normal piece bits
- 3 bits: Captured
    - 0-3: type
- 3 bits: type of piece

PawnMove: 
if the move is a double Move (BigPawnMove) then the enpassent flag is set to true
there is no need to set a square 
because the captured piece will always be on the target square - 8 * direction

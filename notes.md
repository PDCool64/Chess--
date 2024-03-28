# Chess

## Move
32 bits:  
_00cC CCCC PPPP kqEE EEEE TTTT TTSS SSSS_  
upper case -> number
lower case -> boolean 
from end to start:
- 6 bits: start square: 0-63
- 6 bits: end square: 0-63
- 6 bits: en passent square: 0-63
- 2 bits Castling: first bit is king side, second bit is queen side
- 4 bits: promotion -> 
    first bit: Queen
    second bit: Rook
    third bit: Bishop
    fourth bit: Knight
    if all are 0, then it is a normal move
- 6 bits: Captured
    - 0-5: type
    - 6ths bit: is capture move or not


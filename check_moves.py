from pprint import pprint

with open('stockfish.txt', 'r') as f:
    lines = f.readlines()

stockfish_moves = dict()
for line in lines: 
    move = line .replace('\n', '').split(':')
    stockfish_moves[move[0]] = move[1]

with open('myMoves.txt', 'r') as f:
    lines = f.readlines()

my_moves = dict()
for line in lines:
    move = line.replace('\n', '').split(':')
    my_moves[move[0]] = move[1]


for move, n in stockfish_moves.items():
    if move in my_moves:
        if int(n) != int(my_moves[move]):
            print(f'{move} : {n} : {my_moves[move]}')
    else:
        print(f'{move} : {n} : 0')
for move, n in my_moves.items():
    if move not in stockfish_moves:
        print(f'{move} : 0 : {n}')

temp = dict()
for line in lines:
    if line not in temp: 
        temp[line] = 1 
    else:
        print(line)
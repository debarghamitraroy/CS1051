/* Write a Prolog program to implement Depth First Search (DFS) for Tic-Tac-Toe. */

% Switch player
switch(x, o).
switch(o, x).

% Check winning condition
win(Board, Player) :-
    ( Board = [Player, Player, Player, _, _, _, _, _, _] % Row 1
    ; Board = [_, _, _, Player, Player, Player, _, _, _] % Row 2
    ; Board = [_, _, _, _, _, _, Player, Player, Player] % Row 3
    ; Board = [Player, _, _, Player, _, _, Player, _, _] % Column 1
    ; Board = [_, Player, _, _, Player, _, _, Player, _] % Column 2
    ; Board = [_, _, Player, _, _, Player, _, _, Player] % Column 3
    ; Board = [Player, _, _, _, Player, _, _, _, Player] % Diagonal 1
    ; Board = [_, _, Player, _, Player, _, Player, _, _] % Diagonal 2
    ).

% Check if board is full
full(Board) :- \+ member(e, Board).

% Make a move
move(Board, Player, NewBoard) :-
    nth0(Pos, Board, e), % Find an empty cell
    replace(Board, Pos, Player, NewBoard).

% Replace an element at position
replace([_|T], 0, X, [X|T]).
replace([H|T], I, X, [H|R]) :-
    I > 0,
    I1 is I - 1,
    replace(T, I1, X, R).

% DFS Search
dfs(Board, Player, Path) :-
    dfs_util(Board, Player, [Board], Path).

dfs_util(Board, Player, _Visited, [Board]) :-
    win(Board, Player), !. % If win found, stop

dfs_util(Board, Player, Visited, [Board | Path]) :-
    move(Board, Player, NewBoard),
    \+ member(NewBoard, Visited), % Avoid revisiting
    switch(Player, NextPlayer),
    dfs_util(NewBoard, NextPlayer, [NewBoard | Visited], Path).

% Start DFS Search
start_dfs :-
    Start = [e,e,e,e,e,e,e,e,e],
    dfs(Start, x, Path),
    write('Winning path found for X: '), nl,
    print_path(Path).

% Print Path
print_path([]).
print_path([Board | Rest]) :-
    write(Board), nl,
    print_path(Rest).

/* Write a Prolog program to implement Breadth First Search for Tic-Tac-Toe. */

% Switch Player
switch(x, o).
switch(o, x).

% Check Winning Condition
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

% Replace Nth Element
replace([_|T], 0, X, [X|T]).
replace([H|T], I, X, [H|R]) :-
    I > 0,
    I1 is I - 1,
    replace(T, I1, X, R).

% Place Player in an empty cell 'e'
move(Board, Player, NewBoard) :-
    nth0(Pos, Board, e), % find an empty position
    replace(Board, Pos, Player, NewBoard).

% returns SolutionPath as a list
bfs(StartBoard, StartPlayer, SolutionPath) :-
    bfs_queue([ state(StartBoard, [StartBoard], StartPlayer) ], [], RevPath),
    reverse(RevPath, SolutionPath).

% Queue empty -> no solution
bfs_queue([], _, _) :-
    !, fail.

% If the current board is terminal
bfs_queue([ state(Board, Path, Player) | _Rest ], _Visited, Path) :-
    switch(Player, PrevPlayer), % PrevPlayer is the one who moved to get Board
    win(Board, PrevPlayer), !.

% Expand current state: generate moves, add them to end of queue (BFS)
bfs_queue([ state(Board, Path, Player) | RestQueue ], Visited, ResultPath) :-
    findall(state(NewBoard, [NewBoard | Path], NextPlayer),
            ( move(Board, Player, NewBoard),
              \+ member(NewBoard, Visited), % not visited previously
              \+ member(NewBoard, Path), % avoid cycles in current path
              switch(Player, NextPlayer) % NextPlayer gets the turn
            ),
            NewStates),
    append(RestQueue, NewStates, UpdatedQueue),
    bfs_queue(UpdatedQueue, [Board | Visited], ResultPath).

% Helper to start a search from the empty board
start_bfs :-
    Start = [e,e,e,e,e,e,e,e,e],
    ( bfs(Start, x, Path) ->
        reverse(Path, OrderedPath),
        writeln('Shortest winning path for X (via BFS):'),
        print_path(OrderedPath)
    ; writeln('No winning path found (BFS exhausted).')
    ).

% Print Path (one board per line)
print_path([]).
print_path([Board | Rest]) :-
    write(Board), nl,
    print_path(Rest).

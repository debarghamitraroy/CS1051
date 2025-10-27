% Define goal state
goal((2,_)).

% Define possible moves (production rules)
move((X,Y), (4,Y)) :- X < 4. % R1: Fill 4-gallon jug
move((X,Y), (X,3)) :- Y < 3. % R2: Fill 3-gallon jug
move((X,Y), (0,Y)) :- X > 0. % R5: Empty 4-gallon jug
move((X,Y), (X,0)) :- Y > 0. % R6: Empty 3-gallon jug
move((X,Y), (4, Y1)) :- X + Y >= 4, Y > 0, Y1 is Y - (4 - X). % R7: Pour Y -> X until X full
move((X,Y), (X1, 3)) :- X + Y >= 3, X > 0, X1 is X - (3 - Y). % R8: Pour X -> Y until Y full
move((X,Y), (X1,0)) :- X + Y =< 4, Y > 0, X1 is X + Y. % R9: Pour Y -> X completely
move((X,Y), (0,Y1)) :- X + Y =< 3, X > 0, Y1 is X + Y. % R10: Pour X -> Y completely

% Search algorithm (DFS)
path(State, Goal, Visited, [State|Path]) :-
    move(State, NextState),
    \+ member(NextState, Visited),
    path(NextState, Goal, [NextState|Visited], Path).

path(State, State, _, [State]).

% Solve from initial state (0,0)
solve :-
    path((0,0), (2,_), [(0,0)], Path),
    print_path(Path).

% Print solution steps
print_path([]).
print_path([H|T]) :-
    write(H), nl,
    print_path(T).
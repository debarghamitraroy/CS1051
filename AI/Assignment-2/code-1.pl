/* Write a Prolog program to insert an element in a list. */

insert(E, L, [E|L]).
insert(E, [], [E]).
insert(E, [H|T], [H|R]) :-
    insert(E, T, R).
insert(E, 1, L, [E|L]).
insert(E, Pos, [H|T], [H|R]) :-
    Pos > 1,
    Pos1 is Pos - 1,
    insert(E, Pos1, T, R).
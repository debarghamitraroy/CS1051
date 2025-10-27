/* Write a Prolog program to increment one value of a list element. */

increment([], _, []).
increment([H|T], H, [H1|T]) :-
    H1 is H + 1.
increment([H|T], E, [H|R]) :-
    H \= E,
    increment(T, E, R).

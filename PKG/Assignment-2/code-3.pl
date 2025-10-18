/* Write a Prolog program to delete an element in a list. */

delete(_, [], []).
delete(E, [E|T], T).
delete(E, [H|T], [H|R]) :-
    E \= H,
    delete(E, T, R).
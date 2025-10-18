/* Write a Prolog program to decompose a list. */

decompose([]) :- 
    write('End of list.'), nl.

decompose([H|T]) :-
    write('Head: '), write(H), nl,
    write('Tail: '), write(T), nl, nl,
    decompose(T).

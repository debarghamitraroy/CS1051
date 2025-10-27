/* Write a program in prolog to check two numbers are equal or not. */

equal(X, Y) :-
    X =:= Y,
    write('The numbers are equal.').

equal(X, Y) :-
    X =\= Y,
    write('The numbers are not equal.').
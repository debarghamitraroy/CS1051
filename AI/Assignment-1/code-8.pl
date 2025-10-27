/* Write a program in prolog to find Maximum and Minimum among three numbers. */

max_min(X, Y, Z) :-
    (X >= Y, X >= Z -> Max = X ;
     Y >= X, Y >= Z -> Max = Y ;
     Max = Z),
    (X =< Y, X =< Z -> Min = X ;
     Y =< X, Y =< Z -> Min = Y ;
     Min = Z),
    write('Maximum number: '), write(Max), nl,
    write('Minimum number: '), write(Min), nl.

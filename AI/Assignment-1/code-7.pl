/* Write a program in prolog to find greater and smaller number of two numbers. */

compare_numbers(X, Y) :-
    (X > Y ->
        write('Greater number: '), write(X), nl,
        write('Smaller number: '), write(Y)
    ;
    X < Y ->
        write('Greater number: '), write(Y), nl,
        write('Smaller number: '), write(X)
    ;
        write('Both numbers are equal.')
    ).

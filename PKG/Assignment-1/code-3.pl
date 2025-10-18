/* Write a program in prolog to input two numbers from user and display it. */

input :-
    write('Enter first number: '),
    read(X),
    write('Enter second number: '),
    read(Y),
    nl,
    write('You entered:'), nl,
    write('First number: '), write(X), nl,
    write('Second number: '), write(Y), nl.

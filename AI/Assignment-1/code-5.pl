/* Write a program in prolog to input two numbers from user and perform following operation:
a. Modulus
b. Power */

operation :-
    write('Enter first number: '),
    read(X),
    write('Enter second number: '),
    read(Y),
    Modulus is X mod Y,
    Power is X ** Y,
    nl,
    write('Results:'), nl,
    write('Modulus (X mod Y): '), write(Modulus), nl,
    write('Power (X^Y): '), write(Power), nl.

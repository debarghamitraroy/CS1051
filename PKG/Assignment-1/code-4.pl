/* Write a program in prolog to show the following arithmetic operation between two 
numbers:
a. Addition 
b. Subtraction 
c. Multiplication
d. Division */

arithmetic_operations(X, Y) :-
    Sum is X + Y,
    Difference is X - Y,
    Product is X * Y,
    (Y =\= 0 -> Quotient is X / Y ; Quotient = 'undefined (division by zero)'),
    write('Addition: '), write(Sum), nl,
    write('Subtraction: '), write(Difference), nl,
    write('Multiplication: '), write(Product), nl,
    write('Division: '), write(Quotient), nl.
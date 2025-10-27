/* Write a Prolog program to concatenate two lists. */

concatenate([], L2, L2).
concatenate([H|T], L2, [H|R]) :- 
    concatenate(T, L2, R).

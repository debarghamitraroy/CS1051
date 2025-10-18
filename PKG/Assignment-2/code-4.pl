/* Write a Prolog program to generate all permutations of a list of elements. */

permutation(List) :-
    permutation(List, P),
    write(P), nl,
    fail.
permutation(_).

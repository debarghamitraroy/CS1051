/* Write a Prolog program to find the nth element of a list. */

nth_element(1, [H|_], H).
nth_element(N, [_|T], E) :-
    N > 1,
    N1 is N - 1,
    nth_element(N1, T, E).

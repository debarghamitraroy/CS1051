/* Write a Prolog program to implement prime factors of a given (user input) number.  */

% Check divisibility
divides(X, Y) :- 0 is Y mod X.

% Main predicate
prime_factors(N, Factors) :-
    N > 1,
    factor(N, 2, Factors).

% Base case
factor(1, _, []).

% If F divides N, include it and divide again
factor(N, F, [F | Rest]) :-
    divides(F, N),
    N1 is N // F,
    factor(N1, F, Rest).

% If F does not divide N, try next F
factor(N, F, Factors) :-
    F * F =< N,
    next_factor(F, NF),
    factor(N, NF, Factors).

% If F * F > N, remaining N is prime
factor(N, F, [N]) :-
    F * F > N.

% Increment factor (skip even numbers after 2)
next_factor(2, 3) :- !.
next_factor(F, NF) :-
    NF is F + 2.

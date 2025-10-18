/* Write a Prolog program to find before and after list values of particular elements in the list. */

find_before_after(E, List, Before, After) :-
    append(Before, [E|After], List).

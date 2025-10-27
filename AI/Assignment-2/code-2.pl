/* Write a Prolog program to insert an element in the last position of a list. */

insert_at_end(E, [], [E]).
insert_at_end(E, [H|T], [H|R]) :-
    insert_at_end(E, T, R).
/* Write a Prolog program that takes a student's marks as input and returns their grade according to the following rules:
Marks >= 90 → grade = excellent
Marks >= 75 and < 90 → grade = good
Marks >= 50 and < 75 → grade = average
Marks < 50 → grade = fail */

grade(Marks, excellent) :-
    Marks >= 90, !.
grade(Marks, good) :-
    Marks >= 75,
    Marks < 90, !.
grade(Marks, average) :-
    Marks >= 50,
    Marks < 75, !.
grade(Marks, fail) :-
    Marks < 50.
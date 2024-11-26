% min(e1, e2) =
% e1, if e1 <= e2
% e2, if e1 > e2

% min(E1 - number, E2 - number, R - number) -> (i, i, o)

min(E1, E2, E1):-
    E1 =< E2.
min(E1, E2, E2):-
    E1 > E2.

% findMinimum(l1l2..ln, C) =
% C, if n = 0
% findMinimum(l2l3..ln, min(l1, C)), otherwise

% findMinimum(L - list, C - collector, R - result) -> (i, i, o)

findMinimum([], C, C).
findMinimum([H|T], C, R):-
    min(H, C, MR),
    findMinimum(T, MR, R).

mainFindMinimum([H|T], R):-findMinimum(T, H, R).


% removeOcc(e, l1l2..ln) =
% [], if n = 0
% l1 U removeOcc(l2l3..ln), if l1 != e
% removeOcc(l2l3..ln), if l1 = e

% removeOcc(L - list, E - element, R - result) -> (i, i, o)

removeOcc([], _, []).
removeOcc([H|T], E, R):-
    H = E,
    removeOcc(T, E, R).
removeOcc([H|T], E, [H|R]):-
    H \= E,
    removeOcc(T, E, R).

% removeMinimumElemsOcc(l1l2..ln) =
% [], if n = 0
% removeOcc(l1l2..ln, (findMinimum(l1l2..ln)), R), otherwise

% removeMinimumElemsOcc(L - list, R - result)

removeMinimumElemsOcc([], []).
removeMinimumElemsOcc(L, R):-
    mainFindMinimum(L, MR),
    removeOcc(L, MR, R).


% nrOcc(l1l2..ln, E) = nrOcc(l2l3..ln, E) + 1, if l1 = E
%                      nrOcc(l2l3..ln, E), if l1 != E
%                      0 if n = 0

% nrOccC(l1l2..ln, E, C) = nrOcc(l2l3..ln, E, C + 1), if l1 = E
%                         nrOcc(l2l3..ln, E, C) if l1 != E
%                         C, n = 0

% mainNrOcc(l1l2..ln, E) = nrOccC(l1l2..ln, E, 0)

% nrOcc(L - list, E - element, R - number) -> (i, i, o)
% nrOccC(L - list, E - element, C - number, R - number) -> (i, i, i, o)

nrOcc([], _, 0).
nrOcc([H|T], E, R):-
    H =:= E,
    nrOcc(T, E, TR),
    R is TR + 1.
nrOcc([H|T], E, R):-
    H =\= E,
    nrOcc(T, E, R).

nrOccC([], _, C, C).
nrOccC([H|T], E, C, R):-
    H =:= E,
    CH is C + 1,
    nrOccC(T, E, CH, R).
nrOccC([H|T], E, C, R):-
    H =\= E,
    nrOccC(T, E, C, R).

mainNrOcc(L, E, R):-nrOccC(L, E, 0, R).
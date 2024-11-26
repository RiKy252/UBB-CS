% max(e1, e2) =
% e1, if e1 >= e2
% e2, if e1 < e2

% max(E1 - number, E2 - number) -> (i, i)


max(E1, E2, E1):-
    E1 >= E2.
max(E1, E2, E2):-
    E1 < E2.

% listMaxElem(l1l2..ln, c) =
% c, if n = 0
% listMaxElem(l2l3..ln, min(l1, c)), otherwise

% listMaxElem(L - list, C - collector, R - number) -> (i, i, o)

listMaxElem([], C, C).
listMaxElem([H|T], C, R):-
    max(H, C, MR),
    listMaxElem(T, MR, R).

findMaxElem([H|T], R):-
    listMaxElem(T, H, R).

% maxPos(l1l2..ln, m, i) =
% [], if n = 0
% i U maxPos(l2l3..ln), if l1 = m
% maxPos(l2l3..ln), otherwise

% (i, i, i, o)

maxPos([], _, _, []).
maxPos([H|T], M, I, [I|R]):-
    H =:= M,
    NI is I + 1,
    maxPos(T, M, NI, R).
maxPos([H|T], M, I, R):-
    H \= M,
    NI is I + 1,
    maxPos(T, M, NI, R).

mainMaxPos(L, R):-
    findMaxElem(L, M),
    maxPos(L, M, 1, R).

% main(l1l2..ln) =
% [], if n = 0
% l1 U main(l2l3..ln), if \+is_list(l1)
% mainMaxPos(l1) U main(l2l3..ln), if is_list(l1)

% (i, o)

main([], []).

main([H|T], [L|R]):-
    is_list(H),
    mainMaxPos(H, L),
    main(T, R).

main([H|T], [H|R]):-
    \+ is_list(H),
    main(T, R).

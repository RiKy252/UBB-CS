% removeIndexElem(l1l2..ln, i) =
% [], if n = 0
% removeIndexElem(l2l3..ln, -1), if i = 0
% l1 U removeIndexElem(l2l3..ln, i - 1), if i != 0
%
% removeIndexElem(L - list, I - number, R - result)
% -> flow model (i, i, o)

% removeIndexElem([], _, []).
% removeIndexElem([_|T], I, R):-
%    I =:= 0,
%    removeIndexElem(T, -1, R).
% removeIndexElem([H|T], I, [H|R]):-
%    I \= 0,
%    NI is I - 1,
%    removeIndexElem(T, NI, R).

% mainRemoveIndexElem(l1l2..ln, i) =
% [], if n = 0
% removeIndexElem(l1l2..ln, i-1), otherwise

% mainRemoveIndexElem(L - list, I - number (index), R - list)
% -> flow model (i, i, o)

% mainRemoveIndexElem([], _, []).
% mainRemoveIndexElem([H|T], I, R):-
%    NI is I-1,
%    removeIndexElem([H|T], NI, R).





% removeIndexPosition(l1l2..ln, i, x) =
% [], if n = 0
% removeIndexPosition(l2l3..ln, x + 1, x * 2 + 1), if i = 0
% l1 U removeIndexPosition(l2l3..ln, i - 1, x), otherwise

% removeIndexPosition(L - list, I - number(index), X - number, R - list)
% -> fm (i, i, i, o)

removeIndexPosition([], _, _, []).

removeIndexPosition([_|T], I, X, R):-
    I =:= 0,
    NI is X,
    NX is X * 2 + 1,
    removeIndexPosition(T, NI, NX, R).
removeIndexPosition([H|T], I, X, [H|R]):-
    I \= 0,
    NI is I - 1,
    removeIndexPosition(T, NI, X, R).

% mainRemoveIndexPosition(l1l2..ln) =
% [], if n = 0
% removeIndexPosition(l1l2..ln, 0, 1), otherwise

% mainRemoveIndexPosition(L - list, R - result) -> fm (i, o)

mainRemoveIndexPosition([], []).
mainRemoveIndexPosition([H|T], R):-
    removeIndexPosition([H|T], 0, 1, R).

% removePositions(l1l2..ln, p) =
% [], if n = 0
% mainRemoveIndexElem(l1l2..ln)
% x = i
% i--
% if i = 0 -> remove elem
% i = x * 2 + 1 - x = x + 1
% x = x * 2 + 1
%



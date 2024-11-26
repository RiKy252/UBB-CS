% Compute the product of even elements in a list.

% Mathematical model
% prodeven(l1l2..ln) =
% {
%	1 if l1l2..ln = NULL
%	l1 * prodeven(l2l3..ln) if l1 % 2 == 0, n > 0
%	prodeven(l2l3..ln) if l1 % 2 == 1
% }

prodeven([], 1).
prodeven([H|T], R):-
    H mod 2 =:= 0,
    prodeven(T, TP),
    R is TP*H.
prodeven([H|T], R):-
    H mod 2 =\= 0,
    prodeven(T, R).

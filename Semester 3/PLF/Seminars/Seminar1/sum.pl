% Compute the sum of elements of a list.
% L = [1,2,3,4] => S = 10
% sum(L - list, S - number)
% flow model (i, o) -- (i, i)

% Mathematical model
% sum(l1l2..ln) =
% {
%	0 jf l1l2..ln = NULL
%	l1 + sum(l2l3..ln) if n > 0
% }

sum([], 0).
sum([H|T], S):-
    sum(T, TS),
    S is H+TS.

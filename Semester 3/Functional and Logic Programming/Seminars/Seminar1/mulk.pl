% Multiply each element of a list with a constant value.
% Ex: [1,2,3], k=2 => [2,4,6]

% mulk(L - input list, K - number, R - output list)
% flow model (i, i, o) -- (i, i, i)

% Mathematical model
% mulk(l1..ln, k) =
% {
%	NULL if l1..ln = NULL (n = 0)
%	{l1*k} u mulk(l2..ln, k) if n > 0
% }

mulk([], _, []).
mulk([H|T], K, [NH|TR]):-
    mulk(T, K, TR),
    NH is H*K.





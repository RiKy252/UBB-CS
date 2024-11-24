% comb(l1l2..ln, k) = l1, if k = 1, n >= 1
%                     comb(l2..ln, k), if k >= 1, n > 1
%                     l1 U comb(l2..ln, k - 1), k > 1
% comb(L - list, K - number, R - list) -> (i, i, o)

comb([H|_], 1, [H]).
comb([_|T], K, R):-
    K >= 1,
    comb(T, K, R).
comb([H|T], K, [H|R]):-
    K > 1,
    K1 is K - 1,
    comb(T, K1, R).

% findall(R, comb([2, 3, 4], 2,  R), X).

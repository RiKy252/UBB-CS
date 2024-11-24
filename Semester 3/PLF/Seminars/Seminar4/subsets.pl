% [1, 2, 3] n - nr of elems, 2^n
% subsets(l1l2..ln) = [], if n = 0
%                     l1 U subsets(l2..ln), n > 0
%                     subsets(l2..ln), n > 0

subsets([], []).
subsets([H|T], [H|R]):-
    subsets(T, R).
subsets([_|T], R):-
    subsets(T, R).

% permutations (n!)
% [1, 2, 3] -> 2, 1, 3
% insertEl(e, l1..ln) = e U l1..ln, n >= 0
%                       l1 U insertEl(e, l2..ln), n > 0
% insertEl(E - elem, L - list, R - list) -> (i, i, o)

insertEl(E, L, [E|L]).
insertEl(E, [H|T], [H|R]):-
    insertEl(E, T, R).

% perm(l1l2..ln) = [], n = 0
%                  insertEl(l1, perm(l2l3..ln)), n > 0

perm([], []).
perm([H|T], R):-
    perm(T, P),
    insertEl(H, P, R).

% run with findall(R, perm([1, 2, 3], R), X).

% combinations
% [1, 2, 3], k = 2 -> [1, 3], [1, 2], [2, 3]
% comb(l1l2..ln, k) = l1, if k = 1, n >= 1
%                     comb(l2..ln, k), if k >= 1, n > 1
%                     l1 U comb(l2..ln, k - 1), k > 1

comb([H|_], 1, [H]).
comb([_|T], K, R):-
    K >= 1,
    comb(T, K, R).
comb([H|T], K, [H|R]):-
    K > 1,
    K1 is K - 1,
    comb(T, K1, R).

% arrangements
% [1, 2, 3] k = 2 => [1, 2], [2, 1] ...
% arr(l1..ln, k) = l1, if k = 1, n >= 1
%                  arr(l2..ln, k), k >= 1, n > 1
%                  insertEl(l1, arr(l2..ln, k - 1)), if k > 1

arr([H|_], 1, [H]).
arr([_|T], K, R):-
    K >= 1,
    arr(T, K, R).
arr([H|T], K, R):-
    K > 1,
    K1 is K - 1,
    arr(T, K1, A),
    insertEl(H, A, R).

% Arrangments of list with sum s prod p, with k elems

% onesol(L, K, S, P) = A, if arr(L, K) = A and suma(A) = S and prod(A)=P
% fm(i, i, i, i, o)

% onesol(L, K, S, P, A):-
%   arr(L, K, A),
%   suma(A, S),
%   prod(A, P).


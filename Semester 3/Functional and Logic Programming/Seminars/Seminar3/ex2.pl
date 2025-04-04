% Given a list of numbers and sublists of numbers, substitute each list
% in which the sum of elements is odd with the first element of that
% sublist.
% ex: [1, 2, [3, 4, 5], 5, [7], 9, [1, 2 ,4]] -> [1, 2, [3, 4, 5], 5, 7, 9, 1]

% if l1 is a list then l1 = l11, l12, ..., l1m
% ex2(l1l2..ln) = [], n = 0
%                 l11 u ex2(l2..ln), if is_list(l1) && sum(l1) % 2 = 1
% l1 u ex2(l2..ln), if atom(l1) || (is_list(l1) && sum(l1) % 2 = 0)
%
% ex2(L - list, R - list) -> fm(i, o)

sum([], 0).
sum([H|T], S):-
    sum(T, TS),
    S is H+TS.

ex2([], []).
ex2([H|T], [HL|R]):-
    is_list(H),
    sum(H, S),
    S mod 2 =:= 1,
    H = [HL|_],
    ex2(T, R).
ex2([H|T], [H|R]):-
    is_list(H),
    sum(H, S),
    S mod 2 =:= 0,
    ex2(T, R).
ex2([H|T], [H|R]):-
    \+ is_list(H),
    ex2(T, R).

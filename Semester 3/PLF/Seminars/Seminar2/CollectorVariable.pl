% sumA(l1l2..ln) = 0, if n = 0
%				   l1 + sumA(l2l3..ln), if n > 0

% sumA(L - list, S - number)
% flow model (i, o), (i, i)

sumA([], 0).
sumA([H|T], S):-
    sumA(T, TS),
    S is H + TS.

% Collector variable method
% sumC(l1l2..ln, C) = C, if n = 0
%					  sumC(l2l3..ln, l1 + C), if n > 0
% mainSumC(l1l2..ln) = sumC(l1l2..ln, 0)
% sumC(l - list, C - number, R - number)
% flow model (i, i, o)

sumC([], C, C).
sumC([H|T], C, S):-
    CNew is C + H,
    sumC(T, CNew, S).
mainSum(L, R):-sumC(L, 0, R).

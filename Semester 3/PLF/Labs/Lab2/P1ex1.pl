% P1 Ex 1
% a)
% gcd(A, B) = A, if B = 0
%           = gcd(B, A mod B), if B > 0
% gcd(A - number, B - number, R - number) -> flow model (i, i, o)
%
% lcm(A, B) = A * B / gcd(A, B)
% lcm(A - number, B - number, R - number) -> flow model (i, i, o)
%
% lcmList(l1l2..ln) = l1, if n = 1
%                   = lcm(l1, l2l3..ln), if n > 1
% lcmList(l - list, R - number) -> flow model (i, o)

gcd(A, 0, R):-R = A.
gcd(A, B, R):-
    B > 0,
    BN is A mod B,
    gcd(B, BN, R).

lcm(A, B, R):-
    gcd(A, B, X),
    R is A * B / X.

lcmList([X], X).
lcmList([H|T], R):-
    lcmList(T, R1),
    lcm(H, R1, R).
% b)
% isPowerOfTwo(x) = true, if x = 2^k, k >= 0
%                   false otherwise
% isPowerOfTwo(X - number) -> flow model (i)
%
% addAfterPowersOfTwo(l1l2..ln, v, c) = [], if n = 0
% = [l1, v] u addAfterPowersOfTwo(l2l3..ln, v, c + 1),if isPowerOfTwo(c)
% = [l1] u addAfterPowersOfTwo(l2l3..ln, v, c + 1), otherwise
% addAfterPowersOfTwo(l - list, V - number, C - number, R - list)
% -> flow model (i, i, i, o)
%
% mainSolveB(l1l2..ln, v) = addAfterPowersOfTwo(l1l2..ln, v, 1)
% mainSolveB(L - list, V - number, R - list) -> flow model(i, i, o)

isPowerOfTwo(1).
isPowerOfTwo(N):-
    N > 1,
    N mod 2 =:= 0,
    N2 is N // 2,
    isPowerOfTwo(N2).

addAfterPowersOfTwo([], _, _, []).
addAfterPowersOfTwo([H|T], V, C, [H,V|R]) :-
    isPowerOfTwo(C),
    C1 is C + 1,
    addAfterPowersOfTwo(T, V, C1, R).
addAfterPowersOfTwo([H|T], V, C, [H|R]) :-
    C1 is C + 1,
    addAfterPowersOfTwo(T, V, C1, R).

mainSolveB([H|T], V, R) :- addAfterPowersOfTwo([H|T], V, 1, R).

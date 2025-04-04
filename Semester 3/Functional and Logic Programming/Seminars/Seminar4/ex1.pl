% Given a list, for each element write a tuple of the elem and its freq
% in the list

% occ(e, l1..ln) = 0, if n = 0
%                  1 + occ(e, l2..ln), if l1 = e
%                  occ(e, l2..ln), if l1 != e

% [1, 2, 1, 3, 1, 3] => [[1, 3], [2, 1], [3, 2]]
%
% remove(e, l1..ln) = [], n = 0
%                     remove(l2..ln), l1 = e
%                     l1 U remove(l2..ln), if l1 != e

% gen_tuples(l1l2..ln) = [], if n = 0
%                        [l1, occ(l1, l1..ln)] U
%                gen_tuples(l2..ln), n>0


% the ex above is practice for practical exam (not backtrck)

% Backtracking exercise:
% Given a sequence a1..an composed of integer numbers, display all the
% subsequences which have a valley aspect (decreasing -> increasing)
% Ex. [5, 3, 4, 2, 7, 11, 1, 8, 6] -> some sols: [5, 4, 3, 11],
% [3,2,1,4,5,7,8] ...

% Taken from subsets.pl predicates:

subsets([], []).
subsets([H|T], [H|R]):-
    subsets(T, R).
subsets([_|T], R):-
    subsets(T, R).

insertEl(E, L, [E|L]).
insertEl(E, [H|T], [H|R]):-
    insertEl(E, T, R).

perm([], []).
perm([H|T], R):-
    perm(T, P),
    insertEl(H, P, R).

% f = 1 -> decreasing
% f = 0 -> increasing
% valley(l1..ln, f) = true, if n = 1 and f = 0
%                     valley(l2..ln, 1), l1 > l2 and f = 0
%                     valley(l2..ln, 0), l1 < l2 and (f = 0 or f = 1)
% mainValley(l1..ln) = valley(l1..ln, 1), l1 > l2
% oneSol(l1..ln) = r1..rm, if (perm(subset(l1..ln)) = r1..rm) and
%                              mainValley(r1..rm)
% main(l1..ln) = findall(oneSol(l1..ln))

% Implementations
% valley(L - list, F - flag)
% flow model: valley(i, i)

valley([_], 0).
valley([H1,H2|T], 1):-
    H1 > H2,
    valley([H2|T], 1).
valley([H1,H2|T], _):-
    H1 < H2,
    valley([H2|T], 0).

% mainValley(L - list)
% flow model: mainValley(i)

mainValley([H1,H2|T]):-
    H1 > H2,
    valley([H1,H2|T], 1).

% oneSol(IL - input list, OL - output list)
% flow model: oneSol(i, o)

oneSol(IL, _):-
    subsets(IL, SUB),
    perm(SUB, PERM),
    mainValley(PERM).

% main(L - list, R - result)
% flow model: main(i, o)

main(L, R, X):-
    findall(R, oneSol(L, R), X).


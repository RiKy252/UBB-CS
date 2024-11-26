% [[1, 2, 3], e, [4], 5, 6]
% H | T
% H = [1, 2, 3]       T = [e, [4], 5, 6]
% is_list(H)
% atomic(H) - number, symbol or empty list
% number(H)

% Remove sublists of a heterogeneus list.
% process(l1l2..ln) = [], if n = 0
%                     process(l2..ln), if l1 is a list
%                     l1 u process(l2..ln), if l1 is not a list
% process(L - list, R - list) -> (i, o)

process([], []).
process([H|T], R):-
    is_list(H), !,
    process(T, R).
process([H|T], [H|R]):-
    % atomic(H),
    % \+ is_list(H),
    % not(is_list(H)),
    process(T, R).

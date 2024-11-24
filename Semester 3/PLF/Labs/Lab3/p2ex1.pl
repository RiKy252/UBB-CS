% a)
% inList(e, l1l2..ln)
% : l1 = e u inList(l2l3..ln), if n > 0
% : false, if n = 0
%
% inList(E - element, L - list) -> fm(i, i).

inList(E, [E|_]).
inList(E, [_|T]):-
    inList(E, T).

% removeDuplicates(l1l2..ln)
% : [], if n = 0
% : removeDuplicates(l2l3..ln), if inList(l1, l2l3..ln)
% : l1 u removeDuplicates(l2l3..ln), otherwise
%
% removeDuplicates(L - list, R - result (list)) -> fm(i, o).

removeDuplicates([], []).
removeDuplicates([H|T], R):-
    inList(H, T),
    removeDuplicates(T, R).
removeDuplicates([H|T], [H|R]):-
    \+ inList(H, T),
    removeDuplicates(T, R).

% sortedInsertion(x, l1l2..ln)
% : [x], if n = 0
% : x u l1l2..ln, if x <= l1
% : sortedInsertion(l2l3..ln), if x > l1
%
% sortedInsertion(X - number, L - list, R - list) -> fm(i, i, o)

sortedInsertion(X, [], [X]).
sortedInsertion(X, [H|T], [X,H|T]):-
    X =< H.
sortedInsertion(X, [H|T], [H|R]):-
    X > H,
    sortedInsertion(X, T, R).

% insertionSort(l1l2..ln)
% : [], if n = 0
% : sortedInsertion(l1, insertionSort(l2l3..ln)), if n > 0
%
% insertionSort(L - list, R - list) -> fm(i, o).

insertionSort([], []).
insertionSort([H|T], R):-
    insertionSort(T, ST),
    sortedInsertion(H, ST, R).

% sortRemovingDuplicates(l1l2..ln)
% : [], if n = 0
% : removeDuplicates(l1l2..ln), insertionSort(l1l2..ln), if n > 0
%
% sortRemovingDuplicates(L - list, R - result) -> fm(i, o).

sortRemovingDuplicates([], []).
sortRemovingDuplicates([H|T], RF):-
    removeDuplicates([H|T], R),
    insertionSort(R, RF).

% b)
% sortHeterogeneousList(l1l2..ln)
% : [], if n = 0
% : sortRemovingDuplicates(l1), sortHeterogeneousList(l2l3..ln),
% if n > 0 and is_list(l1)
% : sortHeterogeneousList(l2l3..ln), if n > 0 and !is_list(l1)
%
% sortHeterogeneousList(L - list, R - result) -> fm(i, o).

sortHeterogeneousList([], []).
sortHeterogeneousList([H|T], [SH|ST]):-
    is_list(H),
    sortRemovingDuplicates(H, SH),
    sortHeterogeneousList(T, ST).
sortHeterogeneousList([H|T], [H|ST]):-
    \+ is_list(H),
    sortHeterogeneousList(T, ST).

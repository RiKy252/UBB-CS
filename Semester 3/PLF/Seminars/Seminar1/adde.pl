% Add an element at the end of a list.
% e=11, L=[1,2,3] => [1,2,3,11]

% Mathematical model
% adde(l1..ln, e) =
% {
%	[e] if l1..ln = NULL
%	{l1} u adde(l2..ln, e)
% }

adde([], E, [E]).
adde([H|T], E, [H|TR]):-
    adde(T, E, TR).

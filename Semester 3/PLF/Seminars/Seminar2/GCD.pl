gcd(A, B, R):-
    B > A, !,
    BN is B - A,
    gcd(A, BN, R).
gcd(A, B, R):-
    AN is A - B,
    gcd(B, AN, R).
gcd(A, B, R):-
    A =:= B,
    R = A.

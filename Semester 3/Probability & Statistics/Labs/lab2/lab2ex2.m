pkg load statistics
% a) X follows binomial(3, 0.5)
% (  0   1   2   3 ) - number of head appearance in 3 tosses
% ( 1/8 3/8 3/8 1/8) - probability

% b) see previous exercise

% c) P(X = 0) - def of the pdf in x = 0
p1 = binopdf(0, 3, 0.5);
% P(X != 1) = 1 - P(X = 1)
p2 = 1 - binopdf(1, 3, 0.5);
printf("P(X = 0) = %1.6f\n", p1);
printf("P(X != 1) = %1.6f\n", p2);

% d) P(X <= 2) - def of cdf in x = 2
p3 = binocdf(2, 3, 0.5);
% P(X < 2) = P(X <= 1)
p4 = binocdf(1, 3, 0.5);
printf("P(X <= 2) = %1.6f\n", p3);
printf("P(X < 2) = %1.6f\n", p4);

% e) P(X >= 1) = 1 - P(X < 1) = 1 - P(X <= 0)
p5 = 1 - binocdf(0, 3, 0.5);
% P(X > 1) = 1 - P(X <= 1)
p6 = 1 - binocdf(1, 3, 0.5);
printf("P(X >= 1) = %1.6f\n", p5);
printf("P(X > 1) = %1.6f\n", p6);

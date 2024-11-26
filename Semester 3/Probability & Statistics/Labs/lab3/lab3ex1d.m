pkg load statistics

% fisher distribution

% a)

m = input("Please enter the value for m: ");
n = input("Please enter the value for n: ");

res1 = fcdf(0, m, n); % res1 = P(X <= 0)
res2 = 1 - res1; % res2 = P(X >= 0)

printf("P(X <= 0) = %1.6f\n", res1);
printf("P(X >= 0) = %1.6f\n", res2);

% b)

res3 = fcdf(1, m, n) - fcdf(-1, m, n); % res3 = P(-1 <= X <= 1)
res4 = 1 - res3; % res4 = P(X <= -1 or X >= 1)

printf("P(-1 <= X <= 1) = %1.6f\n", res3);
printf("P(X <= -1 or X >= 1) = %1.6f\n", res4);

alpha = input("Please enter the value for alpha (0 < alpha < 1): ");
beta = input("Please enter the value for beta (0 < beta < 1): ");

% c)

res5 = finv(alpha, m, n); % res5 = xalpha

% d)

res6 = finv(1 - beta, m, n); % res6 = xbeta

printf("The quantile of order alpha is: %1.6f\n", res5);
printf("The quantile of order beta is: %1.6f\n", res6);

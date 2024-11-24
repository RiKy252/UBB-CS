pkg load statistics

% chi-squared distribution

% a)

n = input("Please enter the value for n: ");

res1 = chi2cdf(0, n); % res1 = P(X <= 0)
res2 = 1 - res1; % res2 = P(X >= 0)

printf("P(X <= 0) = %1.6f\n", res1);
printf("P(X >= 0) = %1.6f\n", res2);

% b)

res3 = chi2cdf(1, n) - chi2cdf(-1, n); % res3 = P(-1 <= X <= 1)
res4 = 1 - res3; % res4 = P(X <= -1 or X >= 1)

printf("P(-1 <= X <= 1) = %1.6f\n", res3);
printf("P(X <= -1 or X >= 1) = %1.6f\n", res4);

alpha = input("Please enter the value for alpha (0 < alpha < 1): ");
beta = input("Please enter the value for beta (0 < beta < 1): ");

% c)

res5 = chi2inv(alpha, n); % res5 = xalpha

% d)

res6 = chi2inv(1 - beta, n); % res6 = xbeta

printf("The quantile of order alpha is: %1.6f\n", res5);
printf("The quantile of order beta is: %1.6f\n", res6);

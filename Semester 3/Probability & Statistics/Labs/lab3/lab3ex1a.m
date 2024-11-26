pkg load statistics

% normal distribution

% a)

x = input("Please enter the value for the mean parameter: ");
y = input("Please enter the value for the standard deviation parameter: ");

res1 = normcdf(0, x, y); % res1 = P(X <= 0)
res2 = 1 - res1; % res2 = P(X >= 0)

printf("P(X <= 0) = %1.6f\n", res1);
printf("P(X >= 0) = %1.6f\n", res2);

% b)

res3 = normcdf(1, x, y) - normcdf(-1, x, y); % res3 = P(-1 <= X <= 1)
res4 = 1 - res3; % res4 = P(X <= -1 or X >= 1)

printf("P(-1 <= X <= 1) = %1.6f\n", res3);
printf("P(X <= -1 or X >= 1) = %1.6f\n", res4);

alpha = input("Please enter the value for alpha (0 < alpha < 1): ");
beta = input("Please enter the value for beta (0 < beta < 1): ");

% c)

res5 = norminv(alpha, x, y); % res5 = xalpha

% d)

res6 = norminv(1 - beta, x, y); % res6 = xbeta

printf("The quantile of order alpha is: %1.6f\n", res5);
printf("The quantile of order beta is: %1.6f\n", res6);

pkg load statistics

x = [22.4, 21.7, ...
           24.5, 23.4, ...
           21.6, 23.3, ...
           22.4, 21.6, ...
           24.8, 20.0];

y = [17.7, 14.8, ...
           19.6, 19.6, ...
           12.1, 14.8, ...
           15.4, 12.6, ...
           14.0, 12.2];

oneMinusAlpha = input("Please provide the confidence level: ");
alpha = 1 - oneMinusAlpha;

% a)

xbar = mean(x);
ybar = mean(y);

n1 = length(x);
n2 = length(y);

s1Squared = var(x);
s2Squared = var(y);
spSquared = ((n1 - 1) * s1Squared + (n2 - 1) * s2Squared) / (n1 + n2 - 2);

m1 = xbar - ybar - tinv(1 - alpha / 2, n1 + n2 - 2) * sqrt(spSquared) * sqrt((1 / n1) + (1 / n2));
m2 = xbar - ybar + tinv(1 - alpha / 2, n1 + n2 - 2) * sqrt(spSquared) * sqrt((1 / n1) + (1 / n2));

printf("The confidence interval for the difference of the true means when sigmas are equal is (%4.3f, %4.3f).\n", m1, m2);

% b)

c = (s1Squared / n1) / ((s1Squared / n1) + (s2Squared / n2));
oneOverN = (c^2 / (n1 - 1)) + ((1 - c)^2 / (n2 - 1))
n = 1 / oneOverN

m3 = xbar - ybar - tinv(1 - alpha / 2, n) * sqrt((s1Squared / n1) + (s2Squared / n2));
m4 = xbar - ybar + tinv(1 - alpha / 2, n) * sqrt((s1Squared / n1) + (s2Squared / n2));

printf("The confidence interval for the difference of the true means when sigmas are not equal is (%4.3f, %4.3f).\n", m3, m4);

% c)

m5 = (1 / finv(1 - alpha / 2, n1 - 1, n2 - 1)) * (s1Squared / s2Squared);
m6 = (1 / finv(alpha / 2, n1 - 1, n2 - 1)) * (s1Squared / s2Squared);

printf("The confidence interval for the ratio of the variances is: (%4.3f, %4.3f).\n", m5, m6);


pkg load statistics

% past assumptions
% vs. present assumptions

% statistical parameter = some known value <- null hyp - what was
%                                                        previously known
% statistical parameter > < or different from the same known
% value as above <- alternative hyp

% statistical parameters that can be analysed
% a pop mean, a pop variance, ratio of two pop variances,
% and difference of 2 pop means

X = [7, 7, 4, 5, 9, 9, ...
     4, 12, 8, 1, 8, 7, ...
     3, 13, 2, 1, 17, 7, ...
     12, 5, 6, 2, 1, 13, ...
     14, 10, 2, 4, 9, 11, ...
     3, 5, 12, 6, 10, 7];

n = length(X);
alpha = input("Please give the significance level: ");

% a)

% H0: m >= 8.5 <- null hypothesis - system is efficient
% H1: m < 8.5 <- alternative hypothesis - system is not efficient

% this is a left-tailed Z-test,
% for the pop mean when sigma is known

sigma = 5;
m0 = 8.5; % observed value of the mean

% h is used for rejection
% p = p-value (probability)
% ci = confidence interval
% zobs = z-val = observed value of the statistic
[h, p, ci, zobs] = ztest(X, m0, sigma, "alpha", alpha, "tail", "left");

% construct the rejection region for this left-tail z-test
z = norminv(alpha, 0, 1);
RR = [-inf z];

if h == 1 % if h = 1 reject H0 and if h = 0 do not reject H0
  printf("The value of h is %d. The null hypothesis is rejected.\n", h);
  printf("The data suggests that the standard is not met.\n");
else
  printf("The value of h is %d. The null hypothesis is not rejected.\n", h);
  printf("The data suggests that the standard is met.\n");
endif

printf("The rejection region for this test is (%4.3f, %4.3f).\n", RR);
printf("The observed value of the test statistic is %4.3f.\n", zobs);
printf("The P-value of our test is %4.3f.\n", p);

% b) ttest -> you get the observed value of the test statistic if
% you call stats.tstat

[h, p, ci, stats] = ttest(X, m0, "alpha", alpha, "tail", "left");

z = tinv(alpha, n - 1);
RR = [-inf z];

if h == 1
  printf("The value of h is %d. The null hypothesis is rejected. Standard is not met\n", h);
else
  printf("The value of h is %d. The null hypothesis is not rejected. Standard is met\n", h);
endif

printf("The rejection region for this t-test is (%4.3f, %4.3f).\n", RR);
printf("The observed value of the test statistic is %4.3f.\n", stats.tstat);
printf("The P-value of our test is %4.3f.\n", p);

printf("\n\n");

% 2a) vartest2 -> variances are equal or are different
% 2b) you choose in the
% cheatsheet the situation depending on a) ttest2

clear all;

alpha = input("Please give the significance level: ");
premium = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
regular = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

n1 = length(premium);
n2 = length(regular);

% a)
% H0: sigma1 = sigma2 (variances are equal)
% H1: sigma1 != sigma2 (variances are not equal)
% two-tailed test (default value for tail)

[h, pval, ci, stats] = vartest2(premium, regular, "alpha", alpha);

if h == 1
  printf("The null hypothesis is rejected: variances are not equal.\n");
else
  printf("The null hypothesis is not rejected: variances are equal.\n");
endif

% Constructing rejection region:

z2_lower = finv(alpha / 2, n1 - 1, n2 - 1);
z2_upper = finv(1 - alpha / 2, n1 - 1, n2 - 1);

RR2 = [z2_lower z2_upper];

printf("The rejection region for this vartest2 is (%4.3f, %4.3f).\n", RR2);
printf("The observed value of the vartest2 statistic is %4.3f.\n", stats.fstat);
printf("The P-value of our test is %4.3f.\n", pval);

% b)

% H0: miu1 = miu2
% H1: miu1 > miu2 -> right-tailed test

[h1, pval1, ci1, stats1] = ttest2(premium, regular, "alpha", alpha, "tail", "right", "vartype", "equal");

% Rejection region (right-tailed test)

z3 = tinv(1 - alpha, stats1.df);
RR3 = [z3 inf];

if h1 == 0
  printf("Gas mileage DO NOT SEEM to be higher on average when using premium gasoline!\n");
else
  printf("Gas mileage SEEM to be higher on average when using premium gasoline!\n");
endif

printf("The rejection region for this ttest2 is (%4.3f, %4.3f).\n", RR3);
printf("The observed value of the ttest2 statistic is %4.3f.\n", stats1.tstat);
printf("The P-value of our test is %4.3f.\n", pval1);


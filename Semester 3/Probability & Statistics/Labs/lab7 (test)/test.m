pkg load statistics

steel = [4.6, 0.7, 4.2, 1.9, 4.8, 6.1, 4.7, 5.5, 5.4];
glass = [2.5, 1.3, 2.0, 1.8, 2.7, 3.2, 3.0, 3.5, 3.4];

n1 = length(steel);
n2 = length(glass);

% a) 1% significance level => alpha = 0.01

alpha = 0.01;

% We are using the point 4 in the tests.pdf file with vartest2 because
% it performs a two sample F test for equal variances

% to check if population variances differ or not we use the following
% hypothesis

% H0: sigma1 = sigma2 (null hyptohesis -> variances are equal)
% H1: sigma1 != sigma2 (alt hyptohesis -> variances differ)

% this is two-tailed test because we have '!=' sign

[h, pval, ci, stats] = vartest2(steel, glass, "alpha", alpha, "tail", "both");

if h == 0
  printf("At significance level 1%%, the null hypothesis is not rejected. The variances DO NOT differ!\n");
else
  printf("At significance level 1%%, the null hypothesis is rejected. The variances DIFFER!\n");
endif

% Rejection region for a two-tailed test

q1 = finv(alpha / 2, n1 - 1, n2 - 1);
q2 = finv(1 - alpha / 2, n1 - 1, n2 - 1);

printf('Observed value for vartest2 is %1.4f\n', stats.fstat);
printf('P-value for vartest2 is %1.4f\n', pval);
printf('Rejection region R for vartest2 is (-inf, %3.4f) U (%3.4f, inf)\n', q1, q2);
printf("\n");

% b) 99% confidence interval for the diff of the means
% 100(1 - alpha)% confidence interval => alpha = 0.01

% Alpha is the same, so we know rom a) that the variances are equal
% we are using from the tests.pdf file the point 3, line 2
% for witch we need ttest2

% H0: miu1 = miu2 (null hypothesis => average heat is equal)
% H1: miu1 != miu2 (alt hypothesis => average heat differ)

% two-tailed test
% we use the ttest for obtaining the confidence interval

[h1, pval1, ci1, stats1] = ttest2(steel, glass, "alpha", alpha, "vartype", "equal");

if h1 == 0
  printf("At significance level 1%%, the null hypothesis is not rejected. The means DO NOT differ!\n");
else
  printf("At significance level 1%%, the null hypothesis is rejected. The means DIFFER!\n");
endif

printf("The 99%% confidence interval for the difference of the average heat loss is: (%4.3f, %4.3f)\n", ci1);


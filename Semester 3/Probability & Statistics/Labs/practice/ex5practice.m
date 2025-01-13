pkg load statistics

standard = [46, 37, 39, 48, 47, 44, 35, 31, 44, 37];
new = [35, 33, 31, 35, 34, 30, 27, 32, 31, 31];
n1 = length(standard);
n2 = length(new);

% a)

% H0: sigma1 = sigma2
% H1: sigma1 != sigma2 (two-tailed test)

alpha = 0.05;

[h, pval, ci, stats] = vartest2(standard, new, "alpha", alpha, "tail", "both");

if h == 0
  printf("At 0.05 significance level, variances are equal!\n");
else
  printf("At 0.05 significance level, variances are NOT equal!\n");
endif

% Rejection region: two-tailed test

lower_region = finv(alpha / 2, n1 - 1, n2 - 1);
higher_region = finv(1 - alpha / 2, n1 - 1, n2 - 1);
RR = [lower_region higher_region];

printf("The rejection region for this vartest2 is (%4.3f, %4.3f).\n", RR);
printf("The observed value of the vartest2 statistic is %4.3f.\n", stats.fstat);
printf("The P-value of our vartest2 is %4.3f.\n", pval);

% b)


% H0: miu1 = miu2
% H1: miu1 != miu2 (two-tailed test)

[h1, pval1, ci1, stats1] = ttest2(standard, new, "alpha", alpha, "tail", "both", "vartype", "unequal");

% Rejection region: two-tailed test

lower_region1 = tinv(alpha / 2, stats1.df);
higher_region1 = tinv(1 - alpha / 2, stats1.df);
RR1 = [lower_region1 higher_region1];


if h1 == 0
  printf("At 0.05 significance level, the average assembling times are equal!\n");
else
  printf("At 0.05 significance level, the average assembling times are NOT equal!\n");
endif

printf("The rejection region for this ttest2 is (%4.3f, %4.3f)\n", RR1);
printf("The observed value of the ttest2 statistic is %4.3f.\n", stats1.tstat);
printf("The P-value of our ttest2 is %4.3f.\n", pval1);
printf("0.95 confidence interval for the difference: (%4.3f, %4.3f)\n", ci1);

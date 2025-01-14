pkg load statistics

x = [1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 1004, 1030, 1015, 995, 1023];
y = [1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010, 975];
n1 = length(x);
n2 = length(y);

% a)

alpha = 0.05; % significance level

% H0: sigma1 = sigma2
% H1: sigma1 != sigma2 (two-tailed test)

% we use vartest2 for testing the variances of two samples

[h, pval, ci, stats] = vartest2(x, y, "alpha", alpha, "tail", "both");

if h == 0
  printf("At the 5%% significance level, population variances are EQUAL\n");
else
  printf("At the 5%% significance level, population variances are NOT EQUAL\n");
endif

% Rejection region for two-tailed test

lower_region = finv(alpha / 2, stats.df1, stats.df2);
higher_region = finv(1 - alpha / 2, stats.df1, stats.df2);
RR = [lower_region higher_region];

printf("The rejection region for this vartest2 is (%4.3f, %4.3f).\n", RR);
printf("The observed value of the vartest2 statistic is %4.3f.\n", stats.fstat);
printf("The P-value of our vartest2 is %4.3f.\n", pval);

% b)

% H0: miu1 = miu2 (null hypothesis => mean weights are the same)
% H1: miu1 != miu2 (alt hypothesis => mean weights differ)

% we use a two-tailed ttest2 for testing the means

[h1, pval1, ci1, stats1] = ttest2(x, y, "alpha", alpha);

if h1 == 0
  printf("The mean weights are the SAME\n");
else
  printf("The mean weight are NOT the SAME\n");
endif

% Rejection region

lower_region1 = tinv(alpha / 2, stats1.df);
higher_region1 = tinv(1 - alpha / 2, stats1.df);
RR1 = [lower_region1 higher_region1];

printf("The rejection region for this ttest2 is (%4.3f, %4.3f).\n", RR1);
printf("The observed value of the ttest2 statistic is %4.3f.\n", stats1.tstat);
printf("The P-value of our ttest2 is %4.3f.\n", pval1);

printf("\nThe answer for the problem is: \na)At 5%% significance level the population variances are EQUAL\nb)At 5%% significance level the population means are the SAME, so both suppliers are equally reliable\n");


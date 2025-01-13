pkg load statistics

X = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, ...
  1.76, 3.82, 2.42, 2.96];

% a)

% H0: m0 = 0
% H1: m0 != 0 (two-tailed test)
% we are interested in confidence interval so hyp does not matter

alpha = 0.05; % 100(1 - alpha) confidence interval
m0 = 0;
[h, pval, ci, stats] = ttest(X, m0, "alpha", alpha);

printf("The 0.95 confidence interval is: (%4.3f, %4.3f)\n", ci);

% b)

% H0: m0 >= 3
% H1: m0 < 3 (left tailed test)

alpha1 = 0.01; % significance level
m1 = 3;

[h1, pval1, ci1, stats1] = ttest(X, m1, "alpha", alpha1, "tail", "left");

if h1 == 0
  printf("On average with significance level = 0.01, the particles are NOT smaller than 3!\n");
else
  printf("On average with significance level = 0.01, the particles ARE smaller than 3!\n");
endif

% Rejection region

z = tinv(alpha, stats1.df);
RR = [-inf z];

printf("The rejection region for this ttest is (%4.3f, %4.3f)\n", RR);
printf("The observed value of the ttest statistic is %4.3f.\n", stats1.tstat);
printf("The P-value of our ttest is %4.3f.\n", pval1);


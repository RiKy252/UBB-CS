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

% H0: m = 8.5 <- null hypothesis - system is efficient
% H1: m < 8.5 <- alternative hypothesis - system is not efficient
% this is a left-tailed Z-test,
% for the pop mean when sigma is known

sigma = 5;
m0 = 8.5; % observed value of the mean

[h, p, ci, zobs] = ztest(X, m0, sigma, "alpha", alpha, "tail", "left");

% construct the rejection region for this left-tail test
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

% 2a) vartest2 -> variances are equal or are different
% 2b) you choose in the
% cheatsheet the situation depending on a) ttest2


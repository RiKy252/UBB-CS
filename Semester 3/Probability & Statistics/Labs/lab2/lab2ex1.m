pkg load statistics

% pdf -> f(x) = P(X = x)
% cdf -> F(x) = P(X <= x)

n = input("Give number of trials: n = "); % n - positive integer
p = input("Give probabily of success: p = "); % 0 <= p <= 1
x = 0:n;
px = binopdf(x, n, p);
clf
plot(x, px, '*')
hold on
xx = 0:0.01:n;
cx = binocdf(xx, n, p);
plot(xx, cx, 'r')
legend('pdf', 'cdf');

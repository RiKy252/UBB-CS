pkg load statistics

n = input("Enter the value of n >= 30: ");
p = input("Enter the value of p <= 0.05: ");
lambda = n * p;
k = 0:n
bp = binopdf(k, n, p)
pp = poisspdf(k, lambda)

plot(k, bp, '.');
hold on
plot(k, pp, '__');

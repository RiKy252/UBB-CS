pkg load statistics
clear all
p = input("Please enter the probability: "); % p = 0.4
n = input("Please enter the number of trials: "); % n = 20
N = input("Please enter the number of simulations: "); % N = 1000
U = rand(n, N);
X = sum(U < p);
k = 0:n;
px = binopdf(k, n, p);
U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq = n_X / N;
clf
plot(U_X, rel_freq, "*", k, px, "ro")
legend("sim", "bino")

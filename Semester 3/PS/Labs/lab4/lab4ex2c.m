pkg load statistics
clear all
p = input("Please enter the probability: "); % p = 0.4
N = input("Please enter the number of simulations: "); % N = 1000
X = zeros(1, N);
for i = 1:N
  X(i) = 0;
  while rand >= p
    X(i) = X(i) + 1;
  endwhile
endfor
k = 0:20;
px = geopdf(k, p);
U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq = n_X / N;
clf
plot(U_X, rel_freq, "*", k, px, "ro")
legend("sim", "geo")

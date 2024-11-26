pkg load statistics
N = input("Give the number of simulations N = ");
U = rand(3, N);
Y = (U < 0.5); % 1 - heads, 0 - tails
X = sum(Y); % sum each column
clf
hist(X)

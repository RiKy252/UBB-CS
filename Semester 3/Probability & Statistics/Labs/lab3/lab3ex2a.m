pkg load statistics

p = input("Enter the value of p (0.05 <= p <= 0.95): ");

for n = 1:3:100;
  k = 0:n
  pb = binopdf(k, n, p);
  plot(k, pb, '*')
  pause(0.5);
 endfor


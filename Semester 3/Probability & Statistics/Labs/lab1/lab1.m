printf("Exercise 1.\n");
A = [1 0 -2 ; 2 1 3 ; 0 1 0];
B = [2 1 1 ; 1 0 -1; 1 1 0];
C = A - B
D = A*B
E = A.*B % . -> element wise operation
printf("Exercise 2.\n");

x = 0:0.01:3; % [0, 3], with 0.01 step

y1 = x.^5/10;
y2 = x.*sin(x);
y3 = x.*cos(x);

% x coordinate, y coordinate, color (options)
plot(x, y1, "r", x, y2, "b", x, y3, "y");
title("My graphs");
legend("x^5/10", "xsin(x)", "xcos(x)");

figure; % creates a new window

% subplot(n, m, p)
% n = nr rows
% m = nr columns
% p = which one to "activate"

subplot(3, 1, 1);
plot(x, y1, "r");
legend("x^5/10");

subplot(3, 1, 2);
plot(x, y2, "b");
legend("xsin(x)");

subplot(3, 1, 3);
plot(x, y3, "y");
legend("xcos(x)");

pkg load statistics

x = [20, 20, ...
    21, ...
    22, 22, 22, ...
    23, 23, 23, 23, 23, 23, ...
    24, 24, 24, 24, 24, ...
    25, 25, 25, 25, 25, 25, 25, 25, 25, ...
    26, 26, ...
    27, 27]

y = [75, 75, 75, ...
     76, 76, ...
     77, 77, ...
     78, 78, 78, 78, 78, ...
     79, 79, 79, 79, 79, 79, 79, 79, ...
     80, 80, 80, 80, 80, 80, 80, 80, ...
     81, 82]

% a)

xbar = mean(x)
ybar = mean(y)

% b)

s1 = var(x)
s2 = var(y)

% c)

cov(x, y)

% d)

corrcoef(x, y)

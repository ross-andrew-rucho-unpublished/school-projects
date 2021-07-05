% Ross Rucho
% ratrucho@gmail.com
% 05/26/2020
% HW2-Problem5.m
%
%{
In Part 1, this script implements Newton's method for calculating the root
of a function and uses it to calculate the root for the following system:

F(x1, x2) = [f1; f2] = [0; 0] where:
    f1 = 4*(x1).^2 + (x2).^2 - 4
    f2 = x1 + x2 - sin(x1 - x2)
    with initial guess [x1; x2] = [1; 0]

In Part 2, this script solves the same system as in part 1, but instead
uses the built-in Matlab function fsovle to compute the root. 

%}

%% Part 1
% Declare the initial guess
x0 = [1; 0];

% Declare the following symbols to represent symbolic variables and
% functions
syms x1 x2 f1(x1, x2) f2(x1, x2);
F(x1, x2) = [(4*(x1).^2) + ((x2).^2) - 4; x1 + x2 - sin(x1 - x2)];

% Define the symbolic functions
f1(x1, x2) = (4*(x1).^2) + ((x2).^2) - 4;
f2(x1, x2) = x1 + x2 - sin(x1 - x2);

% Compute the Jacobian symbolically (analytically) using Matlab
J(x1, x2) = [diff( f1(x1, x2), x1 ), diff( f1(x1, x2), x2 ); diff( f2(x1, x2), x1 ), diff( f2(x1, x2), x2 )];

% Define the initial value and the iterator variable
x = x0;
n = 0;

% Iteratively compute the root for the system
while norm( double(F(x(1), x(2))) ) > 1.0e-13 || n > 1000
    x = x - double(J(x(1), x(2)))\double(F(x(1), x(2))); % Calculate the updated root
    n = n + 1;
end

disp(n);
disp(x);


%% Part 2
% Compute the root using fsolve
fun = @HW2_Problem5_Function;
root = fsolve(fun ,x0);

disp(root);


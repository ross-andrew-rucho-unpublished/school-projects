% Ross Rucho
% ratrucho@gmail.com
% 05/26/2020
% HW2-Problem3.m
%
%{
All parts of this script utilize the following system:

f(x) = exp[x] - 3*(x).^2 = 0

In Part 1, this script uses the bisection method to calculate the root of
the system listed above.

In Part 2, this script uses Newton's method to calculate the root of the
system listed above. 

In Part 3, this script uses the secant method to calculate the root of the
system listed above. 

From left to right (Figure 1 through Figure 3) the images represent the
error after each iteration for each of the three methods

%}

%% Preliminary
% Define anonymous functions to be equal to the system and its derivative
f = @(x) exp(x) - 3*(x).^2;
fp1 = @(x) exp(x) - 6*x;
XinitialLow = 0;
XinitialHigh = 1;

%% Part 1
% Define local variables
x0 = XinitialLow;
x1 = XinitialHigh;
error1(1) = abs( x1 - x0 );
n = 1;

while x1 - x0 > 1.0e-13
    % Compute the updated root and iteration value
    x = (x0+x1)/2;
    n = n+1;
    
    % Compute the updated error value
    error1(n) = abs( x1 - x0 );
    
    % Compute the new x0 and x1 values
    if f(x)*f(x0) < 0
        x1 = x;
    else
        x0 = x;
    end
end

disp(x);
figure(1);
plot( log(error1(4:44)) );
%plot(error1);

%% Part 2
% Define local variables
x = XinitialLow;
error2(1) = abs( f(x) );
n = 1;

while abs( f(x) ) > 1.0e-13
    % Compute the updated root and iteration value
    x = x - ( f(x) )/( fp1(x) );
    n = n+1;
    
    error2(n) = abs( f(x) );
end

disp(x0);
figure(2);
plot( error2(2:4)./error2(1:3).^2 );
%plot(error2);

%% Part 3
% Define local variables
x0 = XinitialLow;
x1 = XinitialHigh;
error3(1) = abs( f(x1) );
n = 1;

while abs( f(x1) ) > 1.0e-13
    % Compute the updated root and iteration value
    Xtemp = x1 - ( f(x1)*(x1-x0) )/( f(x1)-f(x0) );
    n = n+1;
    
    error3(n) = abs( f(Xtemp) );
    
    % Update the solution
    x0 = x1;
    x1 = Xtemp;
end

disp(x1);
figure(3);
plot( error3(2:7)./error3(1:6).^(1.62) );
%plot(error3);

% Ross Rucho
% ratrucho@gmail.com
% 2/6/2018
% assignment1.m
%
% This script creates and displays and image;
% Second, it calculates the x and y partial derivatives for
% the previous image
% Third, it specifies a 2D unit vector that is at a maximum
% when dotted with the gradient of the previous image
% Fourth, it specifies another 2D unit vector in the same
% quadrant as the first but with an angle of pi/6 with the
% horizontal.

%% Declarations
clear
close all

% Declare and initialize the array to 0
I(128,128) = 0;

% Loop to create the image array
for j = 1:size(I,1)
    for k = 1:size(I,2)
        if j > k 
            I(j,k) = 1000;
        end
    end
end

% Declare and initialize the partial derivative arrays
I_x = I;
I_y = I;

%% Calculations
% Calculate partial derivatives for non edge
for j = (2:size(I,1)-1)
    for k = (2:size(I,2)-1)
        I_x(j,k) = (I(j,k-1) - I(j,k+1))/2;
        I_y(j,k) = (I(j+1,k) - I(j-1,k))/2;
    end
end

% Handle edge cases
I_x(:,[1,size(I,2)]) = 0;
I_x([1,size(I,1)],:) = 0;
I_y(:,[1,size(I,2)]) = 0;
I_y([1,size(I,1)],:) = 0;

% Specify a unit directional vector u
u = [1,1]*sqrt(2)/2;

% Calculate the Gradient dotted with u
A = I_x*u(1) + I_y*u(2);

% Calculate three values of A
res1 = [A(64,64),A(63,64),A(64,62)];

% Specify a unit directional vector v
v = [sqrt(3), 1]/2;

% Calculate the Gradient dotted with v
B = I_x*v(1) + I_y*v(2);

% Calculate three values of B
res2 = [B(64,64),B(63,64),B(64,62)];

% Compare res1 with res2
C = ['<','=','='];


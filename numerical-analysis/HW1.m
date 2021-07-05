% Ross Rucho
% ratrucho@gmail.com
% 05/21/2020
% HW1.m
%
%{
This function accurately computes the two roots using the correct quadratic
formula depending on the sign of b
This function correctly takes into account the underlying imprecision of
computing
There is an implicit assumption that b^2 is not approximately equal to
4*a*c
%}

function [root1, root2] = HW1( a, b, c )
    % Calculate and store the value under the radical for code clarity
    rad = b^2 - 4*a*c;

    % Determine the correct formula to use 
    if (b < 0)
        root1 = (-b + sqrt(rad))/(2*a);
        root2 = (2*c)/(-b + sqrt(rad));
    else
        root1 = (2*c)/(-b - sqrt(rad));
        root2 = (-b - sqrt(rad))/(2*a);
    end

end

% Ross Rucho
% ratrucho@gmail.com
% 05/26/2020
% HW2-Problem5-Function.m
%
%{
This function defines the following system:

F(x) = [F(1); F(2)] = [0; 0] where:
    F(1) = 4*(x(1)).^2 + (x(2)).^2 - 4
    F(2) = x(1) + x(2) - sin(x(1) - x(2))

%}

function F = HW2_Problem5_Function(x)
    F(1) = 4*(x(1)).^2 + (x(2)).^2 - 4;
    F(2) = x(1) + x(2) - sin(x(1) - x(2));
end

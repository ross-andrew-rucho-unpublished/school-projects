% Ross Rucho
% ratrucho@gmail.com
% 06/11/2020
% HW5.m
%
%{
This function computes a set C from two given sets A and B. C has elements
that are defined to be the sum of any two elements from A and B. Therefore,
for all elements in A and for all elements in B, perform a_j + b_k to
compute c_i. Additionally, this function returns the number of times that
c_i is computed from elements a_j + b_k.

These operations are performed by assuming that A and B take the form of
polynomials with coefficients equal to 1 if the exponent is equal to
one of the elements in the set and coefficients equal to 0 otherwise. Then,
their multiplication A*B produces a polynomial C where each exponent on a
term corresponds to a c_i value and each coefficient corresponds to the
number of times that the exponent (i.e., c_i) was computed from a unique
(a_j, b_k) pair.

Finally, to implement this algorithm efficiently, the Fast Fourier
Transform is used to compute the polynomial multiplication in O(n * log(n))
time. 

Input:
A - a list of n elements that represent the n elements in the set A
B - a list of n elements that represent the n elements in the set B

Output:
C - a list of n elements that represent the unique sums from the elements
    in A and B
gamma - a list of the coefficients of the polynomial. Each index represents
        the polynomial degree and the value at that index is the
        coefficient associated with that exponent of the polynomial. For
        example, if the element at the 5th index of gamma is a 3, then the
        term with exponent to the 4th power in the polynomial has a
        coefficient equal to 3. 
%}

function [ C, gamma ] = HW5( A, B )
    % The vectors of length 10n + 1 that correspond to the coefficients of the
    % polynomials A and B
    A_modified = zeros(10*numel(A) + 1, 1);
    B_modified = zeros(10*numel(B) + 1, 1);
    
    for i = 1:numel(A)
        A_modified(A(i) + 1) = 1;
    end
    
    for i = 1:numel(B)
        B_modified(B(i) + 1) = 1;
    end
    
    % Compute the transformation to convert the polynomial coefficient
    % representation into the function value representation
    A_transform = fft(A_modified);
    B_transform = fft(B_modified);
    
    % Perform the element by element multiplication of the function values
    C_transform = A_transform.*B_transform;
    
    % Compute the transformation to convert the function value 
    % representation back into the polynomial coefficient representation
    gamma = cast(ifft(C_transform), 'int64');
    
    % Use the index of the nonzero coefficients of the solution polynomial
    % to compute the unique sums in the set C
    k = 1;
    for i=1:numel(gamma)
        if gamma(i) ~= 0
            C(k) = i - 1;
            k = k + 1;
        end
    end
    
end

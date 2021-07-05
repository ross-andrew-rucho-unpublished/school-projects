% Ross Rucho
% ratrucho@gmail.com
% 11/05/2019
% getShapeVariations.m
%
% This function computes the principal shape variation axes in descending
% order of contribution to the total variation
%
% Input: A vector of pre-aligned point sets
%        The mean point set of the pre-aligned point sets
%
% Output: Matrix of sorted column eigenvectors (descending)
%         Row of sorted eigenvalues (descending)

function [sortedEigenVectors, sortedEigenValues] = getShapeVariations( setOfPointSets, meanPointSet )
    % Declare and initialize local variables
    numOfPointSets = size( setOfPointSets, 1 );
    numOfPoints = size( setOfPointSets, 2 );
    dimensionOfPoints = size( setOfPointSets, 3 );
    pointSetShape = [numOfPoints, dimensionOfPoints];
    
    covarianceMatrix = zeros( numOfPoints.*dimensionOfPoints, numOfPoints.*dimensionOfPoints );

    % Compute deviations from the mean and the Covariance matrix
    for i = 1:numOfPointSets
        differencePointSet = transpose(reshape( setOfPointSets(i,:,:), pointSetShape ) - meanPointSet);
        meanDeviation = differencePointSet(:);
        covarianceMatrix = covarianceMatrix + meanDeviation*(meanDeviation');
    end
   
    covarianceMatrix = covarianceMatrix.*( 1/numOfPointSets );
    
    % Compute the eigenvectors and corresponding eigenvalues
    [eigenVectors, eigenValues] = eig(covarianceMatrix);
    
    % Sort the eigenvectors according to largest eigenvalue
    eigValues = sum(eigenValues, 2);
    combinedEigen = [eigValues, eigenVectors'];
    sortedEigen = sortrows(combinedEigen, 'descend');
    sortedEigenVectors = sortedEigen(:,2:end)';
    sortedEigenValues = sortedEigen(:,1)';
end

% Ross Rucho
% ratrucho@gmail.com
% 11/05/2019
% getMeanPointSet.m
%
% This function computes a mean point set from a set of point sets by
% choosing an initialization point set and calculating an aligned average  
%
% Input: A vector of point sets
%
% Output: A point set

function meanPointSet = getMeanPointSet( setOfPointSets )
    % Declare and initialize local variables
    initialPointSet = 1;
    numOfPointSets = size( setOfPointSets, 1 );
    numOfPoints = size( setOfPointSets, 2 );
    dimensionOfPoints = size( setOfPointSets, 3 );
    pointSetShape = [numOfPoints, dimensionOfPoints];
    
    setOfAlignedPointSets = zeros( numOfPointSets, numOfPoints , dimensionOfPoints );
    meanPointSet = zeros( numOfPoints , dimensionOfPoints );

    % Update the mean point set to be the first point set
    tempMeanPointSet = reshape( setOfPointSets(initialPointSet,:,:), pointSetShape );

    % Loop until the sum of squared differences between updates converges
    while sum( sqrt( sum( (meanPointSet - tempMeanPointSet).^2, 2 ) ) ) > 0.0001
        % Store the updated mean point set
        meanPointSet = tempMeanPointSet;
        
        % Align all of the point sets to the mean point set
        for i = 1:numOfPointSets
            [setOfAlignedPointSets(i,:,:), ~] = getAlignedPts( meanPointSet, reshape( setOfPointSets(i,:,:), pointSetShape ) );
        end

        % Calculate the updated mean point set
        tempMeanPointSet = ( 1/numOfPointSets ).*reshape( sum( setOfAlignedPointSets, 1 ), pointSetShape );

        % Align the updated mean point set to the first point set
        [tempMeanPointSet, ~] = getAlignedPts( reshape( setOfPointSets(initialPointSet,:,:), pointSetShape ), tempMeanPointSet );
    end
end

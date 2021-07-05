% Ross Rucho
% ratrucho@gmail.com
% 11/05/2019
% homework3.m
%
% This program reads in a set of point sets and performs image registration
% as well as performing principal component analysis in order to construct
% a point distributiom model

%% Declarations
clear
close all


%% A) Compute mean point set and align point sets to the mean

% Declare and Initialize local variables
numOfPointSets = 21;
numOfPoints = 68;
dimensionOfPoints = 2;
pointSetShape = [numOfPoints, dimensionOfPoints];
setOfPointSets = zeros( numOfPointSets, numOfPoints, dimensionOfPoints );
setOfAlignedPointSets = zeros( numOfPointSets, numOfPoints , dimensionOfPoints );

% Populate data structure with point sets
setOfPointSets(1,:,:) = readPoints('dat/107_0764.pts');
setOfPointSets(2,:,:) = readPoints('dat/107_0766.pts');
setOfPointSets(3,:,:) = readPoints('dat/107_0779.pts');
setOfPointSets(4,:,:) = readPoints('dat/107_0780.pts');
setOfPointSets(5,:,:) = readPoints('dat/107_0781.pts');
setOfPointSets(6,:,:) = readPoints('dat/107_0782.pts');
setOfPointSets(7,:,:) = readPoints('dat/107_0784.pts');
setOfPointSets(8,:,:) = readPoints('dat/107_0785.pts');
setOfPointSets(9,:,:) = readPoints('dat/107_0786.pts');
setOfPointSets(10,:,:) = readPoints('dat/107_0787.pts');
setOfPointSets(11,:,:) = readPoints('dat/107_0788.pts');
setOfPointSets(12,:,:) = readPoints('dat/107_0789.pts');
setOfPointSets(13,:,:) = readPoints('dat/107_0790.pts');
setOfPointSets(14,:,:) = readPoints('dat/107_0791.pts');
setOfPointSets(15,:,:) = readPoints('dat/107_0792.pts');
setOfPointSets(16,:,:) = readPoints('dat/107_0793.pts');
setOfPointSets(17,:,:) = readPoints('dat/107_0794.pts');
setOfPointSets(18,:,:) = readPoints('dat/107_0795.pts');
setOfPointSets(19,:,:) = readPoints('dat/107_0798.pts');
setOfPointSets(20,:,:) = readPoints('dat/107_0799.pts');
setOfPointSets(21,:,:) = readPoints('dat/107_0800.pts');

% Compute the mean point set
meanPointSet = getMeanPointSet(setOfPointSets);

% Align point sets to the mean
for i = 1:numOfPointSets
    [setOfAlignedPointSets(i,:,:), ~] = getAlignedPts( meanPointSet, reshape( setOfPointSets(i,:,:), pointSetShape ) );
end

% Display all of the aligned point sets
figure
for i = 1:numOfPointSets
  drawFaceParts( -reshape( setOfAlignedPointSets(i,:,:), pointSetShape ), 'k-' );
end

% Display the mean point set in red 
drawFaceParts(-meanPointSet, 'r-');

% Modify the display format
axis off
axis equal

%% B)

% Compute the principal axes of shape variation
[eigenVectors, eigenValues] = getShapeVariations(setOfAlignedPointSets, meanPointSet);

% Extract the three most significant variations (first three)
principalVar1 = eigenVectors(:,1);
principalVar2 = eigenVectors(:,2);
principalVar3 = eigenVectors(:,3);


% Eigenvector corresponding to the largest variation
figure
for i = -2:2
    drawFaceParts(-( meanPointSet + [principalVar1(1:2:end-1), principalVar1(2:2:end)].*( i*sqrt( eigenValues(1) ) ) ), 'k-');
    pause(2);
end

% Modify the display format
axis off
axis equal

% Eigen vector corresponding to the second largest variation
figure
for i = -2:2
    drawFaceParts(-( meanPointSet + [principalVar2(1:2:end-1), principalVar2(2:2:end)].*( i*sqrt( eigenValues(2) ) ) ), 'k-');
    pause(2);
end

% Modify the display format
axis off
axis equal

% Eigenvector corresponding to the third largest variation
figure
for i = -2:2
    drawFaceParts(-( meanPointSet + [principalVar3(1:2:end-1), principalVar3(2:2:end)].*( i*sqrt( eigenValues(3) ) ) ), 'k-');
    pause(2);
end

% Modify the display format
axis off
axis equal


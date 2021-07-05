% Ross Rucho
% ratrucho@gmail.com
% 10/03/19
% homework2.m
%
% This program implements three different similarity measures and compares
% them to a set of similar images that differ only by rotation and or
% pixel intensity inversion

%% Declarations
clear
close all

%% Execution
% Variables
numImages = 11;
numPixStates = 256;

% Initialize image data structure
inverted = double( imread('brainImage-00-inverted.png') ); % Load an image
I = zeros( numImages, size(inverted, 1), size(inverted, 2) );

I(1,:,:) = double( imread( 'brainImage-00.png' ) );
for k = 2:10
    I(k,:,:) = double( imread( strcat('brainImage-', int2str( 10*(k-1) ), '.png') ) );  % load an image
end
I(11,:,:) = inverted;

% Initialize similarity measure arrays
I_ssd = zeros( numImages-1, 1 );
I_ssd2 = zeros( numImages-1, 1 );

I_ncc = zeros( numImages-1, 1 );
I_ncc2 = zeros( numImages-1, 1 );

I_mi = zeros( numImages-1, 1 );
I_mi2 = zeros( numImages-1, 1 );

% Calculate average image intensities
I_avg = zeros( numImages, 1 );
for k = 1:11
    I_avg(k) = sum( sum( I(k,:,:) ) ) ./ numel( I(k,:,:) );
end

% Calculate one and two dimensional intensity histograms
d_mi = zeros( numImages, numPixStates );
D_mi = zeros( numImages-1, numPixStates, numPixStates );
D2_mi = zeros( numImages-1, numPixStates, numPixStates );

for k = 1:11
    for i = 1:size(inverted,1)
        for j = 1:size(inverted,2)
            d_mi(k, I(k,i,j)+1) = d_mi(k, I(k,i,j)+1) + 1;
        end
    end
end
d_mi = d_mi ./ numel(inverted);

for k = 1:10
    for i = 1:size(inverted,1)
        for j = 1:size(inverted,2)
            D_mi(k, I(1,i,j)+1, I(k,i,j)+1) = D_mi(k, I(1,i,j)+1, I(k,i,j)+1) + 1;
            D2_mi(k, I(11,i,j)+1, I(k,i,j)+1) = D2_mi(k, I(11,i,j)+1, I(k,i,j)+1) + 1;
        end
    end
end
D_mi = D_mi ./ numel(inverted);
D2_mi = D2_mi ./ numel(inverted);

% Calculate informational entropies
h_mi = zeros( numImages );
H_mi = zeros( numImages-1 );
H2_mi = zeros( numImages-1 );

for k = 1:11
    for i = 1:numPixStates
         if d_mi(k,i)~=0
            h_mi(k) = h_mi(k) + d_mi(k,i) .* log2( d_mi(k,i) );
         end
    end
end
h_mi = -1.*h_mi;

for k = 1:10
    for i = 1:numPixStates
        for j = 1:numPixStates
            if D_mi(k,i,j)~=0
                H_mi(k) = H_mi(k) + D_mi(k,i,j) .* log2( D_mi(k,i,j) ) ;
            end
            
            if D2_mi(k,i,j)~=0
                H2_mi(k) = H_mi(k) + D2_mi(k,i,j) .* log2( D2_mi(k,i,j) );
            end
        end
    end
end
H_mi = -1.*H_mi;
H2_mi = -1.*H2_mi;

% Sum of Squared Differences
for k = 1:10
    I_ssd(k) = sum ( sum( ( I(1,:,:) - I(k,:,:) ).^2 ) );
end

% Normalized Cross Correlation
for k = 1:10
    I_ncc(k) = sum( sum( ( I(1,:,:) - I_avg(1) ) .* ( I(k,:,:) - I_avg(k) ) ) ) ./ ( sqrt( sum( sum( ( I(1,:,:) - I_avg(1) ).^2 ) ) ) .* sqrt( sum( sum( ( I(k,:,:) - I_avg(k) ).^2 ) ) ) );
end

% Mutual Information
for k = 1:10
    I_mi(k) = h_mi(1) + h_mi(k) - H_mi(k);
end

% Sum of Squared Differences (2)
for k = 1:10
    I_ssd2(k) = sum ( sum( ( I(11,:,:) - I(k,:,:) ).^2 ) );
end

% Normalized Cross Correlation (2)
for k = 1:10
    I_ncc2(k) = sum( sum( ( I(11,:,:) - I_avg(11) ) .* ( I(k,:,:) - I_avg(k) ) ) ) ./ ( sqrt( sum( sum( ( I(11,:,:) - I_avg(11) ).^2 ) ) ) .* sqrt( sum( sum( ( I(k,:,:) - I_avg(k) ).^2 ) ) ) );
end

% Mutual Information (2)
for k = 1:10
    I_mi2(k) = h_mi(11) + h_mi(k) - H2_mi(k);
end

% Joint level of surprise
J = zeros(3, numPixStates, numPixStates);
J2 = zeros(3, numPixStates, numPixStates);

for k = 1:3
    for i = 1:numPixStates
        for j = 1:numPixStates
            if D_mi(k,i,j)~=0
                J(k,i,j) = -log2( D_mi(k,i,j) );
            end
            
            if D2_mi(k,i,j)~=0
                J2(k,i,j) = -log2( D2_mi(k,i,j) );
            end
        end
    end
end

%% Output

% Sum of Squared Differences
figure(1);
scatter(1:10, I_ssd);
figure(2);
scatter(1:10, I_ssd2);

% Normalized Cross Correlation
figure(3);
scatter(1:10, I_ncc);
figure(4);
scatter(1:10, I_ncc2);

% Mutual Information
figure(5);
scatter(1:10, I_mi);
figure(6);
scatter(1:10, I_mi2);

% Joint level of Surprise
figure(7);
imshow( reshape(J(1,:,:), [numPixStates numPixStates]) );
figure(8);
imshow( reshape(J(2,:,:), [numPixStates numPixStates]) );
figure(9);
imshow( reshape(J(3,:,:), [numPixStates numPixStates]) );
figure(10);
imshow( reshape(J2(1,:,:), [numPixStates numPixStates]) );
figure(11);
imshow( reshape(J2(2,:,:), [numPixStates numPixStates]) );
figure(12);
imshow( reshape(J2(3,:,:), [numPixStates numPixStates]) );



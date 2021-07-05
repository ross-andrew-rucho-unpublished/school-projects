% Ross Rucho
% ratrucho@gmail.com
% 2/15/2018
% assignment2.m
%
% Part 1: This script reads in two 2D images, modifies them to
% be double precision, grayscale, and 128x128; Then it
% performs the DFT and then the inverse DFT and compares
% the input image versus the output image
% Part 2: This script computes the compound images magAphaseB
% and magBphaseA and compares them to the originals
% Part 3:


%% Declarations
clear
close all

% Read in double precision images
img1 = im2double(imread('dubai.jpg'));
img2 = im2double(imread('nature.jpg'));

%% Part 1
% Resizes the images to 128 x 128
inA = img1(floor(size(img1,1)/128).*(1:128), floor(size(img1,2)/128).*(1:128));
inB = img2(floor(size(img2,1)/128).*(1:128), floor(size(img2,2)/128).*(1:128));

% Performs the DFT
[magA, phaseA] = AmpPhaseDFT(inA); 
[magB, phaseB] = AmpPhaseDFT(inB);

% Performs the inverse DFT
outA = ReconfromAmpPhase(magA, phaseA);
outB = ReconfromAmpPhase(magB, phaseB);

% Calculates the difference between the input and output images
diffA = inA - outA;
diffB = inB - outB;

%% Part 2
% Compute the compound images
magAphaseB = ReconfromAmpPhase(magA, phaseB);
magBphaseA = ReconfromAmpPhase(magB, phaseA);

% Determine which DFT image is the larger influence
TextAnswer = 'Phase';

%% Part 3
% Declare local variables
del_y = 15;
del_x = 64;

% Shift the input image
ASx = inA(:, mod((0:127) + del_x, 128) + 1);
AS = inA(mod((0:127) + del_y, 128) + 1, mod((0:127) + del_x, 128) + 1);
    
% Apply the DFT to the shifted image
[mag, phase] = AmpPhaseDFT(inA); 
    
[shiftMagX, shiftPhaseX] = AmpPhaseDFT(ASx);
[shiftMagXY,shiftPhaseXY] = AmpPhaseDFT(AS); 
    
% Calculate the difference in the magnitudes
x_mag_diff = shiftMagX - mag;
x_phase_diff = shiftPhaseX - phase;
    
xy_mag_diff = shiftMagXY - mag; 
xy_phase_diff = shiftPhaseXY - phase;

%% Output
% Displays output
figure
imshow(mag);
figure
imshow(shiftMagX);
figure
imshow(x_mag_diff);



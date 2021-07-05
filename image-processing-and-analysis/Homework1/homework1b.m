% Ross Rucho
% ratrucho@gmail.com
% 09/18/19
% homework1b.m
%
% This program implements the geometric heat equation with some assumptions
% according to the homework 1 writeup.

%% Declarations
clear
close all

%% Execution
I = double( imread('brainslice.png') );  % load an image

% initialize the values (i+1,j), (i-1,j), (i,j+1), (i,j-1)
Ixp = zeros( size( I ) );
Ixm = zeros( size( I ) );
Iyp = zeros( size( I ) );
Iym = zeros( size( I ) );

% initialize the values (i+1,j+1), (i+1,j-1), (i-1,j+1), (i-1,j-1)
Ixypp = zeros( size( I ) );
Ixypm = zeros( size( I ) );
Ixymp = zeros( size( I ) );
Ixymm = zeros( size( I ) );

% initialize the values for second derivatives
Ix = zeros( size( I ) );
Iy = zeros( size( I ) );
Ixx = zeros( size( I ) );
Iyy = zeros( size( I ) );
Ixy = zeros( size( I ) );

% initialize the image boundary to zero
I(1,:)=0; I(end,:)=0; I(:,1)=0; I(:,end)=0;

% initialize other variables
epsilon = 0.001;

% number of iterations
iter = 50;
dt = 0.25;

figure

% iterate
for iI=0:iter

  % display the image every 10 iteration steps
  if ( mod(iI,10)==0 )
    clf
    imagesc( I )
    colormap( gray )
    axis image
    waitforbuttonpress
  end
  
  % compute the neighboring values 
  Ixp(1:end-1,:) = I(2:end,:);  Iyp(:,1:end-1) = I(:,2:end);
  Ixm(2:end,:) = I(1:end-1,:);  Iym(:,2:end) = I(:,1:end-1);
  
  Ixypp(1:end-1,1:end-1) = I(2:end,2:end);
  Ixypm(1:end-1,2:end) = I(2:end,1:end-1);
  Ixymp(2:end,1:end-1) = I(1:end-1,2:end);
  Ixymm(2:end,2:end) = I(1:end-1,1:end-1);
  
  % compute the first and second derivatives
  Ix = 0.5.*( Ixp - Ixm );
  Iy = 0.5.*( Iyp - Iym);
  Ixx = Ixp -2.*I + Ixm;
  Iyy = Iyp -2.*I + Iym;
  Ixy = 0.25.*( Ixypp + Ixymm - Ixymp - Ixypm );

  % compute the new value by averaging
  Itmp = dt.*( ( (Iy.^2).*Ixx -2.*(Ixy).*(Ix).*(Iy) + (Ix.^2).*Iyy )./( Ix.^2 + Iy.^2 + epsilon^2 ) );
  
  % using Dirichlet boundary conditions (ie., fix the boundary)
  I(2:end-1,2:end-1) = I(2:end-1,2:end-1) + Itmp(2:end-1,2:end-1);
  
end

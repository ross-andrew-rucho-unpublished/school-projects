% This program implements the generic heat equation with some assumptions
% according to the homework 1 writeup. (Written by Dr. Marc Niethammer)

%% Declarations
clear
close all

%% Execution
% Solves the diffusion equation I_t = I_xx + I_yy
I = double( imread('brainslice.png') );  % load an image

% initialize the values (i+1,j), (i-1,j), (i,j+1), (i,j-1)
Ixp = zeros( size( I ) );
Ixm = zeros( size( I ) );
Iyp = zeros( size( I ) );
Iym = zeros( size( I ) );

% number of iterations
iter = 50;

useNeumann = false; % use Neumann boundary conditions, otherwise Dirichlet

figure

% iterate
for iI=0:iter

  % display the image every 100 iteration steps
  if ( mod(iI,10)==0 )
    clf
    imagesc( I )
    colormap( gray )
    axis image
    waitforbuttonpress
  end
  
  % compute the neighboring values 
  
  Ixp(1:end-1,:) = I(2:end,:);
  Ixm(2:end,:) = I(1:end-1,:);
  
  Iyp(:,1:end-1) = I(:,2:end);
  Iym(:,2:end) = I(:,1:end-1);

  % use Neumann boundary conditions (zero derivative at boundary)
  Ixp(end,:) = I(end,:); Ixm(1,:) = I(1,:);
  Iyp(:,end) = I(:,end); Iym(:,1) = I(:,1);
  
  % compute the new value by averaging
  
  Itmp = 0.25*( Ixp + Ixm + Iyp + Iym );
  
  if ( useNeumann )
    I = Itmp;
  else  % using Dirichlet boundary conditions (ie., fix the boundary)
    I(2:end-1,2:end-1) = Itmp(2:end-1,2:end-1);
  end
  
end
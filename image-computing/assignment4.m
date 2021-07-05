% Ross Rucho
% ratrucho@gmail.com
% 3/22/2018
% assignment4.m

clear
close all

load('images.mat', 'im_array');

A = double(im_array(1:60,:));

AT = transpose(A);

AAT = A*AT;

[V, D] = eigs(AAT, 60);

ATAV = AT*V;

N = zeros(16384, 40);

for i = 1:40
    N(:,i) = ATAV(:,i)/norm(ATAV(:,i));
end

C = A*N;

val = zeros(16384,1);

for i = 1:40
    val = val + C(4,i).*N(:,i);
end

figure;
imshow(mat2gray(reshape(N(:,1), [128,128])));
figure;
imshow(mat2gray(reshape(N(:,2), [128,128])));
figure;
imshow(mat2gray(reshape(N(:,3), [128,128])));
figure;
imshow(mat2gray(reshape(N(:,4), [128,128])));
figure;
imshow(mat2gray(reshape(val(:,1), [128,128])));


% Prep images
im1 = imread('coffee.png');
im2 = imread('books.png');

imSize = [128,128];

img1 = im2double(rgb2gray(imresize(im1, imSize)));
img2 = im2double(rgb2gray(imresize(im2, imSize)));

% Filter from Question 2
   I2 = zeros(65,128);
   I5 = zeros(65,128);
   
   for j = 1:65
       for k = 1:65
           I2(j,k) = ((((k - 1)/128)^2)+(((j - 1)/128)^2))*exp(-(1/2)*((4*pi)^2)*((((k - 1)/128)^2)+(((j - 1)/128)^2)));
           I5(j,k) = ((((k - 1)/128)^2)+(((j - 1)/128)^2))*exp(-(1/2)*((20*pi)^2)*((((k - 1)/128)^2)+(((j - 1)/128)^2)));
       end
       
       for k = 66:128
           I2(j,k) = ((((k - 129)/128)^2)+(((j - 1)/128)^2))*exp(-(1/2)*((4*pi)^2)*((((k - 129)/128)^2)+(((j - 1)/128)^2)));
           I5(j,k) = ((((k - 129)/128)^2)+(((j - 1)/128)^2))*exp(-(1/2)*((20*pi)^2)*((((k - 129)/128)^2)+(((j - 1)/128)^2)));
       end
       
   end
   
   I2 = I2(1:65,:);
   I5 = I5(1:65,:);
   
   % Apply filter to images
   [mag1, phase1] = AmpPhaseDFT(img1);
   [mag2, phase2] = AmpPhaseDFT(img2);
   
   mag1A = I2.*mag1;
   mag1B = I5.*mag1;
   mag2A = I2.*mag2;
   mag2B = I5.*mag2;
   
   I1A = ReconfromAmpPhase(mag1A, phase1);
   I1B = ReconfromAmpPhase(mag1B, phase1);
   I2A = ReconfromAmpPhase(mag2A, phase2);
   I2B = ReconfromAmpPhase(mag2B, phase2);
   
   I1AZ = zeros(130);
   I1BZ = zeros(130);
   I2AZ = zeros(130);
   I2BZ = zeros(130);
   
   I1AZ(2:129,2:129) = I1A;
   I1BZ(2:129,2:129) = I1B;
   I2AZ(2:129,2:129) = I2A;
   I2BZ(2:129,2:129) = I2B;
   
   % Check for zero crossings
   for j = 1:128
       for k = 1:128
           if abs(I1AZ(j + 1,k + 1)) < 0.2E-5
               I1A(j,k) = 0;
           else
               if I1AZ(j,k)*I1AZ(j + 1,k + 1) < 0
                   I1A(j,k) = 1000;
               elseif I1AZ(j,k + 1)*I1AZ(j + 1,k + 1) < 0
                   I1A(j,k) = 1000;
               elseif I1AZ(j,k + 2)*I1AZ(j + 1,k + 1) < 0
                   I1A(j,k) = 1000;
               elseif I1AZ(j + 1,k)*I1AZ(j + 1,k + 1) < 0
                   I1A(j,k) = 1000;
               elseif I1AZ(j + 1,k + 2)*I1AZ(j + 1,k + 1) < 0
                   I1A(j,k) = 1000;
               elseif I1AZ(j + 2,k)*I1AZ(j + 1,k + 1) < 0
                   I1A(j,k) = 1000;  
               elseif I1AZ(j + 2,k + 1)*I1AZ(j + 1,k + 1) < 0
                   I1A(j,k) = 1000;
               elseif I1AZ(j + 2,k + 2)*I1AZ(j + 1,k + 1) < 0
                   I1A(j,k) = 1000;  
               else
                   I1A(j,k) = 0;  
               end
           end
           if abs(I1BZ(j + 1,k + 1)) < 10E-7
               I1B(j,k) = 0;
               else
               if I1BZ(j,k)*I1BZ(j + 1,k + 1) < 0
                   I1B(j,k) = 1000;
               elseif I1BZ(j,k + 1)*I1BZ(j + 1,k + 1) < 0
                   I1B(j,k) = 1000;
               elseif I1BZ(j,k + 2)*I1BZ(j + 1,k + 1) < 0
                   I1B(j,k) = 1000;
               elseif I1BZ(j + 1,k)*I1BZ(j + 1,k + 1) < 0
                   I1B(j,k) = 1000;
               elseif I1BZ(j + 1,k + 2)*I1BZ(j + 1,k + 1) < 0
                   I1B(j,k) = 1000;
               elseif I1BZ(j + 2,k)*I1BZ(j + 1,k + 1) < 0
                   I1B(j,k) = 1000;  
               elseif I1BZ(j + 2,k + 1)*I1BZ(j + 1,k + 1) < 0
                   I1B(j,k) = 1000;
               elseif I1BZ(j + 2,k + 2)*I1BZ(j + 1,k + 1) < 0
                   I1B(j,k) = 1000;  
               else
                   I1B(j,k) = 0;  
               end
           end
           if abs(I2AZ(j + 1,k + 1)) < 10E-7
               I2A(j,k) = 0;
           else
               if I2AZ(j,k)*I2AZ(j + 1,k + 1) < 0
                   I2A(j,k) = 1000;
               elseif I2AZ(j,k + 1)*I2AZ(j + 1,k + 1) < 0
                   I2A(j,k) = 1000;
               elseif I2AZ(j,k + 2)*I2AZ(j + 1,k + 1) < 0
                   I2A(j,k) = 1000;
               elseif I2AZ(j + 1,k)*I2AZ(j + 1,k + 1) < 0
                   I2A(j,k) = 1000;
               elseif I2AZ(j + 1,k + 2)*I2AZ(j + 1,k + 1) < 0
                   I2A(j,k) = 1000;
               elseif I2AZ(j + 2,k)*I2AZ(j + 1,k + 1) < 0
                   I2A(j,k) = 1000;  
               elseif I2AZ(j + 2,k + 1)*I2AZ(j + 1,k + 1) < 0
                   I2A(j,k) = 1000;
               elseif I2AZ(j + 2,k + 2)*I2AZ(j + 1,k + 1) < 0
                   I2A(j,k) = 1000;  
               else
                   I2A(j,k) = 0;  
               end
           end
           if abs(I2BZ(j + 1,k + 1)) < 10E-7
               I2B(j,k) = 0;
           else
              if I2BZ(j,k)*I2BZ(j + 1,k + 1) < 0
                   I2B(j,k) = 1000;
               elseif I2BZ(j,k + 1)*I2BZ(j + 1,k + 1) < 0
                   I2B(j,k) = 1000;
               elseif I2BZ(j,k + 2)*I2BZ(j + 1,k + 1) < 0
                   I2B(j,k) = 1000;
               elseif I2BZ(j + 1,k)*I2BZ(j + 1,k + 1) < 0
                   I2B(j,k) = 1000;
               elseif I2BZ(j + 1,k + 2)*I2BZ(j + 1,k + 1) < 0
                   I2B(j,k) = 1000;
               elseif I2BZ(j + 2,k)*I2BZ(j + 1,k + 1) < 0
                   I2B(j,k) = 1000;  
               elseif I2BZ(j + 2,k + 1)*I2BZ(j + 1,k + 1) < 0
                   I2B(j,k) = 1000;
               elseif I2BZ(j + 2,k + 2)*I2BZ(j + 1,k + 1) < 0
                   I2B(j,k) = 1000;  
               else
                   I2B(j,k) = 0;  
              end
           end
       end
   end
   
figure;
imshow(I1A);
figure;
imshow(I1B);
figure;
imshow(img1);

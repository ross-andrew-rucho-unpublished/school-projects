% Ross Rucho
% ratrucho@gmail.com
% 4/27/2018
% assignment5.m
%
function [z_slice, z_rotated_slice, q, R, d, A] = assignment5(z_index, c_x, c_y, c_z, r_x, r_y, r_z, theta, axis)
    %z_index is the index for the slice
    %c_x is the center in the x
    %c_y is the center in the y
    %c_z is the center in the z
    %r_x is the radius in the x
    %r_y is the radius in the y
    %r_z is the radius in the z
    %theta is the angle of rotation
    I = zeros(64,64,64);
    Irot = zeros(64,64,64);
    corn = @(x, y, z) ((x - c_x)^2/(r_x)^2 + (y - c_y)^2/(r_y)^2 + (z - c_z)^2/(r_z)^2 - 1) <= 0;
    
    if(axis == 'x') 
        axis = [1, 0, 0];
    end
    if(axis == 'y')
        axis = [0, 1, 0];
    end
    if(axis == 'z')
        axis = [0, 0, 1];
    end
    
    
    %slice at z_index of ellipsoid
    for i = 1:size(I,1)
        for j = 1:size(I,2)
            for k = 1:size(I,3)
                I(i,j,k) = sum([corn(i+0.5, j+0.5, k+0.5), corn(i+0.5, j+0.5, k-0.5), corn(i+0.5, j-0.5, k+0.5),...
                             corn(i+0.5, j-0.5, k-0.5), corn(i-0.5, j+0.5, k+0.5), corn(i-0.5, j+0.5, k-0.5),...
                             corn(i-0.5, j-0.5, k+0.5), corn(i-0.5, j-0.5, k-0.5)]);
            end
        end
    end
    
    z_slice = I(:,:,z_index);

    %quaternion, vector with 4 values
    q = [cos(theta/2), sin(theta/2).*axis];
    s = (1./(q*q'));
    qinv = s.*[q(1), -q(2), -q(3), -q(4)];
    
    %rotation matrix, 3x3
    R = [1 - 2.*s.*(q(3)^2 + q(4)^2), 2.*s.*(q(2).*q(3) - q(4).*q(1)), 2.*s.*(q(2).*q(4) + q(3).*q(1));...
         2.*s.*(q(2).*q(3) + q(4).*q(1)), 1 - 2.*s.*(q(2)^2 + q(4)^2), 2.*s.*(q(3).*q(4) - q(2).*q(1));...
         2.*s.*(q(2).*q(3) - q(3).*q(1)), 2.*s.*(q(3).*q(4) + q(2).*q(1)), 1 - 2.*s.*(q(2)^2 + q(3)^2)];
    
    %slice at z_index of rotated ellipsoid
    for i = 1:size(I,1)
        for j = 1:size(I,2)
            for k = 1:size(I,3)
                % Multiply Quaternians together
                % q x r
                r = [0, i - size(I,1)/2, j - size(I,2)/2, k - size(I,3)/2];
                n1 = r(1)*q(1) - r(2)*q(2) - r(3)*q(3) - r(4)*q(4);
                n2 = r(1)*q(2) + r(2)*q(1) - r(3)*q(4) + r(4)*q(3);
                n3 = r(1)*q(3) + r(2)*q(4) + r(3)*q(1) - r(4)*q(2);
                n4 = r(1)*q(4) - r(2)*q(3) + r(3)*q(2) + r(4)*q(1);
                % (q x r) x qinv
                n = [n1, n2, n3, n4];
                p1 = qinv(1)*n(1) - qinv(2)*n(2) - qinv(3)*n(3) - qinv(4)*n(4);
                p2 = qinv(1)*n(2) + qinv(2)*n(1) - qinv(3)*n(4) + qinv(4)*n(3);
                p3 = qinv(1)*n(3) + qinv(2)*n(4) + qinv(3)*n(1) - qinv(4)*n(2);
                p4 = qinv(1)*n(4) - qinv(2)*n(3) + qinv(3)*n(2) + qinv(4)*n(1);
                p = [p1, p2 + size(I,1)/2, p3 + size(I,2)/2, p4 + size(I,3)/2];
                
                value = interp3(I, p(2), p(3), p(4),'linear');
                if(value ~= value)
                    Irot(i, j, k) = 0;
                else
                    Irot(i, j, k) = value;
                end
            end
        end
    end
    
    z_rotated_slice = Irot(:,:,z_index);
    
    total = sum(sum(sum(Irot)));
    x_c = 0;
    y_c = 0;
    z_c = 0;
    for i = 1:size(I,1)
        for j = 1:size(I,2)
            for k =1:size(I,3)
                v = Irot(i,j,k);
                x_c = x_c + i*v;
                y_c = y_c + j*v;
                z_c = z_c + k*v;
            end
        end
    end

    %center of mass, vector with 3 values
    d = [x_c/total,y_c/total,z_c/total];    
    
    x_t = 0;
    x_m = 0;
    x_b = 0;
    y_t = 0;
    y_m = 0;
    y_b = 0;
    z_t = 0;
    z_m = 0;
    z_b = 0;
    %second moment, 3x3
    for i = 1:size(I,1)
        for j = 1:size(I,2)
            for k =1:size(I,3)
                v = Irot(i,j,k);
                x_t = x_t + v*(i-d(1))*(i-d(1));
                x_m = x_m + v*(i-d(1))*(j-d(2));
                x_b = x_b + v*(i-d(1))*(k-d(3));
                y_t = y_t + v*(j-d(2))*(i-d(1));
                y_m = y_m + v*(j-d(2))*(j-d(2));
                y_b = y_b + v*(j-d(2))*(k-d(3));
                z_t = z_t + v*(k-d(3))*(i-d(1));
                z_m = z_m + v*(k-d(3))*(j-d(2));
                z_b = z_b + v*(k-d(3))*(k-d(3));
            end
        end
    end
    
    A = [x_t, y_t, z_t; x_m, y_m, z_m; x_b, y_b, z_b]./total;    
    
    e = (eig(A)).^(1/2);
    
    q
    R
    d
    A
    e(1)/r_x
    e(2)/r_y
    e(3)/r_z
    
    figure;
    imshow(mat2gray(z_slice));
    figure;
    imshow(mat2gray(z_rotated_slice));
end

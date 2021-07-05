% Ross Rucho
% ratrucho@gmail.com
% 06/15/2020
% GroupProject1.m
%
%{
This script numerically computes the answer to question 6 from homework 1.
Utilizing the physics of the photon's behavior as it travels through space
and interacts with various mirrors, this script iteratively computes the
updated position and velocity of the photon at time steps on the order of
machine precision (i.e., 10e-13 because the final time value equals 1.0e1).
With the initial conditions given in the problem, this script computes the
predicted location of the photon after 10s of time have elapsed.

Computing 1.0e15 iterations of the while loop in this script was extremely
computationally intensive, and in order to have time steps equal to 1.0e-13,
several conditions needed to be added to speed up the computation time for
this software. This explains the addition of initial checks to determine if
the photon is very far from the nearest mirror (i.e., > 1.5e-10 time steps
away). If the photon is this far away from the nearest mirror, then a large
step is taken so that trivial computation can be avoided. Additionally,
these larger time steps help to improve the accuracy of the solution
slightly by incrementing position with the most significant digits of the
velocity vector whenever possible. The more significant digits of the
velocity vector are more likely to remain correct longer than the less
significant digits.

Unfortunately, the current analytical solution for this problem makes this
an illconditioned problem, and therefore, any numerical solutions are
unlikely to be accurate after several iterations. Even with exact
relationships for the physics of this problem, this numerical
implementation amplifies the error in each iteration until, if given enough
time, no accuracy will remain.

For the problem as specified in the homework assignment and as implemented
in this script, the condition number is on the order of (1.0e10). This
means that any error in the input of this algorithm will be amplified to
(1.0e10) times greater in the output of this algorithm. This can be seen by
adding an error on the order of (1.0e-10, 1.0e-11, 1.0e-12, etc.) to the
input and observing that the output differs from the original output by
(1.0e0, 1.0e-1, 1.0e-2, etc.).
%}


%% HW 1 Problem 6 
% Define initial parameters
x0 = [0.5 ; 0.1];
%x0 = [0.5 ; 0.1] + (1.0e-12);
xp0 = [1.0; 0.0];
t0 = 0.0;
dt = 1.0e-13;
mirror_width = (1.0/3.0);

% Initialize model variables with the initial parameters
X = x0;
Xp = xp0;
t = t0;

% Define some plot variables
X_prev = x0;
figure(1);
%figure(2);
hold on

while t < 10.0
    % Calculate the vector from the center of the nearest mirror to the
    % photon
    r = X - round(X);
    
    % Check to see if the photon has collided with a mirror
    if norm(r) > mirror_width + (1.0e-1) && (t + (0.9e-1)) < 10.0
        X = X + Xp.*(0.9e-1);
        t = t + (0.9e-1);
    elseif norm(r) > mirror_width + (1.0e-2) && (t + (0.9e-2)) < 10.0
        X = X + Xp.*(0.9e-2);
        t = t + (0.9e-2);
    elseif norm(r) > mirror_width + (1.0e-3) && (t + (0.9e-3)) < 10.0
        X = X + Xp.*(0.9e-3);
        t = t + (0.9e-3);
    elseif norm(r) > mirror_width + (1.0e-4) && (t + (0.9e-4)) < 10.0
        X = X + Xp.*(0.9e-4);
        t = t + (0.9e-4);
    elseif norm(r) > mirror_width + (1.0e-5) && (t + (0.9e-5)) < 10.0
        X = X + Xp.*(0.9e-5);
        t = t + (0.9e-5);
    elseif norm(r) > mirror_width + (1.0e-6) && (t + (0.9e-6)) < 10.0
        X = X + Xp.*(0.9e-6);
        t = t + (0.9e-6);
    elseif norm(r) > mirror_width + (1.0e-7) && (t + (0.9e-7)) < 10.0
        X = X + Xp.*(0.9e-7);
        t = t + (0.9e-7);
    elseif norm(r) > mirror_width + (1.0e-8) && (t + (0.9e-8)) < 10.0
        X = X + Xp.*(0.9e-8);
        t = t + (0.9e-8);
    elseif norm(r) > mirror_width + (1.0e-9) && (t + (0.9e-9)) < 10.0
        X = X + Xp.*(0.9e-9);
        t = t + (0.9e-9);
    elseif norm(r) > mirror_width + (1.0e-10) && (t + (0.9e-10)) < 10.0
        X = X + Xp.*(0.9e-10);
        t = t + (0.9e-10);
    elseif norm(r) > mirror_width + (1.0e-11) && (t + (0.9e-11)) < 10.0
        X = X + Xp.*(0.9e-11);
        t = t + (0.9e-11);
    elseif norm(r) > mirror_width + (1.0e-12) && (t + (0.9e-12)) < 10.0
        X = X + Xp.*(0.9e-12);
        t = t + (0.9e-12);
    elseif norm(r) <= mirror_width % Collision
        % Begin to add another collision to the plot
        viscircles( round(X)', mirror_width);
        quiver( X_prev(1),X_prev(2),X(1)-X_prev(1),X(2)-X_prev(2), 0,'k');
        X_prev = X;
        
        % Compute the dot product of the velocity with
        % the negative of the normalized r vector
        r_norm_neg = -r./norm(r);
        impact_product = transpose(Xp)*(r_norm_neg);
        
        % Determine the type of impact
        if impact_product==1 % Photon velocity is exactly orthogonal to the mirror
            Xp = -Xp;
        elseif impact_product~=0 % Photon velocity is not tangent nor orthogonal to the mirror
            % Compute the angle of rotation induced by the impact
            impact_cross = cross( [ Xp(1);Xp(2);0 ],[ r_norm_neg(1);r_norm_neg(2);0 ] );
            impact_angle = 2*asin( impact_cross(3) );
            
            % Compute the updated velocity vector using the impact angle
            % performing rotation via complex multiplication
            Xp_complex = -( exp(1i*impact_angle)*complex( Xp(1),Xp(2)) );
            Xp = [ real( Xp_complex );imag( Xp_complex ) ];
        end
    else

    end
    
    % Update the position and the current time
    X = X + Xp.*dt;
    t = t + dt;
end

disp(X)
disp(norm(X))

hold off

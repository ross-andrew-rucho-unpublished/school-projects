% Ross Rucho
% ratrucho@gmail.com
% 09/1/2020
% cyclic-executive-frame-calculator.m
%
%{
This function computes all of the feasible frame sizes for a cyclic
executive scheduler given some task set. 

Input:
tau - An M x 4 matrix that characterizes a task set for some application.
        Each row is a single task represented using the sporadic task
        model. I.e, (phase, period, computation time, relative deadline).

Output:
all_frames - An array containing all of the feasible frame sizes for the given
                task set.
no_first_frames - An array containing all of the feasible frame sizes for
                    the given task set with the first constraint relaxed.
%}

function [ all_frames, no_first_frames ] = cyclic_executive_frame_calc(tau)
    %% Format Input
    % All reasonable integer frame sizes represented by indices
    hyperperiod = double(lcm(sym(tau( :,2 ))));
    frames = uint8(ones( 1,hyperperiod ));
    
    
    %% Second Constraint
    % The frame size must divide the hyperperiod, or equivalently, the
    % frame size must divide the period of some task in the task set
    no_first_constraint = bitand( frames,uint8(mod( hyperperiod,find(frames) )==0) );

    
    %% Third Constraint
    % There must be at least one frame between the release time and the
    % deadline of every task, or equivalently, this relation must hold for
    % every task:
    % 2*(frame size) - gcd(period, frame size) <= relative deadline
    candidate_frames = find( no_first_constraint);
    periods = tau(:,2)';
    deadlines = tau(:,4)';
    for i = 1:size( candidate_frames,2 )
        for j = 1:size( periods,2 )
            if 2*candidate_frames(i) - gcd( periods(j),candidate_frames(i) ) > deadlines(j)
                no_first_constraint(candidate_frames(i)) = 0;
                break
            end
        end
    end
    
    
    %% First Constraint
    % The frame size must be greater than the computation time for
    % each task in the task set
    all_constraints = bitand( no_first_constraint,uint8( find( frames )>max( tau( :,3 ) ) ) );
    
    
    %% Format Output
    % All feasible frame sizes
    all_frames = find(all_constraints);
    no_first_frames = find(no_first_constraint);
    
    
end


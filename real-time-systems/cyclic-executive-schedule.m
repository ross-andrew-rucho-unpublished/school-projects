% Ross Rucho
% ratrucho@gmail.com
% 09/1/2020
% cyclic-executive-schedule.m
%
%{
This function computes a feasible schedule for a periodic task system with
arbitrary phases and arbitrary relative deadlines. * Some assumptions are
made and listed below in the comments. This is by no means guaranteed to
work in complete generality * 

Input:
tau - An M x 4 matrix that characterizes a task set for some application.
        Each row is a single task represented using the sporadic task
        model. I.e, (phase, period, computation time, relative deadline).

Output:
first_feasible_frame - The largest frame size that satisfies the
                        constraints of the task system.
scheduled_graph - The graph returned by the max flow algorithm. This graph
                    represents a feasible schedule for the task set given
                    the chosen frame size.
%}

function [ first_feasible_frame, scheduled_graph ] = cyclic_executive_schedule(tau)
    % Compute the hyperperiod and all feasible frame sizes
    hyperperiod = double(lcm(sym(tau( :,2 ))));
    [ not_used,frame_sizes ] = cyclic_executive_frame_calc(tau);
    
    % Initialize helpful variables
    phases = tau( :,1 )';
    periods = tau( :,2 )';
    computation_times = tau( :,3 )';
    deadlines = tau( :,4 )';
    task_number = size( phases,2 );
    
    % Compute the number of jobs in a major cycle for each task
    % Computes the number of jobs assuming the overly strict condition that
    % all jobs released within a hyperperiod will be completed within the
    % hyperperiod
    maximum_computation = 0;
    jobs_in_task = zeros( 1,task_number );
    for i = 1:task_number
        jobs_in_task_i = ceil((hyperperiod-phases(i))/periods(i));
        jobs_in_task(i) = jobs_in_task_i;
        maximum_computation = maximum_computation+(computation_times(i).*jobs_in_task_i);
    end
    N = sum(jobs_in_task);
    disp(jobs_in_task);
        
    % Initialize control variables
    feasible_schedule = false;
    frame_number = size( frame_sizes,2 );
    
    % Iterate through the frame sizes from largest to smallest until a
    % feasible schedule has been determined
    while ~feasible_schedule && frame_number > 0
        current_frame_size = frame_sizes(frame_number);
        
        % Compute the number of frames in a major cycle
        % Frames are assumed to divide the hyperperiod
        F = hyperperiod/current_frame_size;
        
        %{ create directed graph
    
        %}
        
        % Initialize the matrix representation for the graph
        graph_matrix = zeros(F+N+2);
        
        % First row represents the source node, i.e., there is an edge from
        % the source node to every job node with an edge weight equal to
        % the computation time for the task that the job represents
        start_index = 2;
        for i = 1:task_number
            graph_matrix( 1,start_index:start_index+(jobs_in_task(i)-1) ) = computation_times(i).*ones( 1,jobs_in_task(i) );
            start_index = start_index + jobs_in_task(i);
        end
        
        % Rows 2 through N+1 represent the job nodes, i.e., there is an
        % edge from each job node to every frame node in which that job
        % could feasibly execute. All edge weights are equal to the
        % current frame size.
        start_row = 2;
        for i = 1:task_number
            for j = 1:jobs_in_task(i)
                % Compute the first feasible frame
                % Assumes that any jobs released in the last frame simply
                % run in the last frame. In general, this implementation
                % could produce an incorrect schedule or determine that a
                % task set is not schedulable when it actually can be
                first_frame = ceil(((j-1)*periods(i)+phases(i)) / current_frame_size);
                if first_frame == F
                    first_frame = F-1;
                end
                start_col = N+2+first_frame;
                
                % Compute the last feasible frame
                % Probably should include error checking here to guarantee
                % that first_col <= last_col
                % Includes conditional guarantee that all released jobs
                % will complete within the hyperperiod
                last_frame = floor(((j-1)*periods(i)+phases(i)+deadlines(i)) / current_frame_size);
                if last_frame > F
                    last_frame = F;
                end
                stop_col = N+2+(last_frame-1);
                
                % Update the matrix
                graph_matrix( start_row+(j-1),start_col:stop_col ) = current_frame_size;
            end
            % Increase start row to the row representing the first job in
            % the next task
            start_row = start_row + jobs_in_task(i);
        end
        
        % Rows N+2 through F+N+1 represent the frame nodes, i.e., there is
        % an edge from each frame node to the sink with an edge weight
        % equal to the frame size
        graph_matrix( N+2:F+N+1,F+N+2 ) = current_frame_size.*ones(F,1) ;
        
        % Format the matrix representation for the graph and perform a
        % maximum flow analysis
        [ max_flow,scheduled_graph ] = maxflow(digraph(graph_matrix), 1, N+F+2);
        if abs(maximum_computation - max_flow) <= 0.001 
            first_feasible_frame = current_frame_size;
            feasible_schedule = true;
        end
        
        % Decrement frame_number to iterate through potential frame sizes
        frame_number = frame_number - 1;
    end
end


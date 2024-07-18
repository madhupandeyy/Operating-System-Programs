#include<stdio.h>

void main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int proc_id[n], at[n], bt[n], ct[n], tat[n], wt[n], m[n];
    double avg_tat = 0.0, ttat = 0.0, avg_wt = 0.0, twt = 0.0;

    // Input process IDs, arrival times, burst times
    for (int i = 0; i < n; i++)
    {
        proc_id[i] = i + 1;
        printf("Enter arrival time for P%d: ", proc_id[i]);
        scanf("%d", &at[i]);
        printf("Enter burst time for P%d: ", proc_id[i]);
        scanf("%d", &bt[i]);
        m[i] = 0; // Initialize marker for process completion
    }

    // SJF Non-preemptive scheduling logic

    int c = 0; // Current time starts at 0
    int count = 0; // Number of completed processes

    while (count < n)
    {
        int min_bt = 999999; // Initialize with a large number
        int mb = -1; // Initialize mb to -1 indicating no process selected

        // Find the process with minimum burst time that has arrived and not completed
        for (int i = 0; i < n; i++)
        {
            if (at[i] <= c && m[i] == 0 && bt[i] < min_bt)
            {
                min_bt = bt[i];
                mb = i;
            }
        }

        // If no process is found (mb is still -1), move time forward to next arrival
        if (mb == -1)
        {
            int next_arrival = 999999; // Initialize with a large number

            // Find the next arrival time
            for (int i = 0; i < n; i++)
            {
                if (at[i] > c && at[i] < next_arrival)
                {
                    next_arrival = at[i];
                }
            }

            // Move time to the next arrival time
            c = next_arrival;
        }
        else
        {
            // Execute the selected process
            ct[mb] = c + bt[mb];
            c = ct[mb]; // Update current time
            m[mb] = 1; // Mark process mb as completed
            count++; // Increment completed process count
        }
    }

    // Calculate turnaround time (TAT) and waiting time (WT)
    for (int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        ttat += tat[i];
        twt += wt[i];
    }

    // Calculate averages
    avg_tat = ttat / (double)n;
    avg_wt = twt / (double)n;

    // Print scheduling results
    printf("\nSJF Non Preemptive scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", proc_id[i], at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage turnaround time: %lf ms\n", avg_tat);
    printf("Average waiting time: %lf ms\n", avg_wt);
}

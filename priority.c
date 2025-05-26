#include <stdio.h>

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], pr[n], rt[n], wt[n], tat[n], completed = 0, time = 0, min_pri, shortest;
    for(i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for P%d: ", i + 1);
        scanf("%d%d%d", &at[i], &bt[i], &pr[i]);
        rt[i] = bt[i];
    }
    while(completed != n) {
        min_pri = 1e9;
        shortest = -1;
        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && pr[i] < min_pri) {
                min_pri = pr[i];
                shortest = i;
            }
        }
        if(shortest == -1) {
            time++;
            continue;
        }
        rt[shortest]--;
        if(rt[shortest] == 0) {
            completed++;
            int finish_time = time + 1;
            tat[shortest] = finish_time - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
            if(wt[shortest] < 0)
                wt[shortest] = 0;
        }
        time++;
    }
    printf("Process\tAT\tBT\tPR\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], wt[i], tat[i]);
    }
    return 0;
}

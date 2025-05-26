#include <stdio.h>

int main() {
    int n, i, tq, time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int bt[n], rt[n], wt[n], tat[n], at[n];
    for(i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    int done;
    while(completed != n) {
        done = 1;
        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0) {
                done = 0;
                if(rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    wt[i] = time - at[i] - bt[i];
                    tat[i] = time - at[i];
                    rt[i] = 0;
                    completed++;
                }
            }
        }
        if(done)
            time++;
    }
    printf("Process\tAT\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    return 0;
}

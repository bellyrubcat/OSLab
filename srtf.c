#include <stdio.h>

int main() {
    int n, i, j, time = 0, smallest, count = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int at[n], bt[n], rt[n], wt[n], tat[n];
    for(i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }
    int complete = 0, minm = 1e9, finish_time;
    int check = 0;
    while (complete != n) {
        smallest = -1;
        minm = 1e9;
        for (i = 0; i < n; i++) {
            if ((at[i] <= time) && (rt[i] < minm) && rt[i] > 0) {
                minm = rt[i];
                smallest = i;
                check = 1;
            }
        }
        if (check == 0) {
            time++;
            continue;
        }
        rt[smallest]--;
        if (rt[smallest] == 0) {
            complete++;
            finish_time = time + 1;
            tat[smallest] = finish_time - at[smallest];
            wt[smallest] = tat[smallest] - bt[smallest];
            if (wt[smallest] < 0)
                wt[smallest] = 0;
        }
        time++;
    }
    printf("Process\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    return 0;
}

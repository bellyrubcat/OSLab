#include <stdio.h>

int main() {
    int n, i, j, time = 0, completed = 0, shortest;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int period[n], et[n], rt[n], wt[n], tat[n], next_arrival[n];
    for(i = 0; i < n; i++) {
        printf("Enter execution time and period for P%d: ", i + 1);
        scanf("%d%d", &et[i], &period[i]);
        rt[i] = et[i];
        next_arrival[i] = 0;
        wt[i] = 0;
        tat[i] = 0;
    }
    int hyper_period = period[0];
    for(i = 1; i < n; i++) {
        int a = hyper_period, b = period[i], temp;
        while(b != 0) {
            temp = b;
            b = a % b;
            a = temp;
        }
        hyper_period = (hyper_period * period[i]) / a;
    }
    for(time = 0; time < hyper_period; time++) {
        for(i = 0; i < n; i++) {
            if(time == next_arrival[i]) {
                rt[i] = et[i];
                next_arrival[i] += period[i];
            }
        }
        shortest = -1;
        for(i = 0; i < n; i++) {
            if(rt[i] > 0 && (shortest == -1 || period[i] < period[shortest])) {
                shortest = i;
            }
        }
        if(shortest != -1) {
            rt[shortest]--;
            for(j = 0; j < n; j++) {
                if(j != shortest && rt[j] > 0)
                    wt[j]++;
            }
            if(rt[shortest] == 0)
                tat[shortest] += time + 1;
        }
    }
    printf("Process\tPeriod\tET\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, period[i], et[i], wt[i], tat[i]);
    }
    return 0;
}

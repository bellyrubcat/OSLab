#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int et[n], deadline[n], rt[n], wt[n], tat[n], at[n], next_deadline[n];
    for(i = 0; i < n; i++) {
        printf("Enter arrival time, execution time, and deadline for P%d: ", i + 1);
        scanf("%d%d%d", &at[i], &et[i], &deadline[i]);
        rt[i] = et[i];
        next_deadline[i] = deadline[i];
        wt[i] = 0;
        tat[i] = 0;
    }
    int hyper_period = deadline[0];
    for(i = 1; i < n; i++) {
        int a = hyper_period, b = deadline[i], temp;
        while(b != 0) {
            temp = b;
            b = a % b;
            a = temp;
        }
        hyper_period = (hyper_period * deadline[i]) / a;
    }
    for(time = 0; time < hyper_period; time++) {
        for(i = 0; i < n; i++) {
            if(time == at[i]) {
                rt[i] = et[i];
                next_deadline[i] = time + deadline[i];
            }
        }
        int min_deadline = 1e9, current = -1;
        for(i = 0; i < n; i++) {
            if(rt[i] > 0 && next_deadline[i] < min_deadline && at[i] <= time) {
                min_deadline = next_deadline[i];
                current = i;
            }
        }
        if(current != -1) {
            rt[current]--;
            for(i = 0; i < n; i++) {
                if(i != current && rt[i] > 0)
                    wt[i]++;
            }
            if(rt[current] == 0)
                tat[current] = time + 1 - at[current];
        }
    }
    printf("Process\tAT\tET\tDL\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], et[i], deadline[i], wt[i], tat[i]);
    }
    return 0;
}

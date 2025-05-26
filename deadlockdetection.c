#include <stdio.h>
#include <stdbool.h>

int main() {
    int P, R;
    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resources: ");
    scanf("%d", &R);

    int alloc[P][R], request[P][R], avail[R];
    bool finish[P];

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter request matrix:\n");
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &request[i][j]);

    printf("Enter available resources:\n");
    for (int i = 0; i < R; i++)
        scanf("%d", &avail[i]);

    for (int i = 0; i < P; i++)
        finish[i] = false;

    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (request[i][j] > avail[j])
                        break;
                }
                if (j == R) {
                    for (int k = 0; k < R; k++)
                        avail[k] += alloc[i][k];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            break;
    }

    bool deadlock = false;
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            deadlock = true;
            printf("Process P%d is in deadlock.\n", i);
        }
    }

    if (!deadlock)
        printf("No deadlock detected.\n");

    return 0;
}

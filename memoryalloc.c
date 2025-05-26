#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }

    printf("First Fit:\nProcess\tSize\tBlock\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%s\n", i + 1, processSize[i], allocation[i] != -1 ? (char[4]){ 'B', '0' + allocation[i] + 1, '\0' } : "Not Allocated");
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i])
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    printf("\nBest Fit:\nProcess\tSize\tBlock\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%s\n", i + 1, processSize[i], allocation[i] != -1 ? (char[4]){ 'B', '0' + allocation[i] + 1, '\0' } : "Not Allocated");
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i])
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nWorst Fit:\nProcess\tSize\tBlock\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%s\n", i + 1, processSize[i], allocation[i] != -1 ? (char[4]){ 'B', '0' + allocation[i] + 1, '\0' } : "Not Allocated");
}

int main() {
    int m, n;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter sizes of memory blocks:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter sizes of processes:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    int tempBlock1[m], tempBlock2[m], tempBlock3[m];
    for (int i = 0; i < m; i++) {
        tempBlock1[i] = blockSize[i];
        tempBlock2[i] = blockSize[i];
        tempBlock3[i] = blockSize[i];
    }

    firstFit(tempBlock1, m, processSize, n);
    bestFit(tempBlock2, m, processSize, n);
    worstFit(tempBlock3, m, processSize, n);

    return 0;
}

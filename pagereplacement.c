#include <stdio.h>

int search(int key, int frame[], int f) {
    for (int i = 0; i < f; i++)
        if (frame[i] == key)
            return i;
    return -1;
}

void printFrames(int frame[], int f) {
    for (int i = 0; i < f; i++) {
        if (frame[i] == -1)
            printf("- ");
        else
            printf("%d ", frame[i]);
    }
    printf("\n");
}

void fifo(int pages[], int n, int f) {
    int frame[f], index = 0, faults = 0;
    for (int i = 0; i < f; i++) frame[i] = -1;

    printf("FIFO:\n");
    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, f) == -1) {
            frame[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }
        printFrames(frame, f);
    }
    printf("Page Faults: %d\n\n", faults);
}

void lru(int pages[], int n, int f) {
    int frame[f], used[f], time = 0, faults = 0;
    for (int i = 0; i < f; i++) frame[i] = -1;

    printf("LRU:\n");
    for (int i = 0; i < n; i++) {
        int pos = search(pages[i], frame, f);
        if (pos == -1) {
            int lru = 0;
            for (int j = 1; j < f; j++)
                if (used[j] < used[lru])
                    lru = j;
            frame[lru] = pages[i];
            used[lru] = ++time;
            faults++;
        } else {
            used[pos] = ++time;
        }
        printFrames(frame, f);
    }
    printf("Page Faults: %d\n\n", faults);
}

void optimal(int pages[], int n, int f) {
    int frame[f], faults = 0;
    for (int i = 0; i < f; i++) frame[i] = -1;

    printf("Optimal:\n");
    for (int i = 0; i < n; i++) {
        if (search(pages[i], frame, f) == -1) {
            int replace = -1, farthest = i + 1;
            for (int j = 0; j < f; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replace = j;
                        }
                        break;
                    }
                }
                if (k == n) {
                    replace = j;
                    break;
                }
            }
            if (replace == -1)
                for (int j = 0; j < f; j++)
                    if (frame[j] == -1) {
                        replace = j;
                        break;
                    }
            frame[replace] = pages[i];
            faults++;
        }
        printFrames(frame, f);
    }
    printf("Page Faults: %d\n", faults);
}

int main() {
    int n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    fifo(pages, n, f);
    lru(pages, n, f);
    optimal(pages, n, f);

    return 0;
}

#include <stdio.h>


int findOptimal(int pages[], int frame[], int currentIndex, int no, int n) {
    int res = -1, farthest = currentIndex;
    for (int i = 0; i < no; i++) {
        int j;
        for (j = currentIndex; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n) {
            return i;
        }
    }
    return (res == -1) ? 0 : res;
}

int findLRU(int time[], int no) {
    int i, minimum = time[0], pos = 0;
    for(i = 1; i < no; ++i) {
        if(time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main()
{
    int i, j, n, a[50], frame[10], no, k, avail, countFIFO = 0, countOPT = 0, countLRU = 0;
    int time[10], counter = 0;

    // Input the number of pages
    printf("\nENTER THE NUMBER OF PAGES:\n");
    scanf("%d", &n);

    // Input the page numbers
    printf("\nENTER THE PAGE NUMBER :\n");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    // Input the number of frames
    printf("\nENTER THE NUMBER OF FRAMES :");
    scanf("%d", &no);

    // Initialize all frames to -1 (empty)
    for(i = 0; i < no; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement\n");
    printf("Ref String\t\tPage Frames\n");
    j = 0;
    for(i = 0; i < n; i++)
    {
        printf("%d\t\t\t", a[i]);
        avail = 0;
        for(k = 0; k < no; k++) {
            if(frame[k] == a[i]) {
                avail = 1;
                break;
            }
        }
        if (avail == 0) {
            frame[j] = a[i];
            j = (j + 1) % no;
            countFIFO++;
            printf("PF No. %d\t", countFIFO);
        }
        else {
            printf("\t\t");
        }
        for(k = 0; k < no; k++) {
            if(frame[k] != -1)
                printf("%d\t", frame[k]);
            else
                printf("-\t");
        }
        printf("\n");
    }

    printf("\nOptimal Page Replacement\n");
    for(i = 0; i < no; i++)
        frame[i] = -1;

    printf("Ref String\t\tPage Frames\n");
    for(i = 0; i < n; i++)
    {
        printf("%d\t\t\t", a[i]);
        avail = 0;
        for(k = 0; k < no; k++) {
            if(frame[k] == a[i]) {
                avail = 1;
                break;
            }
        }
        if (avail == 0) {
            if (i < no) {
                frame[i] = a[i];
            } else {
                int pos = findOptimal(a, frame, i+1, no, n);
                frame[pos] = a[i];
            }
            countOPT++;
            printf("PF No. %d\t", countOPT);
        } else {
            printf("\t\t");
        }
        for(k = 0; k < no; k++) {
            if(frame[k] != -1)
                printf("%d\t", frame[k]);
            else
                printf("-\t");
        }
        printf("\n");
    }

    printf("\nLRU Page Replacement\n");
    for(i = 0; i < no; i++)
        frame[i] = -1;

    printf("Ref String\t\tPage Frames\n");
    for(i = 0; i < n; i++)
    {
        printf("%d\t\t\t", a[i]);
        avail = 0;
        for(k = 0; k < no; k++) {
            if(frame[k] == a[i]) {
                avail = 1;
                time[k] = ++counter;
                break;
            }
        }
        if (avail == 0) {
            if (i < no) {
                frame[i] = a[i];
                time[i] = ++counter;
            } else {
                int pos = findLRU(time, no);
                frame[pos] = a[i];
                time[pos] = ++counter;
            }
            countLRU++;
            printf("PF No. %d\t", countLRU);
        } else {
            printf("\t\t");
        }
        for(k = 0; k < no; k++) {
            if(frame[k] != -1)
                printf("%d\t", frame[k]);
            else
                printf("-\t");
        }
        printf("\n");
    }

    printf("\nThe number of Page Faults using FIFO are %d\n", countFIFO);
    printf("The number of Page Faults using Optimal are %d\n", countOPT);
    printf("The number of Page Faults using LRU are %d\n", countLRU);

    return 0;
}

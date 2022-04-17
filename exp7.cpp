#include <stdio.h>

// FIRST-COME FIRST-SERVED scheduling.

int max(int a, int b) {
    return (a >= b ? a : b);
}

int main() {
    int n;
    printf("How many processes : ");
    scanf("%d", &n);

    int processId[n];
    for (int i = 0; i < n; i++) {
        processId[i] = i + 1;
    }

    int arrivalTime[n];
    printf("Enter their arrival times (ascending.) : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arrivalTime[i]);
    }

    int burstTime[n];
    printf("Enter their burst times : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &burstTime[i]);
    }

    int startTime[n], endTime[n];
    startTime[0] = arrivalTime[0];
    endTime[0] = startTime[0] + burstTime[0];
    for (int i = 1; i < n; i++) {
        startTime[i] = max(endTime[i - 1], arrivalTime[i]);
        endTime[i] = startTime[i] + burstTime[i];
    }

    int turnAroundTime[n], waitingTime[n];
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = endTime[i] - arrivalTime[i];
        waitingTime[i] = turnAroundTime[i] - burstTime[i];
    }

    float avgTAT, avgWT;
    for (int i = 0; i < n; i++) {
        avgTAT += turnAroundTime[i];
        avgWT += waitingTime[i];
    }
    avgTAT /= n;
    avgWT /= n;

    char border[] = "-------------------------------------------------------------------------------------";
    printf("%s\n", border);
    printf("ProcessID\tArrival\t\tStart\tBurst\tEnd\tTurnAround\tWaiting\n");
    printf("%s\n", border);

    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t%d\t%d\t%d\t\t%d\n", processId[i], arrivalTime[i], startTime[i], burstTime[i],
            endTime[i], turnAroundTime[i], waitingTime[i]);
        printf("%s\n", border);
    }

    printf("Average Turn around time : %f\n", avgTAT);
    printf("Average Wating time : %f\n", avgWT);
    return 0;
}
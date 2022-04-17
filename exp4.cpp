#include <stdio.h>
#include <bits/stdc++.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void PrintSeq(int n) {
    std::cout << "From " << getpid() << " " << n << ", from parent " << getppid() << std::endl;
    if (n == 1) return;
    auto pid = fork();
    if (pid == 0) {
        if (n&1) {
            PrintSeq(n * 3 + 1);
        }else PrintSeq(n / 2);
    }
    else wait(0);
}

int main() {
    int n; std::cin >> n;
    PrintSeq(n);
}
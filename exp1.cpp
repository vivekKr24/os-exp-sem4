#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<iostream>
using namespace std;

int main(){
    pid_t pid1, pid2, pid3, pid4;
    printf("Parent of all: %d\n",getpid());

    pid1 = fork();

    if(pid1 == 0){   
        cout<< " Current Process ID : " << getpid() << " It's Parent Process ID : " <<getppid() <<endl;
        pid2 = fork();
        if(pid2 == 0){ 
            cout<< " Current Process ID : " << getpid() << " It's Parent Process ID : " <<getppid() <<endl;
        }
    }
    if(pid1 > 0){
        pid3 = fork();
        if(pid3 == 0){ 
            cout<< " Current Process ID : " << getpid() << " It's Parent Process ID : " <<getppid() <<endl;
            pid4 = fork();
            if(pid4 == 0){ 
                cout<< " Current Process ID : " << getpid() << " It's Parent Process ID : " <<getppid() <<endl;
            }

        }
    }
    for(int i=0; i< 3; i++)
        cout << wait(NULL) << " ";

}
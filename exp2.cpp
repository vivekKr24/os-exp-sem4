#include <stdio.h>
#include <bits/stdc++.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

char *filename;
FILE *fp;



void viewHistory()
{
    char *line;
    int i = 1;
    fp = fopen(filename, "r");
    while (fgets(line, 100, fp))
    {
        cout << i++ << " : " << line << endl ;
    }
    fclose(fp);
}
void addToHistory(char *args)
{
    fp = fopen(filename, "a");
    fputs(args, fp);
    fclose(fp);
}
int checkCustomInput(char *args)
{
    if (strcmp(args, "exit") == 0)
    {
        cout<< " \n "<<endl;
        return -1;
    }
    else if (strcmp(args, "history") == 0)
    {
        viewHistory();
        return 1;
    }
    return 0;
}

int execute(char **args)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        if (!strcmp(args[0], "cd") && args[1] != NULL)
        {
            if (chdir(args[1]) != 0)
            {
                cout << "Enter Valid Path ! ! \n";
            }
        }
        else if (execvp(args[0], args) == -1)
        {
            cout << "Enter valid Command ! !\n";
        }
    }
    else if (pid < 0)
    {
        cout << "FORK ERROR OCCURED! \n";
    }
    else
    {
        wait(NULL);
    }

    return 1;
}
char **parseArgs(char *line)
{
    int position = 0;
    char **tokens = (char**)malloc(104 );
    char *token = NULL;
    token = strtok(line, " \n\t");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;
        token = strtok(NULL, " \n\t");
    }
    tokens[position] = NULL;
    return tokens;
}

void MyShell()
{
   
    cout << "----\t WELCOME TO MY-SHELL\t ----\n\n\n";
    filename = strcat(getenv("HOME"), "/myshellHistory.txt");
    fp = fopen(filename, "w");
    fclose(fp);
    while (1)
    {
        char **parsedInput;
        cout<< "\n==> " ;
        char input[100];
        fgets(input, 100, stdin);
        if (input[strlen(input) - 1] != '\n')
        {
            cout << "MAXIMUM 100 CHARACTERS ALLOWED! ";
            while (getchar() != '\n')
                continue;
            continue;
        }

        addToHistory(input);
        parsedInput = parseArgs(input);
        int flg = checkCustomInput(input);
        if(flg==0)
            execute(parsedInput);
        else if(flg==-1)
            exit(0);
    }
}


int main()
{
    MyShell();
    return 0;
}
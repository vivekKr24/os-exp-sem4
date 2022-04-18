#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3
int available[NUMBER_OF_RESOURCES]; //available amount of each resource
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; //max demand of each customer
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; //currently allocated resources to each customer
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]; //remaining need of each customer

// checks if machine is in safe state after allocation
bool isSafe(int n,int m,int need[5][3]) 
{
    int i,j,k;
    // Work: Currently available , Finish: is task i finished, seq: safe seq 
    int work[m],finish[n],seq[n];

    for(i=0;i<m;i++)
        work[i]=available[i];

    for(i=0;i<n;i++)
        finish[i]=0;

    int count=0;

    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            if(finish[i]==0)
            {
                int flag=0;
                for(j=0;j<m;j++) {
                    if(need[i][j]>work[j]) {
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    seq[count++]=i;
                    for(int y=0;y<m;y++)
                        work[y]+=allocation[i][y];
                    finish[i]=1;
                }
            }
        }
    }
    int flag=1;
    for(i=0;i<n;i++)
    {
        if(finish[i]==0)
        {
            flag=0;
            break;
        }
    }
    if(flag)
    {
        printf("Safe sequence : ");
        for(i=0;i<n;i++)
            printf("%d ",seq[i]);
        printf("\n");
    }
    return flag;
}

int request_resources(int customer_num,int request[])
{
    int i,j,m=NUMBER_OF_RESOURCES,n=NUMBER_OF_CUSTOMERS;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            need[i][j]=maximum[i][j]-allocation[i][j];
    i=customer_num;
    for(j=0;j<m;j++)
    {
        if(request[j]>need[i][j])
        {
            printf("More resources demanded by customer %d than required\n",i);
            return -1;
        }
    }
    for(j=0;j<m;j++)
    {
        if(request[j]>available[j])
        {
            printf("Customer %d should wait, since resources are not available\n",i);
            return -1;
        }
    }
    for(j=0;j<m;j++)
    {
        available[j]-=request[j];
        allocation[i][j]+=request[j];
        need[i][j]-=request[j];
    }
    if(isSafe(n,m,need))
        return 0;
    else
    {
        for(j=0;j<m;j++)
        {
            available[j]+=request[j];
            allocation[i][j]-=request[j];
            need[i][j]+=request[j];
        }
        return -1;
    }
}

void release_resources(int customer_num,int release[])
{
    int i=customer_num,j,m=NUMBER_OF_RESOURCES,k;
    for(j=0;j<m;j++)
    {
        if(allocation[i][j]>=release[j])
        {
            allocation[i][j]-=release[j];
            available[j]+=release[j];
            need[i][j]+=release[j];
        }
        else
        {
            printf("Resources to be released exceed allocated resources\n");
            for(k=j-1;k>=0;k--)
            {
                allocation[i][k]+=release[k];
                available[k]-=release[k];
                need[i][k]-=release[k];
            }
            return;
        }
    }
}

int main(int argc, char* argv[])
{
    FILE* fp=fopen("input.txt","r");
    int i,j,x,num,data[NUMBER_OF_CUSTOMERS*NUMBER_OF_RESOURCES];

    for(i=0;i<argc-1;i++)
        available[i]=atoi(argv[i+1]);
    
    i=x=0;

    while(!feof(fp))
    {
        fscanf(fp,"%d",&num);
        data[i++]=num;
    }
    fclose(fp);

    for(i=0;i<NUMBER_OF_CUSTOMERS;i++)
        for(j=0;j<NUMBER_OF_RESOURCES;j++)
            maximum[i][j]=data[x++];

    for(i=0;i<NUMBER_OF_CUSTOMERS;i++)
        for(j=0;j<NUMBER_OF_RESOURCES;j++)
            need[i][j]=maximum[i][j]-allocation[i][j];

    char s[4]="0";
    
    int request[NUMBER_OF_RESOURCES],release[NUMBER_OF_RESOURCES];
    int customer_num;
    do
    {
        printf("Enter command : ");
        scanf(" %s",s);
        if(!strcmp(s,"RQ"))
        {
            scanf("%d",&customer_num);
            for(i=0;i<NUMBER_OF_RESOURCES;i++)
                scanf("%d",&request[i]);
            int req=request_resources(customer_num,request);
            if(req==0)
                printf("Request granted\n");
            else
                printf("Request denied\n");
        }
        else if(!strcmp(s,"RL"))
        {
            scanf("%d",&customer_num);
            for(i=0;i<NUMBER_OF_RESOURCES;i++)
                scanf("%d",&release[i]);
            release_resources(customer_num,release);
        }
        else if(!strcmp(s,"*"))
        {
            printf("Available resources:\n");
            for(i=0;i<NUMBER_OF_RESOURCES;i++)
                printf("%d ",available[i]);
            printf("\nMaximum demand of each customer:\n");
            for(i=0;i<NUMBER_OF_CUSTOMERS;i++)
            {
                printf("Customer %d: ",i);
                for(j=0;j<NUMBER_OF_RESOURCES;j++)
                    printf("%d ",maximum[i][j]);
                printf("\n");
            }
            printf("Currently allocated resources to each customer:\n");
            for(i=0;i<NUMBER_OF_CUSTOMERS;i++)
            {
                printf("Customer %d: ",i);
                for(j=0;j<NUMBER_OF_RESOURCES;j++)
                    printf("%d ",allocation[i][j]);
                printf("\n");
            }
            printf("Remaining need of each customer:\n");
            for(i=0;i<NUMBER_OF_CUSTOMERS;i++)
            {
                printf("Customer %d: ",i);
                for(j=0;j<NUMBER_OF_RESOURCES;j++)
                    printf("%d ",need[i][j]);
                printf("\n");
            }
        }
    }while(strcmp(s,"exit"));
    return 0;
}

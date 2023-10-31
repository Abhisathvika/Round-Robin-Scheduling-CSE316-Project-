#include<stdio.h>
#include<stdlib.h> // Include the necessary library for the rand() function
struct process
{
    char name;
    int arrival_time, burst_time, waiting_time, turnaround_time, remaining_time;
    int completed;
    
}p[100];
int n;
int q[100]; //queue
int front=-1,rear=-1;
void enqueue(int i)
{
    if(rear==100)
        printf("overflow");
    rear++;
    q[rear]=i;
    if(front==-1)
        front=0;
}
int dequeue()
{
    if(front==-1)
        printf("underflow");
    int temp=q[front];
    if(front==rear)
        front=rear=-1;
    else
        front++;
    return temp;
}
int isInQueue(int i)
{
    int k;
    for(k=front;k<=rear;k++)
    {
        if(q[k]==i)
            return 1;
    }
    return 0;
}
void sortByArrival()
{
    struct process temp;
    int i,j;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
        {
            if(p[i].arrival_time>p[j].arrival_time)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
}
int main()
{
    int i,j,time=0,sum_bt=0,tq;
    char c;
    float avgwt=0;
    float avgtt=0;
    printf("Enter no of processes:");
    scanf("%d",&n);
    for(i=0,c='A';i<n;i++,c++)
    {
        p[i].name=c;
        // Generate arrival and burst times
        p[i].arrival_time = rand() % 10; // Generate random arrival time between 0 to 9
        p[i].burst_time = 1 + rand() % 10; // Generate random burst time between 1 to 10
        p[i].remaining_time = p[i].burst_time;
        p[i].completed=0;
        sum_bt+=p[i].burst_time;

    }
    printf("\nEnter the time quantum:");
    scanf("%d",&tq);
    sortByArrival();
    enqueue(0); // enqueue the first process
    printf("\nProcess execution order: ");
    for(time=p[0].arrival_time;time<sum_bt;) // run until the total burst time reached
    {
        i=dequeue();
        if(p[i].remaining_time<=tq)
        {
            time+=p[i].remaining_time;
            p[i].remaining_time=0;
            p[i].completed=1;
            printf(" %c ",p[i].name);
            p[i].waiting_time=time-p[i].arrival_time-p[i].burst_time;
            p[i].turnaround_time=time-p[i].arrival_time;
            
            for(j=0;j<n;j++)
            {
                if(p[j].arrival_time<=time && p[j].completed!=1&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
        }
        else
        {
            time+=tq;
            p[i].remaining_time-=tq;
            printf(" %c ",p[i].name);
            for(j=0;j<n;j++)
            {
                if(p[j].arrival_time<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
                {
                    enqueue(j);
                }
            }
            enqueue(i);
        }
    }
    printf("\nThe Processes are sorted in terms of their arrival time... ");
    printf("\n\n Name\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time");
    for(i=0;i<n;i++)
    {
        avgwt+=p[i].waiting_time;
        avgtt+=p[i].turnaround_time;
        printf("\n  %c\t\t%d\t\t%d\t\t%d\t\t%d",p[i].name,p[i].arrival_time,p[i].burst_time,p[i].waiting_time,p[i].turnaround_time);
    }
    printf("\nAverage waiting time:%0.2f\n",avgwt/n);
    printf("Average Turnaround time:%0.2f\n",avgtt/n);
    
    return 0;
}


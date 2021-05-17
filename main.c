#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 */
typedef struct
{
    char* name;
    int starting_time;
    int remaining_time;
} Process;
/*
 *
 */
typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node *first;
    Node *rear ;
} Queue;
/*
 *
 */
Queue* init()
{
    Queue* q;
    q = (Queue*)malloc(sizeof(q));
    q->first = NULL;
    q->rear = NULL;
    return q;
}
/*
 *
 */
int isEmpty(Queue* q)
{
    if (q->first == NULL)
        return 1;
    else
        return 0;
}
int isFull(Queue* q)
{
    Node* t = malloc(sizeof(Node));
    if (t == NULL)
        return 1;
    else
        return 0;
}

Process dequeue(Queue* q)
{
    Process x;
    x.name = NULL;
    x.remaining_time = 0;
    x.starting_time = 0;

    if (isEmpty(q))
        return x;
    else {
        Node* temp = malloc(sizeof(Node));
        temp->data = q->first->data;
        if (q->first == q->rear) {
            q->rear = NULL;
            q->first = NULL;
        }
        else
            q->first = q->first->next;
        return temp->data;
    }
    
}
/*
 *
 */
void enqueue(Queue* q, Process x)
{
    if (isFull(q))
        return;
    else {
        Node* temp = malloc(sizeof(Node));
        temp->data = x;
        if (q->first == NULL) {
            q->first = temp;
            q->rear = temp;
        }
        else {
            q->rear->next = temp;
            q->rear = temp;
        }
    }
}
/*
 *
 */
void destroy(Queue* q)
{
    free(q->first->next);
    free(q->rear->next);
    free(q->first);
    free(q->rear);
    free(q);
}
void RoundRobin(char* filename)
{
    int time_counter = 0;
    int time_slot ;
    char temp[3] ;
    int process_number = 0;

    FILE* f;
    char line[50], str[10];
    int numOfProcess = -1, x = 0;
    Queue* q = init();
    Process* p = malloc(100 * sizeof(Process));
    f = fopen(filename, "r");
    fgets(line, 25, f);
    str[0] = line[22];
    str[1] = line[23];
    str[2] = '\0';
    time_slot = atoi(str);
    while (fgets(line, 25, f) != NULL) {
        numOfProcess++;
    }
    fclose(f);
    f = fopen(filename, "r");
    fgets(line, 25, f);
    while (!feof(f))
    {
        p[x].name = malloc(100);
        fscanf(f, "%2s", p[x].name);
        fscanf(f, " %d ", &p[x].starting_time);
        fscanf(f, "%d/n", &p[x].remaining_time);
        x++;
    }
    int i = 0;
    int relate = 0;
    while(relate != time_slot)
    {
        if (p[i].starting_time == relate) {
            enqueue(q,p[i]);
            i++;
        }
        else if(!isEmpty(q)){
            if ( q->first->data.remaining_time > 1) {
                printf("%s (%d --> %d)\n", q->first->data.name,relate, relate+1);
                relate++;
                Node* temp;
                temp = q->first;
                temp->data.remaining_time--;
                dequeue(q);
                if (p[i].starting_time == relate) {
                    enqueue(q, p[i]);
                    i++;
                }
                enqueue(q, temp->data);
            }
            else if (q->first->data.remaining_time == 1) {
                printf("%s (%d --> %d) %s aborts\n", q->first->data.name,relate,relate+1, q->first->data.name);
                relate++;
                dequeue(q);
            }
        }
        if (isEmpty(q) && p[i].starting_time != relate&& relate != time_slot) {
            printf("idle (%d --> %d)\n", relate, relate + 1);
            relate++;
        }
    }
}
/*
 *
 */
int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while (fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename) - 1] = '\0';
        if (fopen(filename, "r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}

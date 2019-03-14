#include <stdio.h>
#include <stdlib.h>

typedef struct node *nodePointer;

typedef struct node{
    char character;
    int frequency;
    nodePointer leftChild;
    nodePointer rightChild;
};
nodePointer priorityQueue[300];

char input[10005],code[10005];
int  freq[10005],final_size = 0;

void push(nodePointer item, int *n)
{
    if(n == 299)
    {
        printf("the queue is full");
        //exit(EXIT_FAILURE);
    }
    int i = ++(*n);

    while((i!=1) && (item->frequency <= priorityQueue[i/2]->frequency))
    {
        priorityQueue[i] = priorityQueue[i/2];
        i /= 2;
    }
    //printf("111\n");
    priorityQueue[i] = item;
    //printf("%c %d\n",priorityQueue[i]->character,priorityQueue[i]->frequency);
}

nodePointer pop(int *n)
{
    int parent, child;
    nodePointer item, temp;

    item = priorityQueue[1];
    temp = priorityQueue[(*n)--];
    parent = 1;
    child = 2;

    while(child <= *n)
    {
        if( (child < *n) &&
           (priorityQueue[child]->frequency > priorityQueue[child+1]->frequency))
            child++;

        if(temp->frequency <= priorityQueue[child]->frequency) break;

        priorityQueue[parent] = priorityQueue[child];
        parent = child;
        child *= 2;
    }
    priorityQueue[parent] = temp;
    return item;
}

void merge(nodePointer *a,nodePointer *b,int *n)
{
    nodePointer temp;
    temp = malloc(sizeof(*temp));

    temp->leftChild = *a;
    temp->rightChild = *b;
    temp->character = '\0';
    temp->frequency = (*a)->frequency + (*b)->frequency;

    push(temp,n);
}

void dfs(nodePointer *t,int cnt)
{
    if((*t)->leftChild)
    {
        code[cnt] = '0';
        dfs(&((*t)->leftChild),cnt+1);
    }
    if((*t)->character != '\0')
    {
        int i;
        printf("%c %d ",(*t)->character,(*t)->frequency);
        for(i = 0 ; i < cnt ; i++)  printf("%c",code[i]);
        printf("\n");
        final_size += (*t)->frequency * cnt;
    }
    if((*t)->rightChild)
    {
        code[cnt] = '1';
        dfs(&((*t)->rightChild),cnt+1);
    }
}



int main()
{
    int n = 0;
    freopen("text.txt","r",stdin);
    freopen("code.txt","w",stdout);
    while(fgets(input,10005,stdin) != NULL)
    {
        final_size = 0;
        for(int i=0;i<10005;i++)    freq[i] = 0;
        for(int i=0;i<strlen(input);i++)
        {
            if(input[i] == '\n') continue;
            int tmp = input[i] - ' ';
            //printf("%d\n",tmp);
            freq[tmp]++;
        }
        for(int i=0;i<10005;i++)
            if(freq[i] > 0)
            {

                nodePointer temp;
                temp = malloc(sizeof(*temp));
                temp->character = i + ' ';
                temp->frequency = freq[i];
                temp->leftChild = NULL;
                temp->rightChild = NULL;
                //printf("%d %d\n",i,freq[i]);
                push(temp,&n);
                //printf("%d %d\n",i,freq[i]);
            }
        /*for(int i=1;i<n;i++)
            printf("%c %d\n",priorityQueue[i]->character,priorityQueue[i]->frequency);*/
        if(!n) printf("n = 0,error\n");
        while(n>1)
        {
            //printf("%d\n",n);
            //printf("!!%c %d\n",priorityQueue[1]->character,priorityQueue[1]->frequency);
            nodePointer a = pop(&n);
            nodePointer b = pop(&n);
            //printf("%c %d\n%c %d\n",a->character,a->frequency,b->character,b->frequency);
            merge(&a,&b,&n);
        }
        //printf("%c %d\n",priorityQueue[1]->character,priorityQueue[1]->frequency);
        dfs(&priorityQueue[1],0);
        printf("%d\n",final_size);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}

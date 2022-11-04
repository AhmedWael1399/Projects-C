#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<unistd.h>
#include<time.h>
#include<semaphore.h>

int sharedInteger;

typedef struct {
    int front, rear, size;
    unsigned capacity;
    int* array;
}Queue;
 
/* Function to Create a Queue */
 Queue* createQueue(unsigned capacity)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}
 
/* When Queue is Full */ 
 int isFull(Queue* queue)
{
    return (queue->size == queue->capacity);
}


/* When Queue is Empty */
int isEmpty(Queue* queue)
{
    return (queue->size == 0);
}
 
/* Function to Add an Item to the Queue */
void enqueue(Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}
 
/* Function to Remove an Item From Queue */
int dequeue(Queue* queue)
{
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}


/* Function to get front of queue */
int front(Queue* queue)
{
    return queue->array[queue->front];
}
 
/* Function to get rear of queue */
int rear(Queue* queue)
{
    return queue->array[queue->rear];
}


/* Creating Two Semaphores */
 sem_t shared;
 sem_t sfull;
 sem_t sempty;
 sem_t sbufferSize;
 
/* Shared Buffer */
 Queue* dataBuffer;

/* Number of Messages */ 
 int messageNumber;
 
/* Producer Function */
 void *Producer(void *arg) {
  while (1)
  {
  sleep(rand() % 5 + 1);
  printf("Monitor thread: waiting to read counter\n");
  sem_wait(&shared);
  int saveInt = sharedInteger;
  sharedInteger = 0;
  printf("Monitor thread: reading a count value of %d\n",saveInt);
  sem_post(&shared);
  sem_wait(&sbufferSize);
  sem_wait(&sempty);
  enqueue(dataBuffer,saveInt);
  printf("Monitor thread: writing to buffer at position %d\n",rear(dataBuffer));
  sem_post(&sempty);
  sem_post(&sfull);
  if (isFull(dataBuffer))
  printf("Monitor thread: Buffer full!!\n");
  }
}

/* Consumer Function */
 void *Consumer(void *arg) {
  while (1)
  {
  sleep(rand() % 5 + 1);
  sem_wait(&sfull);
  sem_wait(&sempty);
  dequeue(dataBuffer);
  printf("Collector thread: reading from buffer at position %d\n",front(dataBuffer));
  sem_post(&sempty);
  sem_post(&sbufferSize);
  if (isEmpty(dataBuffer))
  printf("Collector thread: nothing is in the buffer!\n");
  
  }
}

/* Counter Function */
 void *Counter(void *arg){
 unsigned long int counterID = pthread_self();
 while(1)
 {
 sleep(rand() % 5 + 1);
 printf("Counter thread %lu: received a message\n",counterID);
 printf("Counter thread %lu: waiting to write\n",counterID);
 sem_wait(&shared);
 sharedInteger++;
 printf("Counter thread %lu: now adding to counter,counter value = %d\n",counterID,sharedInteger);
 sem_post(&shared);
 }
}
 
int main(){

 dataBuffer = createQueue(20);
 int i;
 
/* Creating a Number of Messages */
 printf ("Enter the number of Messages you want to create:");
 scanf("%d",&messageNumber);
 printf("\n\n");
 
/* Initialize the Semaphores */
  sem_init(&shared,0,1);
  sem_init(&sempty, 0, 1);
  sem_init(&sfull, 0, 0);
  sem_init(&sbufferSize, 0, 20);
 
/* Create the Threads */
 pthread_t counter[messageNumber];
  pthread_t monitor;
  pthread_t collector;
  
  for (i = 0;i < messageNumber;i++)
  pthread_create(&counter[i], NULL, Counter, NULL);
  
  pthread_create(&monitor, NULL, Producer, NULL);
  pthread_create(&collector, NULL, Consumer, NULL);
  
/* Joining the Threads */ 
  for (i = 0; i < messageNumber; i++)
   pthread_join(counter[i], NULL);   
       
  pthread_join(monitor, NULL);
  pthread_join(collector, NULL);

return 0;

}

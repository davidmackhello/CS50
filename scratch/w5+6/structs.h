/**
 * structs.h
 *
 * Computer Science 50
 * Week 6 Practice
 *
 * Define structs for singly-linked lists
 */
 #define CAPACITY 10
 
 typedef struct node
 {
     int val;
     struct node* next;
 }
 node;
 
typedef struct
 {
  int array[CAPACITY];
  int top;
 }
 stack;
 
 
typedef struct stackl
 {
     int val;
     struct stackl* next;
 }
 stackl;
 
 typedef struct
 {
  int array[CAPACITY];
  int size;
  int front;
 }
 queue;
 
 typedef struct queuel
 {
     int val;
     struct queuel* next;
 }
 queuel;
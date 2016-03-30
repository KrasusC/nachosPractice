// threadtest.cc
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield,
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
	printf("Thread is stated with tid : %d\n", currentThread->getTid());
    for (num = 0; num < 100; num++) {
		IntStatus oldLevel = interrupt->SetLevel(IntOn);
		//printf("in : %d\n", currentThread->getTid());
		interrupt->SetLevel(IntOff);
		interrupt->SetLevel(oldLevel);
    }
	printf("Thread is finished with tid : %d\n", currentThread->getTid());
}

void PrintThread(int which) {
	printf("This thread is printed with tid : %d\n", currentThread->getTid());
	currentThread->Yield();
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

	for (int priority = 10; priority >= 5; --priority) {
		for (int i = 0; i < 3; ++i) {
			Thread *t = new Thread("forked thread", 1, priority);
			Thread *t1 = new Thread("forked thread", 1, priority - 1);
			Thread *t2 = new Thread("forked thread", 1, priority);
			t->Fork(SimpleThread, 1);
			t1->Fork(SimpleThread, 1);
			t2->Fork(SimpleThread, 1);

		}
	}
	currentThread->Yield();
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}

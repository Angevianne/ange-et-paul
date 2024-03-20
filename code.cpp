/*
Youpi Robot Test program
------------------------
Author: AlphaK - www.alphak.net
Revision: 2010-07-16
This program has to be run as root
or with sufficient credentials (suid...)
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/io.h>
// Change this to your parallel port
#define LPT 0x378
// Defines the byte type
typedef unsigned char byte;
// Defines the time between each instruction
int tempo = 2000;
/*
This functions writes a byte to the parallel port
Do not use any other way to do it as the robot needs to pause
between each instruction.
*/
void writelpt(byte b) {
outb(b, LPT);
usleep(tempo);
}
/*
This is the main function
*/
int main() {
//Variables
int i,j;
int steps = 600;
//Welcome message
printf("*** YOUPI ROBOT TEST PROGRAM ***\n");
//Tries to access parallel port
if(ioperm(LPT, 1, 1) != 0) {
perror("ioperm");
return 1;
}
//Initializes the robot
printf(" * Initialization\n");
writelpt(0x47);
writelpt(0x00);
//Orders earch motor to rotate
for(j=0; j<6; j++) {
printf(" * Test of motor %d\n", j);
//...with the correct tempo value
tempo = (j == 0) ? 2000:1500;
//...into one direction
writelpt(0x80);
writelpt(0x00);
for(i=0; i<steps; i++) {
writelpt(0x40+j);
writelpt(0x00+j);
}
//...into the opposite direction
writelpt(0xBF);
writelpt(0x3F);
for(i=0; i<steps; i++) {
writelpt(0x40+j);
writelpt(0x00+j);
}
}
return 0;
}
Et le Makefile qui va avec :
CC=gcc
CFLAGS=-W -Wall -O
all: robotest
robotest: robotest.c
$(CC) $(CFLAGS) -o $@ $<
clean:
rm robotest
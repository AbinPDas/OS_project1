#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main()
{
int n;
printf("Enter number   ");
scanf("%d",&n);

if(n==0)
{
system("insmod led0.ko");
sleep(10);
system("rmmod led0.ko");
}

 while(n!=0)
 {
   int i;
   i=n%10;
   n=n/10;
if(i==0)
	{
		system("insmod	led0.ko");
		sleep(2);
		system("rmmod led0.ko");
	}
 else if(i==1)
	{
		system("insmod	led1.ko");
		sleep(2);
		system("rmmod led1.ko");
	}
 else if(i==2)
	{
		system("insmod	led2.ko");
		sleep(2);
		system("rmmod led2.ko");
	}
 else if(i==3)
	{
		system("insmod	led3.ko");
		sleep(2);
		system("rmmod led3.ko");
	}
 else if(i==4)
	{
		system("insmod	led4.ko");
		sleep(2);
		system("rmmod led4.ko");
	}
 else if(i==5)
	{
		system("insmod	led5.ko");
		sleep(2);
		system("rmmod led5.ko");
	}
 else if(i==6)
	{
		system("insmod	led6.ko");
		sleep(2);
		system("rmmod led6.ko");
	}
 
 else if(i==7)
	{
		system("insmod	led7.ko");
		sleep(2);
		system("rmmod led7.ko");
	}
 }
}

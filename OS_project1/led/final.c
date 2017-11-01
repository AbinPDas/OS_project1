#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

long int oct_rev(long int n)
{
	int m;
	m = n;
	n = 0;
	while(m)
	{
		
		n = n*10 + m%8;
		if(m%8 == 0)
			n += 8;
		m /= 8;
	}
	return n;
}

long int oct1(long int a)
{
	long int s=0,i=0;
	while(a!=0)
	{
		s += pow(8,i) * (a%10) ;
		a/=10;
		i++;
	}
	return s;
}

void main()
{

	long int n, m, loop, a, b;
	int ch;
	loop = 1;
	while(loop)
	{
		printf("Menu:\n1. Addition\n2. Difference\n3. Multiplication\n4. Division\n5. Modulus\n6. Counter\n7. Exit\n");
		
		scanf("%d", &ch);
		if(ch == 7)
		{
			printf("Shutting down!\n");
			break;
		}
		if(ch != 1 && ch!= 2 && ch != 3 && ch != 4 && ch != 5 && ch != 6 && ch != 7)
		{
			printf("INVALID ENTRY !!\n\n");
			continue;
		}
		if(ch != 6)
		{
		printf("Enter two positive octal numbers a and b \n");
		scanf("%ld %ld", &a, &b);
		a=oct1(a);
		b=oct1(b);
		switch(ch)
		{
			case 1: 
				n = a + b;
				printf("a + b = ");
				break;

			case 2: 
				n = a - b;
				if(n < 0)
				{
					printf("b - a = ");
					n *= -1;
				}
				else
					printf("a - b = ");
				break;

			case 3: 
				n = a*b;
				printf("a * b = ");
				break;

			case 4: 
				n = a/b;
				if(n == 0)
				{
					printf("b / a = ");
					n = b/a;
				}
				else
					printf("a / b = ");
				break;

			case 5:
				n = a%b;
				printf("a mod b = ");
				break;

			default: 
				printf("Shutting Down!\n");
				break;
		}

		n = oct_rev(n);
		fflush(stdout);
		sleep(1);
		 while(n!=0)
		 {
		   int i;
		   i=n%10;
		   n=n/10;
		 if(i==8)
			{
				printf("0");
				fflush(stdout);
				sleep(2);
			}
		 else if(i==1)
			{
				system("insmod	led1.ko");
				printf("1");
				fflush(stdout);
				sleep(2);
				system("rmmod led1.ko");
			}
		 else if(i==2)
			{
				system("insmod	led2.ko");
				printf("2");
				fflush(stdout);
				sleep(2);
				system("rmmod led2.ko");
			}
		 else if(i==3)
			{
				system("insmod	led3.ko");
				printf("3");
				fflush(stdout);
				sleep(2);
				system("rmmod led3.ko");
			}
		 else if(i==4)
			{
				system("insmod	led4.ko");
				printf("4");
				fflush(stdout);
				sleep(2);
				system("rmmod led4.ko");
			}
		 else if(i==5)
			{
				system("insmod	led5.ko");
				printf("5");
				fflush(stdout);
				sleep(2);
				system("rmmod led5.ko");
			}
		 else if(i==6)
			{
				system("insmod	led6.ko");
				printf("6");
				fflush(stdout);
				sleep(2);
				system("rmmod led6.ko");
			}
		 
		 else if(i==7)
			{
				system("insmod	led7.ko");
				printf("7");
				fflush(stdout);
				sleep(2);
				system("rmmod led7.ko");
			}
		}
		}
		else
		{
			int d,l,i;
			printf("Enter the increment value \n"); 
			scanf("%d",&d);
			
			if(d <	0)
			{
				d*=-1;
				d%=8;
				d=8-d;
				d%=8;	
			}

			printf("Enter the number of iterations \n");
			scanf("%d",&l);
			i=0;
			sleep(1);
			while(l--)
			{
			if(i==0)
			{
				printf("0 ");
				fflush(stdout);
				sleep(2);
			}
			else if(i==1)
			{
				system("insmod	led1.ko");
				printf("1 ");
				fflush(stdout);
				sleep(2);
				system("rmmod led1.ko");
			}
			else if(i==2)
			{
				system("insmod	led2.ko");
				printf("2 ");
				fflush(stdout);
				sleep(2);
				system("rmmod led2.ko");
			}
			else if(i==3)
			{
				system("insmod	led3.ko");
				printf("3 ");			
				fflush(stdout);
				sleep(2);
				system("rmmod led3.ko");
			}
			else if(i==4)
			{
				system("insmod	led4.ko");
				printf("4 ");
				fflush(stdout);
				sleep(2);
				system("rmmod led4.ko");
			}
			else if(i==5)
			{
				system("insmod	led5.ko");
				printf("5 ");
				fflush(stdout);
				sleep(2);
				system("rmmod led5.ko");
			}
			else if(i==6)
			{
				system("insmod	led6.ko");
				printf("6 ");
				fflush(stdout);
				sleep(2);
				system("rmmod led6.ko");
			}
		 
			else if(i==7)
			{
				system("insmod	led7.ko");
				printf("7 ");
				fflush(stdout);
				sleep(2);
				system("rmmod led7.ko");
			}
			i+=d;
			i%=8;
			}
		}
			system("insmod led0.ko");
			printf("\nSuccess..!\n");
			fflush(stdout);
			sleep(2);
			system("rmmod led0.ko");  
	}
}

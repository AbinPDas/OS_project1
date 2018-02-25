/****************** SERVER CODE ****************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<unistd.h> //write
#include<pthread.h> //for threading , link with lpthread
//the thread function
void *connection_handler(void *);

int main(int argc, char **argv){
  int welcomeSocket, newSocket,e=0;
  char buffer[30],c[5],username[30],password[30],us[30],pw[30],error1[30],error2[30],recipient[30],msg[100],error3[30],conf[30],del[30];
  strcpy(error1,"Invalid username");
  strcpy(error2,"Invalid password");
  strcpy(error3,"Invalid recipient");
  strcpy(conf,"User recognised"); 
  strcpy(del,"Message delivered");
  pid_t childpid;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (welcomeSocket == -1)
    {
    printf("Could not create socket");
    }

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(atoi(argv[1]));
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr(argv[3]);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Bind the address struct to the socket ----*/
    if( bind(welcomeSocket,(struct sockaddr *)&serverAddr , sizeof(serverAddr)) < 0)
    {
    //print the error message
    perror("bind failed. Error");
    return 1;
    }

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  puts("Waiting for incoming connections...");
while(1)
  {
  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  printf("%s\n","Received request...");
  if ( (childpid = fork ()) == 0 )
  {
   close (welcomeSocket);
   strcpy(buffer,"");
   strcpy(username,"");
   strcpy(password,"");
   strcpy(us,"");
   strcpy(pw,"");
   recv(newSocket,c,5,0);
	if(c[0]=='1')
	{
	while(1)
	{
		   strcpy(username,"");
		recv(newSocket,username,30,0);
		FILE *f1;
		f1 = fopen("senderlist.txt","r");
		do
		{
			strcpy(us,"");
   			strcpy(pw,"");
			fscanf(f1,"%s %s",us,pw);
			if(strcmp(username,us)==0)
			{
				e=1;
				break;
			}				
		}while(!feof(f1));
		if(e==0)
		{
			send(newSocket,error1,30,0);
		}
		else
		{
			send(newSocket,conf,30,0);
			strcpy(password,"");
			recv(newSocket,password,30,0);
			if(strcmp(password,pw)==0)
			{
				send(newSocket,conf,30,0);	
				break;
			}
			else
			{
				send(newSocket,error2,30,0);
			}
		}
	}
	while(1)
	{
		strcpy(recipient,"");
		strcpy(buffer,"");
		recv(newSocket,recipient,30,0);

		int clientSocket;
  		struct sockaddr_in serverAddr;
  		socklen_t addr_size;

  		clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
 		serverAddr.sin_family = AF_INET;
  		serverAddr.sin_port = htons(atoi(argv[2]));
  		serverAddr.sin_addr.s_addr = inet_addr(argv[3]);
  		memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  		addr_size = sizeof serverAddr;
  		connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  		send(clientSocket, recipient, 30, 0);
		recv(clientSocket, buffer, 30, 0);
		
		if(!(strcmp(error3,buffer))==0)
		{
			send(newSocket,conf,30,0);
			strcpy(msg,"");
			recv(newSocket,msg,100,0);
			send(clientSocket,username,100,0);
			send(clientSocket,msg,100,0);
			send(newSocket,del,30,0);
			break;
		}
		else
		{
			send(newSocket,error3,30,0);
		}
	}
	}
	else
	{
		strcpy(us,"");
		strcpy(pw,"");
		recv(newSocket,us,30,0);
		recv(newSocket,pw,30,0);
		FILE *f2;
		f2 = fopen("senderlist.txt","a");
		fprintf(f2,"%s %s\n",us,pw);
		exit(0);
	}
    }
  close(newSocket);
   }
  return 0;
}
  

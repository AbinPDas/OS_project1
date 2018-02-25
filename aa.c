/****************** CLIENT CODE ****************/
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char**  argv){
  int clientSocket,len;
  char c[5];
  float res;
  char buffer[1024],buffer1[1024],username[30],password[30],error1[30],error2[30],recipient[30],msg[100],error3[30];
  strcpy(error1,"Invalid username");
  strcpy(error2,"Invalid password");
  strcpy(error3,"Invalid recipient"); 
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(atoi(argv[1]));
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr(argv[2]);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  printf("Enter your choice : \n1.Login\n2.New user\n");
  scanf("%s",c);
  send(clientSocket,c,5,0);
  if(c[0]=='1'){
  while(1)
  {
        strcpy(buffer,"");
        strcpy(username,"");
  	printf("Enter username : ");
  	scanf("%s",username);
  	send(clientSocket, username,30, 0);
  	recv(clientSocket, buffer, 30, 0); 
  	printf("%s\n",buffer);
  	if(!(strcmp(buffer,error1)==0))
  	{
		strcpy(buffer,"");
		strcpy(password,"");
  		printf("Enter password : ");
  		scanf("%s",password);	
  		send(clientSocket, password,30, 0);
		recv(clientSocket,buffer,30,0);
		if(strcmp(buffer,error2)==0)
		{
			printf("%s\n",buffer);
		}
		else 
			break;
  	}
  }
while(1)
  {	
        strcpy(recipient,"");
        strcpy(buffer,"");
	printf("Enter the recipient address\n");
	gets(recipient);
    	send(clientSocket, recipient,30, 0);
  	recv(clientSocket, buffer, 30, 0);
        if(!(strcmp(buffer,error3))==0)
	{
		strcpy(msg,"");
		strcpy(buffer,"");
		printf("Enter the messsage\n");
		gets(msg);
                send(clientSocket, msg,100,0);
		recv(clientSocket,buffer,30,0);
		printf("%s\n",buffer);
		break;
	}
	else
	{
		printf("%s\n",buffer);
	}       
  }	
  }
  else
  {
        strcpy(password,"");
        strcpy(username,"");
	printf("Enter username : ");
	scanf("%s",username);
	send(clientSocket, username,30, 0);
	printf("Enter password : ");
	scanf("%s",password);
	send(clientSocket, password,30, 0);
  }

  return 0;
}

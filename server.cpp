
#if 0
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



int main(int argc, char *argv[])
{
   int socket_server;
   int socket_client;
   char buffer[2048] = {'\0'};
   int portno;
   sockaddr_in server_address, client_address;
 
   socket_server = socket(AF_INET, SOCK_STREAM, 0);

   if( socket_server < 0)
    { 
       printf("Error Creando el Socket\n");
       return -1;
    }   
   bzero((char *) &server_address, sizeof(server_address));
   bzero((char *) &client_address, sizeof(client_address));
   if( argc > 2 )
     portno = atoi(argv[1]);
   else
     portno = 5461;

   server_address.sin_family      = AF_INET;
   server_address.sin_port        = htons(portno);
   server_address.sin_addr.s_addr = INADDR_ANY;


    if (bind(socket_server, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
         {
            printf("ERROR on binding");
         }
    if( listen(socket_server ,5)  < 0 )
      {
           printf("Error listening \n");
           return -1; 
     } 

   unsigned int clilen = sizeof(client_address);
    
  while(1){
		   
            socket_client  = accept(socket_server, (struct sockaddr *) &client_address, &clilen);
	    if (socket_client < 0)
			 {
			    printf("ERROR on accept");
			    return -1;
			 }
		    int n = read(socket_client,buffer,255);
		    if (n < 0)
                       {
                          printf("ERROR reading from socket");
                          return -1; 
                       }
		    printf("Here is the message: %s",buffer);

         }




}

#endif


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
 
int main(void)
{
  int listenfd = 0,connfd = 0;
  
  struct sockaddr_in serv_addr;
 
  char sendBuff[1025];  
  int numrv;  
 
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socket retrieve success\n");
  
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
      
  serv_addr.sin_family = AF_INET;    
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  serv_addr.sin_port = htons(5000);    
 
  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }     
  
  while(1)
    {      
      connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
  
      strcpy(sendBuff, "Message from server");
      write(connfd, sendBuff, strlen(sendBuff));
 
      close(connfd);    
      sleep(1);
    } 
 
  return 0;
}

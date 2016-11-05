#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
int socket_desc,port;
struct sockaddr_in server;
char message[100],server_reply[2000],IPa[20],rbg[25],rul[100];

socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}

printf("Please enter the IP:\n");
scanf("%s",IPa);
printf("Please enter the port number:\n");
scanf("%d",&port);

server.sin_addr.s_addr = inet_addr(IPa);
server.sin_family = AF_INET;
server.sin_port = htons(port);

if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("connect error");
return 1;
}
puts("Connected\n");

memset(rbg,0,sizeof(rbg));
read(socket_desc,rbg,sizeof(rbg));
printf("%s\n",rbg);

memset(rul,0,sizeof(rul));
read(socket_desc,rul,sizeof(rul));
printf("%s\n",rul);

while(1)
{
scanf("%4s",message);
if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
puts("Data Send\n");

if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
		puts("recv failed");
	}
puts("Reply received\n");
puts(server_reply);
}

close(socket_desc);
return 0;
}

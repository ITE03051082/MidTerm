#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<time.h>

int main(int argc , char *argv[])
{
int socket_desc,new_socket,sc,i,j,k,l,a,b;
struct sockaddr_in server,client;
char *message,str[4],Ans[4],rec[100];
time_t mytime;
mytime=time(NULL);

socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
	printf("Could not create socket");
}

server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons( 6666 );

if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
	puts("bind failed");
	return 1;
}

puts("bind done");
listen(socket_desc , 3);
puts("Waiting for incoming connections...");
sc = sizeof(struct sockaddr_in);

while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&sc)) )
{
puts("Connection accepted");
srand(time(NULL));

for(k=0;k<4&&(Ans[k]=rand()%10+48);k++)
	for(l=0;l<k;l++)
		Ans[l]==Ans[k]&&k--;
printf("Ans:%s\n",Ans);

write(new_socket,"Let's play a game...",25);

write(new_socket,"將隨機產生一組不重複4位數字\n可以猜到對為止！\n\n那麼就開始吧！！\n",100);

while(1)
{
a=0,b=0,i=0;
bzero(str,4);
read(new_socket,str,4);

for(;i<4;i++)
	for(j=0;j<4;j++)
		Ans[i]==str[j]&&(i==j?a++:b++);

if(a==4)
{
	message="恭喜答～～～對了！";
	write(new_socket,message,strlen(message)+1);
	puts("The game is over.");
	close(new_socket);
	return 0;
}
else
{
	sprintf(rec,"%dA%dB",a,b);
	write(new_socket,rec,strlen(rec)+1);
}
}
}

if (new_socket<0)
{
	perror("accept failed");
	return 1;
}
return 0;
}

#include "head.h"
int main (int argc, char *argv[])
   {
	printf("client welcome\n");
	const char * ip="/*server ip*/";
	int sockfd,n;
	socklen_t ser_addrlen;
	char send_msg[1024],recv_msg[1024];
	struct  sockaddr_in ser_addr,cli_addr;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
		{
			fprintf(stderr,"socket error\n");
			exit(1);
		}
	bzero(&ser_addr,sizeof(ser_addr));
	bzero(&cli_addr,sizeof(cli_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = inet_addr(ip);
	ser_addr.sin_port = htons(Ser_Port);
	
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	cli_addr.sin_port = htons(Cli_Port);
	if((bind(sockfd,(struct sockaddr *)&cli_addr,sizeof(cli_addr))) < 0)
		printf("bind error\n");
	
	while(1)
		{
			fgets(send_msg,1024,stdin);
			int sendto_flag = sendto(sockfd,send_msg,sizeof(send_msg),0,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
			if(sendto_flag==-1)
			{
				printf("send error\n");
			}else{
				printf("send ok\n");
			}
			n = recvfrom(sockfd,recv_msg,sizeof(recv_msg),0,(struct sockaddr *)&ser_addr,&ser_addrlen);
			printf("%s\n",recv_msg);
		}
}



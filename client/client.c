#include "head.h"
void joint(char * str1,char * str2){
	int len1=strlen(str1);
	int len2=strlen(str2);
	for (int i = len2; i >0; i--)
	{
		if(str1[len1-1-i]==str2[len2-i-1]){
			str1[len1-1-i]=0x00;
		}
	}
}
int main (int argc, char *argv[])
   {
	printf("client welcome\n");
	const char * ip="211.149.189.154";
	//const char * ip="127.0.0.1";
  int sockfd,n,sn;
	char token[]={"aong"};
	socklen_t ser_addrlen;
	struct fd_set fdset;
	struct timeval timeout;
	
	timeout.tv_sec = 3;
	timeout.tv_usec = 500;

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
	ser_addr.sin_port = htons(65535);
	
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	cli_addr.sin_port = htons(65534);
	if((bind(sockfd,(struct sockaddr *)&cli_addr,sizeof(cli_addr))) < 0)
		printf("bind error\n");
	
	while(1)
		{
//			fgets(send_msg,20,stdin);
//			int sendto_flag = sendto(sockfd,send_msg,sizeof(send_msg),0,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
//			if(sendto_flag==-1)
//			{
//				printf("send error\n");
//			}else{
//				printf("send ok\n");
//			}
			FD_ZERO(&fdset);
			FD_SET(0,&fdset);
			FD_SET(sockfd,&fdset);

			sn = select(sockfd+1,&fdset,NULL,NULL,&timeout);

			if(sn == 0){
				continue;
			}else if(sn < 0 && errno == EINTR)
				continue;
			
			if(FD_ISSET(0,&fdset)){
				fgets(send_msg,20,stdin);
				int sendto_flag = sendto(sockfd,send_msg,sizeof(send_msg),0,(struct sockaddr *)&ser_addr,sizeof(ser_addr));
		         if(sendto_flag == -1)
		          {
		              printf("send error\n");
		          }
			}

			if(FD_ISSET(sockfd,&fdset)){
				n = recvfrom(sockfd,recv_msg,sizeof(recv_msg),0,(struct sockaddr *)&ser_addr,&ser_addrlen);
				if (n == -1){
				printf("no resv");
				exit(1);
				}else{
					joint(recv_msg,token);
				    printf("%s\n",recv_msg);
			}
			}
		}
}



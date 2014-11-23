#include "head.h"

int cheakip(unsigned int ip[],int m,unsigned int address ){
	int i;
	for(i=1;i<=m;i++){
		if(ip[i] != address)
			if(i != m)
			   continue;
			else
			{ 
			  ip[m+1] = address;
			   m++;
			   printf("addipok");
			   return(1);
			}
		else
			break;
		}
	return(0);
	}

int main (){
  printf("server welcome\n");
  const char *ip="127.0.0.1";
  int sockfd,i,j=1,n=1;
  socklen_t cli_addrlen = sizeof(struct sockaddr_in);
  char msg[20],send_msg[20];
  struct sockaddr_in ser_addr,cli_addr;
  sockfd = socket(AF_INET,SOCK_DGRAM,0);

  memset(&ser_addr,0,sizeof(struct sockaddr_in));
  ser_addr.sin_family = AF_INET;
  inet_aton(ip,&ser_addr.sin_addr);
  ser_addr.sin_port = htons(Ser_Port);
  
  bind(sockfd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_in));
  
  	unsigned int cliaddrtmp,addr[5];
	memset(addr,0,20);
  while(1){
	if ((recvfrom(sockfd,msg,sizeof(msg),0,(struct sockaddr *)&cli_addr,&cli_addrlen)) == -1){
		printf("recvfrom error\n");
		exit(1);
	}else{
	cliaddrtmp = cli_addr.sin_addr.s_addr;
	if (j == 1){
		addr[1] = cli_addr.sin_addr.s_addr;
		j--;
	}
	printf("recved %u:%s\n",cli_addr.sin_addr.s_addr,msg);
	if((cheakip(addr,n,cli_addr.sin_addr.s_addr)) == 1){
		n++;
	};
	for(i=1;i<=n;i++){
		if(cliaddrtmp != addr[i]){
		cli_addr.sin_addr.s_addr = addr[i];
		printf("added %d:%u\n",cli_addr.sin_addr.s_addr,cli_addr.sin_addr.s_addr);	
		if((sendto(sockfd,msg,sizeof(msg),0,(struct sockaddr *)&cli_addr,sizeof(cli_addr))) != -1){
		printf("sendto:%s\n",inet_ntoa(cli_addr.sin_addr));
			}
		}
		}
	printf("%u\n%u\n",addr[1],addr[2]);
	}		
 }
  close(sockfd);
}

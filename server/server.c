#include "head.h"
#include "function.h"
void joint(char* str1,char* str2){
 int len1,len2;
 len1=strlen(str1);
 len2=strlen(str2);
 int i=0;
 for(i=0;i<len2;i++){
  str1[len1+i-1]=str2[i];
 }
  str1[len1+len2-1]=0x00;    
}
int main (int argc, char * argv[]){
	printf("server welcome\n");
	int sockfd,i=0,k=0;
	char* token="aong";
	char test[1]={'y'};
	socklen_t cli_addrlen = sizeof(struct sockaddr_in);
	char msg[1024];
	char send_msg[1024];
	struct sockaddr_in ser_addr,cli_addr;
	///////////////
	//创建客户端结构表
	//struct client_addr{
	//	int id;
	//	in_addr_t addr;
	//} client_addr;
	char* msgData[10];
	int msgData_length=0;
	for(i=0;i<=9;i++){
	  msgData[i]=(char*)malloc(1024);
	}
	sockfd = socket(AF_INET,SOCK_DGRAM,0);

		if(sockfd < 0){
			printf("socket error\n");
			exit(1);
		}
	memset(&ser_addr,'0',sizeof(struct sockaddr_in));
	memset(&cli_addr,'0',sizeof(struct sockaddr_in));

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(Ser_Port);
	inet_aton("211.149.189.154",&ser_addr.sin_addr);

	if(bind(sockfd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr_in)) == -1){
		printf("bind error\n");
		exit(1);
	}
	while(1){
		int n,m;

		if(( n = recvfrom(sockfd,msg,sizeof(msg),0,(struct sockaddr *)&cli_addr,&cli_addrlen)) == -1){
		printf("recvfrom error\n");
		exit(1);
		}else{
		  memcpy(send_msg,"0",1024);		
		  strcpy(send_msg,msg);
		  if(msg[0]==test[0]) continue;
		  joint(send_msg,token);
		 
		  if(msgData_length==0){
			strcpy(msgData[msgData_length],send_msg);
			msgData_length=1;
		  //}else{
		  	save(msgData,msgData_length);
			//for (i = 0; i < 1; ++i){
			  memcpy(msgData[0],"0",sizeof(*msgData[0]));
			//}
			msgData_length=0;
			//strcpy(msgData[msgData_length],send_msg);
			//msgData_length=1;
  		  } 
		}
	
	
	}
	close(sockfd);
}



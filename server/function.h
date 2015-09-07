/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 三  9/ 2 08:47:41 2015
 ************************************************************************/
char* compound_query(char* query,char* value);
int save(char* msg[],int length){
  MYSQL mysql,*sock;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[100]="insert into chat_msg (msg) values ('#')";
  int i;
  //char query_old[100]="insert into chat_msg (msg) values ('#')";
  
  mysql_init(&mysql);
  if(!(sock=mysql_real_connect(&mysql,"localhost","root","1234","yoooooou",0,NULL,0))){
    //fprintf(stderr,"Couldn't connect to engine!\n%s\n\n",mysql_error(&mysql));
    return 0;
  }
  mysql_set_character_set(&mysql,"utf8");
  for (i = 0; i < length; ++i)
  { 
      if(mysql_query(sock,(char*)compound_query(query,msg[i]))){
         //fprintf(stderr,"Query failed (%s)\n",mysql_error(sock));
         return 0;
        }else{
          //printf("%sis ok\n",msg[i]);
        }
        //strcpy(query,query_old);
      // if (!(res=mysql_store_result(sock))) {
      //           fprintf(stderr,"Couldn't get result from %s\n", mysql_error(sock));
      //           return 1;
            
      // }

      //   while((row = mysql_fetch_row(res)))
      //   {
      //     printf("%s:%s\n",row[0],row[1]); 
      //   }
  }
 // mysql_free_result(res);
  mysql_close(sock);
  return 1;
}

/*query="insert into chat_msg (msg) values ('#')";
 *value="hello"
 *compound_query(query,value);
 *用 value 替换 query 中的 # 号
 *结果如下
 *insert into chat_msg (msg) values ('hello')
 */
char* compound_query(char* query,char* value){
  int value_length=strlen(value);
  int query_length=strlen(query);
  int move_length=0;
  int i,j,k;
  static char tmp[100];
  memcpy(tmp,"0",sizeof(tmp));
  strcpy(tmp,query);
  for (i = 0; i < query_length+value_length;)
  { 
    //从两边开始一起判断
    if(tmp[i]=='#' || tmp[query_length-1-i]=='#'){ 
      if(tmp[i]=='#'){
          //要移动的字符的长度
          move_length=query_length-1-i; 
        }else{
          move_length=i; 
        }
        //把＃号后面的字符往后移value_length个长度
        for (j = 0; j < move_length; ++j)
        {
          tmp[query_length+value_length-2-j]=tmp[query_length-1-j];
        }
        //末尾填充0
        tmp[query_length+value_length-1]=0x00;
        //用value的值填充空出的位置
        if(tmp[i]=='#'){
          for (k  = 0; k < value_length; ++k){
            tmp[i+k]=value[k];
          }
        }else{
          for (k  = 0; k < value_length; ++k){
            tmp[query_length-1-i+k]=value[k];
          }
        }
    //跳过value内部＃号检测
    i=i+value_length-1;
    }
    i++;
  }
  return tmp;
}




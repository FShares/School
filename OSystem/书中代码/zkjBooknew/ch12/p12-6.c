void init_sockaddr(struct sockaddr_in *name, const char *hostname, 
                     const char *serv)
{
   struct hostent *hp;
   char *host, myname[255];
   if (hostname == NULL){
      gethostname(myname, sizeof(myname));
      host = myname;
   }
   else
      host = hostname;
   /* 获取主机地址信息 */
   if ((hp = gethostbyname(host)) == NULL){
      printf("Unknown host: %s\n", host);
      exit(-1);
   }
   /* 填入服务器的IP地址和端口 */
   bzero(name,sizeof(struct sockaddr));
   if (hp->h_addrtype == AF_INET){   
      name->sin_family = AF_INET;
      bcopy(hp->h_addr_list[0], &name->sin_addr, hp->h_length);
      if (serv == NULL)
         name->sin_port = htons(0); /* 由系统选择一个适当的端口 */
      else
         name->sin_port = htons(atoi(serv));
   } else {
      printf("Unknown address type\n");
      exit(-1);
   }
}

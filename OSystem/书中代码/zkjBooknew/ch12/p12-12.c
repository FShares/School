int check_peer(int sockfd, in_addr_t *refuse_addr_list)
{
   socklen_t  len;
   struct sockaddr_in addr,raddr;
   in_addr_t s_addr, *ap;
   /* 查看与我连接的是谁 */
   len = sizeof(raddr);
   if (getpeername(sockfd, (struct sockaddr *)&raddr, &len) < 0){
      printf("getpeername with socket %d failed\n", sockfd);
      return -1;
   }
   /* 拒绝来自特定地址的连接 */
   s_addr = raddr.sin_addr.s_addr;
   ap = refuse_addr_list;
   for (; ap!=0; ap++)
      if (*ap == s_addr){
         close(sockfd);
         return -1;
      }
   return 0;
}

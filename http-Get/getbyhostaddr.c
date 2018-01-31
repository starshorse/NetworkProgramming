/* getbyhostaddr.c */

#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
   struct hostent *hptr;
   struct sockaddr_in addr ;
   int i=0;

   if ( argc != 2 )
   {
      printf("Type <command></command> and <domain name="">\n") ;
      exit(1);
   }

   memset ( &addr, 0, sizeof(addr) ) ;
   addr.sin_addr.s_addr = inet_addr(argv[1]) ;

   hptr = gethostbyaddr( (char*)&addr.sin_addr , 4 , AF_INET);

   if ( !hptr ) 
   {
      printf("gethostbyaddr() error!\n") ;
      exit(1);
   }

   printf("Official Host Name : %s\n", hptr->h_name ) ;
 
   for ( i = 0 ; hptr->h_aliases[i] != NULL ; i++)
      printf("Alias Host Name : %s\n", hptr->h_aliases[i] ) ;

   for ( i = 0 ; hptr->h_addr_list[i] != NULL ; i++)
      printf("IP Address : %s\n", inet_ntoa(*(struct in_addr*)hptr->h_addr_list[i]));
}


// </domain>

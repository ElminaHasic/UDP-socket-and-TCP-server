#include <iostream>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>



int main(int argc, char* argv[])
{
   int fd = socket(AF_INET, SOCK_STREAM, 0);
   if(fd < 0)
   {
     //perror();
     exit(1);
   }

   sockaddr_in server_data;
   bzero(&server_data, sizeof(server_data));
   server_data.sin_family = AF_INET;
   server_data.sin_port= htons(9000);
   server_data.sin_addr.s_addr = htonl(0);
    
   int b = bind(fd, (sockaddr*)(&server_data), sizeof(sockaddr));
    if(b < 0)
      exit(1);

   int l = listen(fd, 3);
   if(l < 0)
     exit(1);

   int new_fd ;
   while((new_fd = accept(fd, nullptr, nullptr)) >=0)
   {
   char data_buffer[5];

   int read_;
   while((read_ = read(new_fd, data_buffer, 5)) >0)
   {

     write(new_fd, data_buffer, 5);
   }

   if(read_ <0)
     exit(1);
   close(new_fd);
   }

   close(fd);
   return 0;


}

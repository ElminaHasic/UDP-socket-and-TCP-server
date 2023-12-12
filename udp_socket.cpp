#include <iostream>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int Buffer_size = 255;

int main(void)
{

  int fd = socket (AF_INET, SOCK_DGRAM, 0);
  if(fd <0)
  {

    exit(1);
  }

  sockaddr_in server_data ;
  bzero(&server_data, sizeof(server_data));

  server_data.sin_family = AF_INET;
  server_data.sin_port = htons(10000);
  server_data.sin_addr.s_addr = htonl(0);

  int b = bind(fd, (sockaddr *)(&server_data), (sizeof(sockaddr_in)));
  if (b <0)
    exit(1);

   
  char data_buffer[Buffer_size +1];

  sockaddr client_data;
  socklen_t size = sizeof(sockaddr);
  int read_ ;
  while((read_ = recvfrom(fd, &data_buffer, Buffer_size,0, &client_data, &size)) != 0)
  {

    data_buffer[read_] = '\0';
    std::cout<< data_buffer <<std::endl;

    sendto(fd, &data_buffer, read_ +1 , 0, &client_data, size);

  }


  close(fd); 
  return 0;
}

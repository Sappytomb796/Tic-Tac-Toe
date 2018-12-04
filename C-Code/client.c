#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/types.h>

#include "epoll.h"   //epoll helper functions to increase readability and commonality
#include "game.h"    //Game files to run tic tac toe
#include "packets.h" //include file for packets

#define MAX_EVENTS 10
#define MAX_SIZE 20

#define SOCKET_EPOLL_NEW_MEMBER (EPOLLIN | EPOLLRDHUP)

int join(char * input);
static int pack_rx(int recfd, struct Pack recv); //deserialize
static int pack_tx(int recfd);           //serialize
int connect_client(int *sockfd);
int epoll_event(int i, int event, struct epoll_event events[], int epollfd);

int main(int argc, char *argv[])
{
  struct epoll_event events[MAX_EVENTS];
  int sockfd;
  int epollfd;
  int waiting_epoll;
  int i;

  if(!connect_client(&sockfd)){
    printf("error on connect socket");
    exit(EXIT_FAILURE); }
  
  if(!build_epoll_obj(&epollfd)){
    printf("error on client build_epoll_obj");
    close(sockfd);
    exit(EXIT_FAILURE); }
  
  if(!add_epoll_member(epollfd, sockfd, SOCKET_EPOLL_NEW_MEMBER)){
    printf("error on client add_epoll_member");
    close(sockfd);
    exit(EXIT_FAILURE); }
  
  //Set up listen for server to talk!
  if(!add_epoll_member(epollfd, STDIN_FILENO, EPOLLIN)){
    printf("error on client add_epoll_member for server");
    close(sockfd);
    exit(EXIT_FAILURE); }

  //Lets just basic bitch this and make an infinite loop we can hard stop out of it to disconnect...
  while(1){
    //waiting_epoll = 0;
    waiting_epoll = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    //printf("waiting_epoll = %d\n\n", waiting_epoll);
    //If something went terribly fucking wrong we need to close the connection and abort.
    if(waiting_epoll == -1){
      printf("error on waiting in client loop\n");
      close(epollfd);
      close(sockfd);
      exit(EXIT_FAILURE);
    }

    epoll_event(i, waiting_epoll, events, epollfd);
  }
  
  return 0;
}


int join(char * input)
{
  return 1;
}

//return 0 on failure
static int pack_rx(int recfd, struct Pack recv)
{
  //read(recfd, &recv, sizeof(&recv));
  
  return 1;
}


int pack_tx(int recfd)
{
  struct Pack * sending;
  
  //write(recfd, sending, sizeof(sending));
}

//Return 0 on failure
int connect_client(int *sockfd)
{
  struct sockaddr_in server_adr = {0};
  
  if(!sockfd)
    return 0;

  *sockfd = socket(PF_INET, SOCK_STREAM, 0);
  if(*sockfd == -1){
    printf("error on connect_client\n");
    return 0;
  }
  
  server_adr.sin_family = AF_INET;
  server_adr.sin_port = htons(28590);
  server_adr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if(connect(*sockfd, (struct sockaddr *)&server_adr, sizeof(server_adr)) != 0){
    printf("Error connecting to the server's socket on sonnect_client\n");
    return 0;
  }

  return 1;
}

//Return 1 on success
int epoll_event(int i, int event, struct epoll_event events[], int epollfd)
{
  int mask = event;

  switch(mask){
  case 1: //General sending 
    //printf("\n\ncase 1\n\n");
    //pack_tx(epollfd);
    break;
  case 2: //Server lost
    printf("error server lost\n");
    exit(EXIT_FAILURE);
  default:
    printf("error from epoll event %d from fd %d in epoll_event", mask, epollfd);
    break;
  }

  return 1;
}

//Ok, this should be calling and sending a packet.  I need to call my serialize packet function and then 
// send the serialized packet instead of this.  Then, I will deserialize the packet on return and this
// should spin.

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/types.h>

#include "epoll.h" //epoll helper functions to increase readability and commonality
#include "game.h"  //Game files to run tic tac toe


#define MAX_EVENTS 10
#define MAX_SIZE 20
#define DISCONNECT (EPOLLRDHUP | EPOLLIN)

int setup_socket(int * serverfd);
static void pack_tx(); //deserialize
static void pack_rx(); //serialize
int epoll_event(int i, int event, struct epoll_event events[], int server, int epollfd);

int main(int argc, char *argv[])
{
  struct epoll_event events[MAX_EVENTS];
  int waiting_epoll;
  int serverfd;
  int epollfd;
  int eventfd;
  int i;

  //Abstract out the setup of the socket
  if(!setup_socket(&serverfd))
    exit(EXIT_FAILURE);

  //Abstract out the epoll setup
  if(build_epoll_obj(&epollfd) == 0)
    exit(EXIT_FAILURE);

  if(add_epoll_member(epollfd, serverfd, EPOLLIN) == 0)
    exit(EXIT_FAILURE);

  //The server should never just stop so we should have our infinite loop
  while(1){
    //This is basically "What should the server do every iteration to 
    // compensate for the game logic now that the connection is established.
    // The answer is wait for an epoll event, and then handle it, rinse and repeat.

    //printf("while loop print check\n");
    waiting_epoll = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if(waiting_epoll == -1){
      printf("error on epoll_wait");
      exit(EXIT_FAILURE); }

    epoll_event(i, waiting_epoll, events, serverfd, epollfd);
  }

  //Technically, we should never safe exit server side...
  return 0;
}

//Return 0 on failure
int setup_socket(int * serverfd)
{
  struct sockaddr_in server_address = {0};
  int working = 1;

  if(!serverfd)
    return 0;

  //open the socket
  *serverfd = socket(PF_INET, SOCK_STREAM, 0);
  if(*serverfd < 0){ //If failed to open the socket
    printf("error opening socket\n");
    return 0; }
  
  //Set the socket settings
  if(setsockopt(*serverfd, SOL_SOCKET, SO_REUSEADDR, &working, sizeof(working)) == -1){
    printf("error setting socket settings\n");
    close(*serverfd);
    return 0; }

  //Set the server address inner parts to default
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(28590);

  //Bind the server and the socket
  if(bind(*serverfd, (struct sockaddr *)&server_address, sizeof(server_address)) != 0){
    printf("error on bind\n");
    close(*serverfd);
    return 0; }
    
  //Listen on the port
  if(listen(*serverfd, MAX_SIZE) != 0){
    printf("error listening\n");
    close(*serverfd);
    return 0; }
    
  return 1;
}

//sending and receiving a void type packet is apparently the best way to do this *shakes head*
static void pack_tx()
{
}

static void pack_rx(int epollfd, int event_epoll)
{
}

int epoll_event(int i, int event, struct epoll_event events[], int server, int epollfd)
{
  int mask = events[i].events;
  int eventfd = events[i].data.fd;

  switch(mask){
  case EPOLLIN:
    //Check to make sure the server is the one to handle this
    if(eventfd == server){
      if(!accept_new_epoll_client(epollfd, eventfd)){
	printf("error on accept_new_epoll_client in server");
	exit(EXIT_FAILURE); }
    } else {
      //We be good and can receive their message
      pack_rx(epollfd, eventfd); }
    break;
  case DISCONNECT:
    //remove client from server shtuff
    break;
  case EPOLLERR:
    printf("Error in epoll option EPOLLERR closing eventfd %d", eventfd);
    close(eventfd);
    break;
  case EPOLLHUP:
    printf("Error in epoll option EPOLLHUP closing eventfd %d", eventfd);
    close(eventfd);
    break;
  default:
    //Lolz, I swear I better not be seeing this...
    printf("error on epoll event not supported: event %d from eventfd %d not supported",
	   mask, eventfd);
    break;	 
  }
  return 1;
}

#include "epoll.h"

//returns 0 on failure
int build_epoll_obj(int * epollfd)
{
  if(!epollfd)
    return 0;
  
  *epollfd = epoll_create1(0);
  if(*epollfd < 0){
    printf("error on epoll creation");
    return 0; }
  
  return 1;
}

//Returns 0 on failure
int add_epoll_member(int epollfd, int clientfd, int events_in)
{
  struct epoll_event event;

  event.events = events_in;
  event.data.fd = clientfd;
  if(epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &event) == -1){
    printf("error adding epoll member");
    return 0; }
  
  return 1;
}

//Return 0 on failure
int rm_epoll_member(int epollfd, int clientfd)
{
  if(epoll_ctl(epollfd, EPOLL_CTL_DEL, clientfd, NULL) == -1){
    printf("error on epoll_ctl in rm_epoll_member");
    return 0; } 
  
  close(clientfd); //Close the client's connection

  return 1;
}

//Return 0 on failure
int accept_new_epoll_client(int epollfd, int listeningfd)
{
  int clientfd;

  //This is connecting the new object and making sure they will get messages
  clientfd = accept(listeningfd, (struct sockaddr *)NULL, NULL);
  if(!clientfd){
    printf("error on epoll accept");
    return 0; }
  return 1;
}

#include <sys/epoll.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#ifndef EPOLL_H
#define EPOLL_H

int build_epoll_obj(int * epollfd);
int add_epoll_member(int epollfd, int clientfd, int events_in);
int rm_epoll_member(int epollfd, int clientfd);
int accept_new_epoll_client(int epollfd, int listeningfd);

#endif

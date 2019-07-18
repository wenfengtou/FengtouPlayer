#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<fcntl.h>

#include <arpa/inet.h>
#include <unistd.h>
//#include "MD5.h"
#define BUF_SIZE  4096

int rtsp_main(int argc, char *argv[]);
int rtsp_add();
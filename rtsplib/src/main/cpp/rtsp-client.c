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


char *filename_buf;
char *ip_buf;
int  recv_data_from_server(int sock_udp_fd1,int sock_udp_fd2);
int creat_udp(int i, int port);

int init_udpsocket(int port, struct sockaddr_in *servaddr, char *mcast_addr)
{

    int err = -1;
    int socket_fd;

    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0 )
    {
        perror("socket()");
        return -1;
    }

    memset(servaddr, 0, sizeof(struct sockaddr_in));
    servaddr->sin_family 	   = AF_INET;
    servaddr->sin_addr.s_addr  = htonl(INADDR_ANY);
    servaddr->sin_port 		   = htons(port);

    err = bind(socket_fd,(struct sockaddr*)servaddr, sizeof(struct sockaddr_in)) ;
    if(err < 0)
    {
        perror("bind()");
        return -2;
    }

    /*set enable MULTICAST LOOP */
    int loop = 1;
    err = setsockopt(socket_fd,IPPROTO_IP, IP_MULTICAST_LOOP,&loop, sizeof(loop));
    if(err < 0)
    {
        perror("setsockopt():IP_MULTICAST_LOOP");
        return -3;
    }

    /* Join multicast group */
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(mcast_addr);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    err = setsockopt(socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreq));
    if (err < 0)
    {
        perror("setsockopt():IP_ADD_MEMBERSHIP");
        return -4;
    }
    return socket_fd;
}

int main(int argc, char *argv[])
{

    int i = 0, j = 0, k = 0;
    char *p;
    p = argv[1];
    ip_buf = (char *)malloc(20);
    filename_buf = (char*)malloc(20);
    char response[33];
    char noncestr[33];
    memset(ip_buf,'\0',20);
    memset(filename_buf,'\0',20);
    while (1)
    {
        if (p[i] <= '9' && p[i] >= '0')
        {
            ip_buf[k] = p[i];
            k++;
        }
        if (p[i] == '.')
        {
            ip_buf[k] = p[i];
            k++;
            j++;
        }
        i++;
        if (j == 3)
        {
            if ((p[i] < '0' || p[i] > '9'))
                break;
        }
        //memcpy(filename_buf, argv[1]+strlen(ip_buf)+9, strlen(argv[1]+strlen(ip_buf)));

    }
    filename_buf=argv[2];
    printf("ip=%s\n", ip_buf);
    printf("filename=%s\n", filename_buf);


    int sock_fd;
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 )
    {
        printf("TCP socket() failed\n");
        exit(1);
    }
    printf("TCP socket() succeed\n");
    printf("sock_fd=%d\n", sock_fd);
    struct sockaddr_in ser_addr;
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    int inet_pton_fd;
    if ((inet_pton_fd = inet_pton(AF_INET, ip_buf, &ser_addr.sin_addr)) < 0)
    {
        printf("TCP inet_pton() failed\n");
        exit(1);
    }
    printf("TCP inet_pton() succeed\n");
    printf("inet_pton_fd=%d\n", inet_pton_fd);
    ser_addr.sin_port = htons(554);
    int connect_fd;
    if ((connect_fd = connect(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr))) < 0)
    {
        printf("TCP connect() failed\n");
        exit(1);
    }
    printf("TCP connect() succeed\n");
    printf("connect_fd=%d\n", connect_fd);


    char buf[4096];
    memset(buf, 0, BUF_SIZE);
    printf("****\n");
    sprintf(buf, "OPTIONS %s RTSP/1.0\r\n"
                 "CSeq:1\r\n"
                 "User-Agent:VLC media player(LIVE555 Streaming Media library version 2012.12.09) "
                 "\r\n"
                 "\r\n",argv[1]);
    printf("send to server %s\n", buf);
    int send_fd;
    if((send_fd = send(sock_fd, buf, strlen(buf), 0)) < 0)
    {
        printf("send() failed\n");
        exit(1);
    }
    printf("send() succeed\n");
    printf("send_fd=%d\n",send_fd);
    char rec_buf[4096];
    memset(rec_buf, 0, BUF_SIZE);
    int recv_fd;
    if ((recv_fd = recv(sock_fd, rec_buf, sizeof(buf), 0)) < 0)   /*sizeof(rec_buf) */
    {
        printf("recv() failed\n");
        exit(1);
    }
    printf("recv() succeed\n");
    printf("recv_fd=%d\n",recv_fd);
    printf("options recv from server is %s\n",rec_buf);


    memset(buf, 0, BUF_SIZE);
    sprintf(buf, "DESCRIBE %s RTSP/1.0\r\n"
                 "CSeq:2\r\n"
                 "User-Agent:VLC media player(LIVE555 Streaming Media library version 2012.12.09)\r\n"
                 "Accept:application/sdp"
                 "\r\n"
                 "\r\n",argv[1]);
    printf("send to server %s\n", buf);
    if((send_fd = send(sock_fd, buf, strlen(buf), 0)) < 0)
    {
        printf("send() failed\n");
        exit(1);
    }
    printf("send() succeed\n");
    printf("send_fd=%d\n",send_fd);
    memset(rec_buf, 0, BUF_SIZE);
    if ((recv_fd = recv(sock_fd, rec_buf, sizeof(buf), 0)) < 0)   /*sizeof(rec_buf) */
    {
        printf("recv() failed\n");
        exit(1);
    }
    printf("recv() succeed\n");
    printf("recv_fd=%d\n",recv_fd);
    printf("describe recv from server is %s\n",rec_buf);

    //string_find(rec_buf,"nonce=",noncestr);


/* 	MD5_Encryption(rec_buf,"rtsp//192.168.10.133:554/ch0_0.264","HTTP","admin",response,noncestr);
	// char str1[] = "admin:www.drv163.com:";
	// char str2[] = "rtsp:rtsp://192.168.10.133:554//ch0_0.264";
	// char response1[33],response2[33],response3[33];
	MD5_Encryption(str1,response1);
	MD5_Encryption(str2,response2);
	// sprintf(response3,"%s:%s:%s",response1,noncestr,response2);
	MD5_Encryption(response3,response);
	// memset(buf,0,BUF_SIZE);
	// sprintf(buf, "DESCRIBE %s RTSP/1.0\r\n"
      // "CSeq:3\r\n"
        // "Transport: RTP/AVP;unicast;client_port=5554-5555\r\n"
       // "Authorization:Digest username=\"admin\",realm=\"www.dvr163.com\",nonce=\"%s\",uri=\"%s\",response=\"%s\"\r\n"

      // "User-Agent:VLC media player(LIVE555 Streaming Media library version 2012.12.09)\r\n"
       // "Accept:application/sdp"
      // "\r\n"
      // "\r\n",argv[1],noncestr,argv[1],response);
	// printf("send to server %s\n", buf);
	// if((send_fd = send(sock_fd, buf, strlen(buf), 0)) < 0)
	// {
		// printf("send() failed\n");
		// exit(1);
	// }
	// printf("send() succeed\n");
	// printf("send_fd=%d\n",send_fd);
	// memset(rec_buf, 0, BUF_SIZE);
	// if ((recv_fd = recv(sock_fd, rec_buf, sizeof(buf), 0)) < 0)   /*sizeof(rec_buf) */
    // {
    // printf("recv() failed\n");
    // exit(1);
    // }
    // printf("recv() succeed\n");
    // printf("recv_fd=%d\n",recv_fd);
    // printf("describe recv from server is %s\n",rec_buf); */


#if 1
    int sock_udp_fd1,sock_udp_fd2;
    sock_udp_fd1=creat_udp(1,5554);  //创建udp端口1
    sock_udp_fd2=creat_udp(2,5555);	 //创建udp端口2
    memset(buf,0,BUF_SIZE);
    sprintf(buf,"SETUP %s RTSP/1.0\r\n"
                "CSeq:4\r\n"
                "Transport: RTP/AVP;unicast;client_port=5554-5555\r\n"
                //  "Authorization:Digest username=\"admin\",realm=\"www.dvr163.com\",nonce=\"%s\",uri=\"%s\",response=\"%s\"\r\n"
                "User-Agent:VLC media player(LIVE555 Streaming Media library version 2012.12.09)"
                "\r\n"
                "\r\n",argv[1],noncestr,argv[1],response);
    printf("send to server %s\n", buf);
    if((send_fd = send(sock_fd, buf, strlen(buf), 0)) < 0)
    {
        printf("send() failed\n");
        exit(1);
    }
    printf("send() succeed\n");
    printf("send_fd=%d\n",send_fd);
    memset(rec_buf,0,BUF_SIZE);
    memset(rec_buf, 0, BUF_SIZE);
    if ((recv_fd = recv(sock_fd, rec_buf, sizeof(buf), 0)) < 0)   /*sizeof(rec_buf) */
    {
        printf("recv() failed\n");
        exit(1);
    }
    printf("recv() succeed\n");
    printf("recv_fd=%d\n",recv_fd);
    printf("setup recv from server is %s\n",rec_buf);
#endif

    int m=0;
    char session[4096];
    memset(session,0,4096);

    if(rec_buf == NULL)
    {
        printf("session failed \n");
        exit(1);
    }
    char *q;
    q=strstr(rec_buf,"Session:");  //得到Session在消息中的首地址
    printf("q=%s\n",q);
    while(*(q+9+m) != ('\0' && '\n' && '\r'))
    {
        session[m] = *(q+9+m);
        m++;
    }
    session[m] = '\0';
    printf("Session succeed and it is %s\n",session);



    //getchar();


    memset(buf, 0, BUF_SIZE);
    sprintf(buf,"PLAY %s RTSP/1.0\r\n"
                "CSeq:5\r\n"
                "Session: %s\r\n"
                // "Authorization:Digest username=\"admin\",realm=\"www.dvr163.com\",nonce=\"%s\",uri=\"%s\",response=\"%s\"\r\n"
                "Range:npt=0.000\r\n"
                "User-Agent:VLC media player(LIVE555 Streaming Media library version 2012.12.09)"
                "\r\n"
                "\r\n",argv[1],session,noncestr,argv[1],response);
    printf("send to server %s\n", buf);
    if((send_fd = send(sock_fd, buf, strlen(buf), 0)) < 0)
    {
        printf("send() failed\n");
        exit(1);
    }
    printf("send() succeed\n");
    printf("send_fd=%d\n",send_fd);
    memset(rec_buf, 0, BUF_SIZE);
    if ((recv_fd = recv(sock_fd, rec_buf, sizeof(buf), 0)) < 0)   /*sizeof(rec_buf) */
    {
        printf("recv() failed\n");
        exit(1);
    }
    printf("recv() succeed\n");
    printf("recv_fd=%d\n",recv_fd);
    printf("play recv from server is %s\n",rec_buf);


    recv_data_from_server(sock_udp_fd1,sock_udp_fd2);

    close(sock_fd);
    return 0;

}

int creat_udp(int i, int port)
{
    struct sockaddr_in udp_addr;
    int sock_udp_fd;
    if((sock_udp_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        printf("UDP socket() failed\n");
        exit(1);
    }
    printf("UDP socket() succeed\n");
    printf("sock_udp_fd=%d\n", sock_udp_fd);

    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    udp_addr.sin_port = htons(port);
    int bind_udp_fd;
    if((bind_udp_fd = bind(sock_udp_fd,(struct sockaddr*)&udp_addr,sizeof(udp_addr))) < 0)
    {
        printf("UDP bind() failed\n");
        exit(1);
    }
    printf("UDP socket() succeed\n");
    printf("bind_udp_fd=%d\n", bind_udp_fd);
    printf("create UDP port%d succeed\n", i);
    printf("sock_udp_fd%d=%d\n", i, sock_udp_fd);
    return sock_udp_fd;
}

int  recv_data_from_server(int sock_udp_fd1,int sock_udp_fd2)
{

    char recv_buf[4096];
    int maxfd = 0;
    int filelen = 0;
    int fd = 0;
    //int udp_addr_len =0;
//	socklen_t udp_addr_len =0;
    struct timeval tm;
    //tm.tv_sec=5;
    //tm.tv_usec=0;
    int select_ret=0;
    fd_set read_fd;

    if (sock_udp_fd1 >= sock_udp_fd2)
    {
        maxfd = sock_udp_fd1;
    }
    else
        maxfd = sock_udp_fd2;
    if((fd = open(filename_buf, O_CREAT|O_RDWR,0666)) < 0)
    {
        printf("open %s failed!\n",filename_buf);
        return -1;
    }
#if 1
    while(1)
    {
        tm.tv_sec=5;
        tm.tv_usec=0;
        FD_ZERO(&read_fd);
        FD_SET(sock_udp_fd1,&read_fd);
        FD_SET(sock_udp_fd2,&read_fd);

        select_ret = select(maxfd+1,&read_fd,NULL,NULL,&tm);
        if(select_ret < 0)
        {
            perror("not readly file\n");
            continue;
        }
        else if(select_ret == 0)
        {
            printf("time out\n");
            continue;
        }
        else
        {
            if(FD_ISSET(sock_udp_fd1,&read_fd))
            {
                memset(recv_buf,0,BUF_SIZE);
                filelen = recv(sock_udp_fd1,recv_buf,sizeof(recv_buf),0);
                //printf("sizeof recv_buf is %d\n",sizeof(recv_buf));
                printf("1recv data size from server:%d\n",filelen);
                if(filelen < 12)
                {
                    perror("recv error\n");
                    continue;
                }
                filelen = filelen - 12;
                write(fd,(recv_buf+12),filelen);
            }

            if( FD_ISSET(sock_udp_fd2,&read_fd))
            {
                memset(recv_buf,0,BUF_SIZE);
                filelen = recv(sock_udp_fd2,recv_buf,sizeof(recv_buf),0);
                //printf("sizeof recv_buf is %d\n",sizeof(recv_buf));
                printf("2recv data size from server:%d\n",filelen);
                if(filelen < 12)
                {
                    perror("recv error\n");
                    continue;
                }
                filelen = filelen - 12;
                write(fd,(recv_buf+12),filelen);
            }

        }

    }
#endif
#if 0
    recvfrom(socket_fd, buff, MAXBUF, 0,(struct sockaddr*)&servaddr, &addr_len);




#endif
    close(fd);
    printf("\ncomplete ok!\n");
    return 0;
}
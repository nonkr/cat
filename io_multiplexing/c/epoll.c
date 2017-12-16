/*
 * Copyright (c) 2017, Billie Soong <nonkr@hotmail.com>
 * All rights reserved.
 *
 * This file is under GPL, see LICENSE for details.
 *
 * Author: Billie Soong <nonkr@hotmail.com>
 * Datetime: 2017/12/16 23:29
 *
 */

#include <sys/epoll.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int ret;
    int fd;

    // 创建有名管道
    if (mkfifo("/tmp/test_fifo", 0666) != 0)
    {
        perror("mkfifo：");
    }

    // 读写方式打开管道
    fd = open("/tmp/test_fifo", O_RDWR);
    if (fd < 0)
    {
        perror("open fifo");
        return -1;
    }

    struct epoll_event event;    // 告诉内核要监听什么事件
    struct epoll_event wait_event;

    int epfd = epoll_create(10); // 创建一个epoll的句柄，参数要大于0，自linux2.6.8之后，size参数是被忽略的
    if (epfd == -1)
    {
        perror("epoll_create");
        return -1;
    }

    event.data.fd = 0;       // 标准输入
    event.events = EPOLLIN;  // 表示对应的文件描述符可以读

    // 事件注册函数，将标准输入描述符 STDIN_FILENO 加入监听事件
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    if (ret == -1)
    {
        perror("epoll_ctl");
        return -1;
    }

    event.data.fd = fd;     // 有名管道
    event.events = EPOLLIN; // 表示对应的文件描述符可以读

    // 事件注册函数，将有名管道描述符 fd 加入监听事件
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    if (ret == -1)
    {
        perror("epoll_ctl");
        return -1;
    }

    while (1)
    {
        // 监视并等待多个文件（标准输入，有名管道）描述符的属性变化（是否可读）
        // 没有属性变化，这个函数会阻塞，直到有变化才往下执行
//        ret = epoll_wait(epfd, &wait_event, 2, -1);
        ret = epoll_wait(epfd, &wait_event, 2, 1000);

        if (ret == -1)
        {   // 出错
            close(epfd);
            perror("epoll");
        }
        else if (ret > 0)
        {   // 准备就绪的文件描述符
            char buf[100] = {0};
            if ((wait_event.data.fd == STDIN_FILENO) && (EPOLLIN == wait_event.events & EPOLLIN))
            {   // 标准输入
                read(0, buf, sizeof(buf));
                printf("stdin buf = %s\n", buf);
            }
            else if ((wait_event.data.fd == fd) && (EPOLLIN == wait_event.events & EPOLLIN))
            {   // 有名管道
                read(fd, buf, sizeof(buf));
                printf("fifo buf = %s\n", buf);
            }
        }
        else if (ret == 0)
        {   // 超时
            printf("time out\n");
        }
    }

    close(epfd);

    return 0;
}

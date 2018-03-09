#ifndef CALLBACK_H
#define CALLBACK_H

#include <dns_sd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT_NUM 9877

extern void HandleEvents(DNSServiceRef);

#endif

#include "callback.h"

#define LONG_TIME 100000000

static volatile int stopNow = 0;
static volatile int timeOut = LONG_TIME;

void
HandleEvents(DNSServiceRef serviceRef)
{
    int dns_sd_fd = DNSServiceRefSockFD(serviceRef);
    int nfds = dns_sd_fd + 1;
    fd_set readfds;
    struct timeval tv;
    int result;
    int client_fds[2];
    int clients;
    int listening_fd;
    struct sockaddr_in serveraddr;
    DNSServiceErrorType err;

    listening_fd = socket (AF_INET, SOCK_STREAM, 0);
    if (listening_fd < 0)
    {
        perror ("Socket creation");
        exit (1);
    }

    memset (&serveraddr, 0, sizeof(struct sockaddr_in));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons (PORT_NUM);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);


    result = bind (listening_fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (result < 0)
    {
        perror ("Socket creation");
        exit (1);
    }

    result = listen (listening_fd, 50);
    if (result < 0)
    {
        perror ("Socket creation");
        exit (1);
    }

    memset (client_fds, -1, 2 * sizeof(int));
    clients = 0;

    while (!stopNow)
    {
        FD_ZERO (&readfds);
        FD_SET (dns_sd_fd, &readfds);
        if (clients < 2)
            FD_SET (listening_fd, &readfds);

        tv.tv_sec = timeOut;
        tv.tv_usec = 0;

        err = 0;

        result = select (nfds, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);
        if (result <= 0)
        {
            printf ("select( ) returned %d errno %d %s\n",
                    result, errno, strerror (errno));
            if (errno != EINTR)
                stopNow = 1;
            else
                continue;
        }

        if (FD_ISSET (dns_sd_fd, &readfds))
            err = DNSServiceProcessResult (serviceRef);
        if (err) stopNow = 1;

        if (FD_ISSET (listening_fd, &readfds))
        {
            /* TODO
             * accept()
             * set array value based on if 1st or 2nd
             * if second, run game, close connections, clear array
             * wait till second connects to handle 1st name?
             * keep running select loop while waiting? or during game?
             */
        }

    }
    /* TODO close sockets
     */
}

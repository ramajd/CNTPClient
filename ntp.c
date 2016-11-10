/*
 * ntp.c
 *
 *  Created on: Nov 9, 2016
 *      Author: reza
 */

#include "ntp.h"

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


long ntp_get_from(const char* host, unsigned int port, unsigned int timeout)
{
	unsigned char ntpReq[48] = {010,0,0,0,0,0,0,0,0};
	unsigned long ntpResp[48];

	struct sockaddr_in srvAddr;
	memset(&srvAddr, 0, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_addr.s_addr = inet_addr(host);
	srvAddr.sin_port = htons(port);

	struct timeval read_timeout;
	read_timeout.tv_sec = timeout;
	read_timeout.tv_usec = 0;

	int sfd = socket(PF_INET, SOCK_DGRAM, 0);
	setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
	if (sfd < 0)
	{
		perror("socket: ");
		return -1;
	}

	int res = sendto(sfd, ntpReq, 48, 0, (struct sockaddr*)(&srvAddr), sizeof(srvAddr));
	if (res < 0)
	{
		perror("sendto: ");
		return -1;
	}
	struct sockaddr addr;
	socklen_t addr_len;
	res = recvfrom(sfd, ntpResp, 48, 0, &addr, &addr_len);
	if (res < 0)
	{
		perror("recvfrom: ");
		return -1;
	}

	long time_val = ntohl((time_t)ntpResp[4]);

	time_val -= 2208988800U;	/* difference between NTP and UNIX time */
	return time_val;
}



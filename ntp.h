/*
 * ntp.h
 *
 *  Created on: Nov 9, 2016
 *      Author: reza
 */

#ifndef NTP_H_
#define NTP_H_

#include <time.h>
#include <sys/time.h>


//#define NTP_DEFAULT_SERVER 	"200.20.186.76"
#define NTP_DEFAULT_SERVER 	"194.225.50.25"
#define NTP_DEFAULT_PORT	123
#define NTP_DEFAULT_TIMEOUT	10

#define ntp_get() (ntp_get_from(NTP_DEFAULT_SERVER, NTP_DEFAULT_PORT, NTP_DEFAULT_TIMEOUT))

long ntp_get_from(const char* host, unsigned int port, unsigned int timeout);

#endif /* NTP_H_ */

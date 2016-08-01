/*
 * client.h
 *
 *  Created on: Aug 1, 2016
 *      Author: devteam
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>
#include "calculation.pb-c.h"
#include "result.pb-c.h"
#include <sys/ipc.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

void serialize(float, float, const char*, int);
float deserialize(Result*, ssize_t, uint8_t*);
void connected();
void handler_quit(int);
void handler_interrupt(int);
void init_shm();
void read_from_shm();
void notify_conn(int);
void notify_disconn(int);
void notify_server_disconn(int);
void print_log();

static int sock, pid, shm_fd;
FILE *f;
ssize_t calc_len;
uint8_t buf[1024];
void* addr;
Calculation msg = CALCULATION__INIT;
const shm_size = 1024;
char *shm_p, shm[] = {"/slog"};

#endif /* CLIENT_H_ */

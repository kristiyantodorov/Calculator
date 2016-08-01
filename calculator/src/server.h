/*
 * server.h
 *
 *  Created on: Aug 1, 2016
 *      Author: devteam
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <signal.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include "calculation.pb-c.h"
#include "result.pb-c.h"
#include <sys/ipc.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>

void server();
void init_shm();
void write_to_shm(const char*);
void* thread_func(void*);
void handler(int);
void add_to_online(int);
void remove_from_online(int);
void notify(int, int);
void resize();
void deserialize_input(Calculation*, ssize_t, uint8_t*, float*, float*, char*, int*);
float calculate(float, float, char);
void serialize_result(uint8_t*, Result*, float, ssize_t*);
void initialize_online();

struct online {
	int pid;
	int present;
};

static int sock, active_connections, max_connections = 100, shm_fd;
struct online* users;
const shm_size = 1024;
char *shm_p, shm[] = {"/slog"};

#endif /* SERVER_H_ */

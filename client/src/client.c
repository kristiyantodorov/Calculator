#include "client.h"

int main() {
	signal(SIGINT, handler_interrupt);
	signal(SIGQUIT, handler_quit);
	signal(30, notify_conn);
	signal(10, notify_disconn);
	signal(16, notify_server_disconn);
	init_shm();
	connected();
	return EXIT_SUCCESS;
}

void read_from_shm() {
	printf("%s\n", shm_p);
}

void init_shm() {
	shm_fd = shm_open(shm, O_CREAT | O_RDONLY, 777);
	ftruncate(shm_fd, shm_size);
	shm_p = mmap(NULL, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
}

// Signal handlers for events on the server
void notify_conn(int sig) {
	printf("client has connected\n");
}

void notify_disconn(int sig) {
	printf("client has disconnected\n");
}

void notify_server_disconn(int sig) {
	printf("The server has disconnected... Exiting\n");
	close(sock);
	shm_unlink(shm);
	sleep(1);
	exit(1);
}

// Makes input data into protocol buffer
void serialize(float l, float r, const char* op, int pid) {
	msg.left = l;
	msg.right = r;
	msg.operation = malloc(2);
	strcpy(msg.operation, op);
	msg.pid = pid;
	calc_len = calculation__get_packed_size(&msg);
	calculation__pack(&msg, buf);
}

// Uses the recieved buffer to get result information
float deserialize(Result* res, ssize_t res_len, uint8_t* res_buf) {
	res = result__unpack(NULL, res_len, res_buf);
	if(res == NULL) {
		fprintf(stderr, "error unpacking incoming message\n");
		exit(1);
	}
	float l = res->result;
	// Free the unpacked message
	result__free_unpacked(res, NULL);
	return l;
}

void connected() {
	Result res = RESULT__INIT;
	struct sockaddr_in server;
	char operation[2];
	float left = 0, right;
	uint8_t r_buf[1024];
	ssize_t r_len;
	pid = getpid();
	printf("You can begin calculation or review the server log by typing 'l' instead of operator\n");

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1) {
		printf("Could not create socket\n");
	}
	puts("Socket created");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("10.185.21.117");
	server.sin_port = htons(8888);

	while( (connect(sock, (struct sockaddr*) &server, sizeof(server))) < 0 ) {
		puts("Error connecting to server... Reconnecting");
		sleep(3);
	}
	puts("Connected\n");

	printf("= %f\n", left);
	scanf("%s", operation);
	if( strcmp("l", operation) == 0 ) {
		printf("Here is the server log:\n");
		read_from_shm();
		printf("= %f\n", left);
		scanf("%s", operation);
	}

	scanf("%f", &right);

	// Zero division check
	if(operation[0] == '/' && right == 0) {
		do {
			puts("Cannot divide by 0... Enter different number");
			scanf("%f", &right);
		}
		while (right == 0 && operation[0] == '/');
	}
	serialize(left, right, operation, pid);

	while( (send(sock, buf, calc_len, 0)) ) {
		r_len = recv(sock, r_buf, 1024, 0);
		left = deserialize(&res, r_len, r_buf);
		printf("= %f\n", left);
		scanf("%s", operation);
		if( strcmp("l", operation) == 0 ) {
			read_from_shm();
			printf("= %f\n", left);
			scanf("%s", operation);
		}
		scanf("%f", &right);

		// Zero division check
		if(operation[0] == '/' && right == 0) {
			do {
				puts("Cannot divide by 0... Enter different number");
				scanf("%f", &right);
			}
			while (right == 0);
		}

		serialize(left, right, operation, pid);
	}

	close(sock);
	sleep(2);
}

// Handlers for user interruptions
void handler_interrupt(int sig) {
	printf("\nReceived Ctrl+C signal to interrupt. Goodbye!\n");
	close(sock);
	shm_unlink(shm);
	sleep(1);
	exit(1);
}

void handler_quit(int sig) {
	printf("\nReceived Ctrl+\\ signal to interrupt. Goodbye!\n");
	close(sock);
	shm_unlink(shm);
	sleep(1);
	exit(1);
}

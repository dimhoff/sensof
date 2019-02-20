#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <endian.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define WITH_ENCRYPTION 1

#ifdef WITH_ENCRYPTION
# include <openssl/aes.h>
#endif

#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))

#pragma pack(1)
struct sensof_frame {
	// Encrypted Header
	uint32_t  id;
	uint32_t  cnt;

	// Data
	uint16_t  temp;
	uint16_t  hum;
	uint32_t  _reserved2;
};
#pragma pack()

#define SENSOF_PKT_LEN (sizeof(struct sensof_frame))

static struct sensof_ht_node {
	uint32_t id;
	char *name;
	uint32_t last_cnt;
	time_t last_seen;
	double temp;
	double hum;
} nodes[] = {
	// TODO: load nodes from config file
#error "fill this struct with your nodes"
	{ 0x11223344, "Example_node", 0, 0, 0, 0 },
};

int verbose = 0;
bool no_encryption = false;
AES_KEY kobj;
volatile sig_atomic_t terminate = 0;

void terminate_cb(int signum)
{
	terminate = 1;
}

#define OUTPUT_FILE "/dev/shm/sensof.json"
static void generate_json()
{
	FILE *ofp;

	if ((ofp = fopen(OUTPUT_FILE, "w")) == NULL) {
		perror("Failed to open output file");
		return;
	}

	fprintf(ofp, "{ \"nodes\": [\n");
	int i;
	for (i = 0; i < ARRAY_SIZE(nodes); i++) {
		if (i != 0)
			fprintf(ofp, "  ,\n");
		fprintf(ofp, "  {\n");
		fprintf(ofp, "   \"name\": \"%s\",\n", nodes[i].name);
		fprintf(ofp, "   \"last_seen\": %u,\n", nodes[i].last_seen);
		fprintf(ofp, "   \"temp\": %.2f,\n", nodes[i].temp);
		fprintf(ofp, "   \"hum\": %.2f\n", nodes[i].hum);
		fprintf(ofp, "  }\n");
	}
	fprintf(ofp, "]}\n");

	fclose(ofp);
}

static void sensof_process_packet(uint8_t *pkt)
{
	struct sensof_frame *fbuf = (struct sensof_frame *) pkt;

#ifdef WITH_ENCRYPTION
	uint8_t outbuf[AES_BLOCK_SIZE];
	if (! no_encryption) {
		AES_decrypt(pkt, outbuf, &kobj);
		fbuf = (struct sensof_frame *) outbuf;

		if (verbose) {
			fprintf(stderr, "Raw decrypted data:\n");
			for (int i = 0; i < SENSOF_PKT_LEN; i++) {
				printf("%.2x ", outbuf[i]);
			}
			putchar('\n');
		}
	}
#endif // WITH_ENCRYPTION

	uint32_t id = be32toh(fbuf->id);
	uint32_t cnt = be32toh(fbuf->cnt);
	double temp = be16toh(fbuf->temp);
	double hum = be16toh(fbuf->hum);

	temp = -46.85 + 175.72 * temp / 65536;
	hum = -6.0 + 125.0 * hum / 65536;

	bool found = false;
	int i;
	for (i = 0; i < ARRAY_SIZE(nodes); i++) {
		if (id == nodes[i].id) {
			found = true;
			break;
		}
	}

	if (found) {
		if (cnt < nodes[i].last_cnt) {
			printf("Replay packet!: %08x#%08x Temperature = %.2f, Humidity = %.2f\n",
				id, cnt, temp, hum);
		} else if (cnt > nodes[i].last_cnt) {
			nodes[i].temp = temp;
			nodes[i].hum = hum;
			nodes[i].last_seen = time(NULL);
			nodes[i].last_cnt = cnt;

			generate_json();
		} // ignore duplicate packets
	} else {
		printf("Unknown node: %08x#%08x Temperature = %.2f, Humidity = %.2f\n",
			id, cnt, temp, hum);
	}
}

int main(int argc, const char *argv[])
{
	uint8_t pkt[SENSOF_PKT_LEN];
	int sock;

	size_t len;
	struct sockaddr_un remote;
	char str[100];
	if (argc != 2) {
		fprintf(stderr, "usage: sensof_to_json <si443x_drv socket>\n");
		return -1;
	}

	if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, argv[1]);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(sock, (struct sockaddr *)&remote, len) == -1) {
		perror("connect");
		exit(1);
	}


	// Initialise encryption parameters
#ifdef WITH_ENCRYPTION
	if (! no_encryption) {
		//TODO: get key as command line option
		uint8_t key[128/8] = {
#include "key.cinc"
		};
		if (AES_set_decrypt_key(key, 128, &kobj) != 0) {
			fprintf(stderr, "Failed to set decryption key\n");
			exit(EXIT_FAILURE);
		}
	}
#endif // WITH_ENCRYPTION

	generate_json();

	while (!terminate) {
		size_t tot_read;

		// Read Payload
		tot_read = 0;
		while (tot_read < SENSOF_PKT_LEN) {
			ssize_t r = read(sock, &pkt[tot_read], SENSOF_PKT_LEN - tot_read);
			if (r == -1) {
				perror("read()");
				exit(EXIT_FAILURE);
			}
			tot_read += r;
		}

		if (verbose) {
			printf("Received packet: \n");
			for (int i = 0; i < SENSOF_PKT_LEN; i++) {
				printf("%.2x ", pkt[i]);
			}
			putchar('\n');
		}
		sensof_process_packet(pkt);

		if (verbose)
			putchar('\n');
	}

	close(sock);

	return 0;
}

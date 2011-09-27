

typedef struct {
	int sockfd;
	u_char hwaddr[6];
	struct addr_in address;
	struct addr_in subnet;
	struct addr_in netmask;
} DEVICE;



#define FLAG_FREE 0
#define FALG_OK   1
#define FLAG_NG  -1

// TODO what this structure
typedef struct _data_buf_ {
	_data_buf_ *next;
	_data_buf_ *before;
	time_t time;
	int size;
	unsigned char *data;
} DATA_BUF;


typedef struct {
	DATA_BUF top;
	DATA_BUF bottom;
	unsigned long dno;
	unsigned long inBucketSize;
	pthread_mutex_t mutex; 
} SEND_DATA;

typedef struc {
	int flag;
	int deviceNo;
	inaddr_t addr;
	unsigned char hwdaddr[6];
	time_t last_time;
	SEND_DATA sd;
}IP2MAC;



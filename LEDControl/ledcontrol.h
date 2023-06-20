

typedef struct LCH {
	unsigned long magic;
	unsigned char operation;
	unsigned char subOperation;
	unsigned char cmd;
	unsigned char led;

} LCH_t;

#define MAGIC	0x12345678

#define REQ	1
#define REP	2


#define GET	1
#define SET	2

#define LED_ON		1
#define LED_OFF		2
#define LED_BLINK	3
#define LED_NOP		4

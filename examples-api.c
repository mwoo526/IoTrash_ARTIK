
#include <string.h>
#include <sys/boardctl.h>
#include <shell/tash.h>

#include <stddef.h>

#include <artik_module.h>
#include <artik_cloud.h>
#include <artik_http.h>
#include <artik_lwm2m.h>
#include <artik_websocket.h>

#include "command.h"
#include <stdio.h>
#include <apps/shell/tash.h>
#include <errno.h>
#include <fcntl.h>
#include <tinyara/analog/adc.h>
#include <tinyara/analog/ioctl.h>
#include <tinyara/gpio.h>
#define GREEN	1
#define YELLOW	2
#define RED		3

extern int sdk_main(int argc, char *argv[]);
extern int cloud_main(int argc, char *argv[]);
extern int gpio_main(int argc, char *argv[]);
extern int pwm_main(int argc, char *argv[]);
extern int adc_main(int argc, char *argv[]);
extern int http_main(int argc, char *argv[]);
extern int wifi_main(int argc, char *argv[]);
extern int websocket_main(int argc, char *argv[]);
extern int see_main(int argc, char *argv[]);

static void gpio_write(int port, int value)
{
	char str[4];
	static char devpath[16];
	snprintf(devpath, 16, "/dev/gpio%d", port);
	int fd = open(devpath, O_RDWR);
	ioctl(fd, GPIOIOC_SET_DIRECTION, GPIO_DIRECTION_OUT);
	write(fd, str, snprintf(str, 4, "%d", value != 0) + 1);
	close(fd);
}

int http_get(int argc, char **argv);
int websocket_connect2(int argc, char *argv[]);
int message_command(int argc, char *argv[],char* artikID ,double trashAmount,int ledColor);


static tash_cmdlist_t atk_cmds[] = {
		{"sdk", sdk_main, TASH_EXECMD_SYNC},
		{"gpio", gpio_main, TASH_EXECMD_SYNC},
		{"pwm", pwm_main, TASH_EXECMD_SYNC},
		{"adc", adc_main, TASH_EXECMD_SYNC},
		{"cloud", cloud_main, TASH_EXECMD_SYNC},
		{"http", http_main, TASH_EXECMD_SYNC},
		{"wifi", wifi_main, TASH_EXECMD_SYNC},
		{"websocket", websocket_main, TASH_EXECMD_SYNC},
		{"see", see_main, TASH_EXECMD_SYNC},
		{NULL, NULL, 0}
};

 void getData(int *color, double *trashAmount)
{
	int i;
	struct adc_msg_s sample;
	int led_Color;
	char led_ColorS[10] = {0};
	double trash_Amount =0;

	char values[512];
	char data[3];


	int fd, res;
	size_t readsize;
	ssize_t nbytes;
	fd = open("/dev/adc0", O_RDONLY);
	printf("fd: %d\n", fd);
	printf("ADC Data:\n");
	res = ioctl(fd, ANIOC_TRIGGER	, 0);
	readsize = sizeof(struct adc_msg_s);
	nbytes = read(fd, &sample, readsize);
	int nsamples = sizeof(struct adc_msg_s);
	if (sample.am_channel == 0) {
		trash_Amount=sample.am_data;
		printf("value: %d\n",sample.am_data);
		if(sample.am_data < 1800) {
			led_Color = GREEN;
			gpio_write(51, 0);
			gpio_write(52, 0);
			gpio_write(53, 1);
			up_mdelay(200);
		}
		else if(1800 <= sample.am_data && sample.am_data < 2650) {
			led_Color = YELLOW;
			gpio_write(51, 0);
			gpio_write(52, 1);
			gpio_write(53, 0);
			up_mdelay(200);
		}
		else{
			led_Color = RED;
			gpio_write(51, 1);
			gpio_write(52, 0);
			gpio_write(53, 0);
			up_mdelay(200);
		}
		//sprintf(led_ColorS, "%d", led_Color);
	}
	//sleep(1);

	//int *color, double *trashAmount, char artikID[]
	*color = led_Color;
	*trashAmount = trash_Amount;


	close(fd);

	//data[0]=artik_ID;
	//data[1]=""+trash_Amount;
	//data[2]=led_Color;
	//return led_Color;
}

int main(int argc, char *argv[])
{
	char uri[100];
	int ledColor=0;
	double trashAmount=0;;
	char* artik_ID="1394038";
	getData(&ledColor, &trashAmount);

	sprintf(uri, "http://13.124.194.75:8080/project/postTrash?artik_ID=%s&trash_Amount=%lf&led_Color=%d", artik_ID, trashAmount, ledColor);
	char *cmd[] = {"get_command", "http", "get", uri};
	char *cmd2[] = {"connect_command", "websocket", "connect", "wss://echo.websocket.org/"};
	char *cmd3[] = {"message_command", "cloud", "message"};
	printf("### %s %lf %d\n\n", artik_ID, trashAmount, ledColor);


#ifdef CONFIG_TASH
	/*     add tash command*/
	tash_cmdlist_install(atk_cmds);
	websocket_connect2(4, cmd2);
	while(http_get(4, cmd)==1) {
		getData(&ledColor, &trashAmount);
		sprintf(uri, "http://13.124.194.75:8080/project/postTrash?artik_ID=%s&trash_Amount=%lf&led_Color=%d", artik_ID, trashAmount, ledColor);
		printf("### %s %lf %d\n\n", artik_ID, trashAmount, ledColor);
		message_command(3,cmd3,artik_ID,trashAmount,ledColor);
		sleep(1);
	}
#endif
	puts("hello");
	return 0;


}


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	char buf[100] = "I love tomato.";
	printf("This is user-app test program.\n");

	if(argc < 2)
	{
		printf("Please enter the dev you want to use.\n");
		return 1;
	}

	char *dev = argv[1];
	printf("Ready to open device:%s\n",dev);
	int fd = open(dev,O_RDWR);

	if(fd < 0)
	{
		printf("Failed open %s devices.\n",dev);
		return -1;
	}

	printf("The content of buf:%s\n",buf);
	write(fd,buf,5);
	return 0;
}

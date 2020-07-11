#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#include<sys/time.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <asm/types.h>
#include <linux/videodev2.h>
#include <malloc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <termios.h>
#include <iostream>
#include <fstream>
#include <signal.h>
int main()
{
	int isReady;
    	int width=1280 ;
    	int height=720;

    	int fd0 = open("/dev/video1", O_RDWR);
  
    	if (fd0<0 )
    	{
         	printf("Can't open it!\n"); 
         	isReady=0;
    	}
    	else
    	{ 
          	printf("open video Successfull!\n"); 
          	isReady=1;
     	}

    	if(isReady)
   	{
        	// get the capability of the video
        	struct v4l2_capability cap0;
        	if(ioctl(fd0,VIDIOC_QUERYCAP,& cap0)==-1)
             		printf("Can't get both caps!\n");
        	if(cap0.capabilities&V4L2_CAP_VIDEO_CAPTURE)
             		printf("They are video caprure devices!\n");
        	if(cap0.capabilities&V4L2_CAP_STREAMING)
             		printf("They support streaming i/0\n");
        	if(cap0.capabilities&V4L2_CAP_READWRITE)
             		printf("They support read and write i/o\n");
        	// set up the image format
        	struct v4l2_format fmt0;
        	fmt0.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
        	fmt0.fmt.pix.width=width;
        	fmt0.fmt.pix.height=height;
        	fmt0.fmt.pix.pixelformat=V4L2_PIX_FMT_JPEG;

        	if(ioctl(fd0,VIDIOC_S_FMT,& fmt0)==-1)
             		printf ( "format failed\n");
        	else  
			printf(" This format is allowed!\n");
		sleep(1);

		int cam_count=1;
		char pic_str[20];

		while(1)
		{
       			void *buff0 = malloc(10240 * 10240);  
       			sprintf(pic_str,"./pic%d.jpg",cam_count);
       			
			int size0 = read(fd0, buff0, 10240 * 10240);

       			int filefd0 = open(pic_str, O_RDWR | O_CREAT,420);
                        write(filefd0, buff0, size0);

			close(filefd0);
 
			free(buff0);

			cam_count++;
			//usleep(50000);
			sleep(1);

		}
   	}
}

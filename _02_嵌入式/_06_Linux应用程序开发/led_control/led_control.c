#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LED_NUM 2//development board only 2 leds


int main(int argc,char *argv[])
{  
	char *path_leds = "/dev/leds";
    int led_value = atoi(argv[1]);
    int led_fd = 0;
    int i = 0;
    unsigned char temp = 0;
    
    printf("\n");
     
    if(argc >= 3) 
    {
    	printf("failure:too many arguments \n");
    	printf("arguments:led bus value\n");
    	return -1;    
    } 
    
    else 
    {
    	if (led_value < 0)
    	{
    		printf("failure:arguments can't be negative \n");
    		return -1;    
    	}
    	else
    	{
    		led_fd = open(path_leds, O_RDWR|O_NOCTTY|O_NDELAY); //open file
    	    if(led_fd >= 0)
			{
				printf("open %s success \n",path_leds);      
			}
			else 
			{
				printf("open %s failure \n",path_leds); 
				return -1;        
			}
    
    		for(i = 0;i < LED_NUM;i ++)
    		{
    			if(led_value & (0x01<<i)) temp = 1;//get led's value
    			else temp = 0;
    			
    			ioctl(led_fd,temp,i);
    			printf("led%d is %d \n",i,temp);
    			
    		}
    		close(led_fd);
    		 
    	}
    }
   
    
    return 0;        
}













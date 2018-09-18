#include<common.h>
#include<command.h>

#define GPIO_BASE (0x3F000000 + 0x200000)

volatile unsigned *GPIO_FSEL1 = (volatile unsigned *)(GPIO_BASE + 0x04);
volatile unsigned *GPIO_SET0  = (volatile unsigned *)(GPIO_BASE + 0x1C);
volatile unsigned *GPIO_CLR0  = (volatile unsigned *)(GPIO_BASE + 0x28);

static void spin_sleep_us(unsigned int us) 
{
	unsigned int i;
	for (i = 0; i < us * 6; i++) 
	{
		asm volatile("nop");
	}
}

static void spin_sleep_ms(unsigned int ms) 
{
	spin_sleep_us(ms * 1000);
}

int do_led_on_off(cmd_tbl_t *cmdtp, int flag, int argc, char * argv[])
{
	if(!strcmp(argv[1],"ON"))
	{
		printf("LED ON\n");
		// STEP 1: Set GPIO Pin 16 as output.
		*GPIO_FSEL1 = *GPIO_FSEL1 | (0b001 << 18);
		// STEP 2: Continuously set and clear GPIO 16.
		//while(1) 
		{
			*GPIO_SET0 = 0b001 << 16;
			//spin_sleep_ms(1000);
			//*GPIO_CLR0 = 0b001 << 16;
			//spin_sleep_ms(1000);
		}
	}
	else
	{
		printf("LED OFF\n");
		*GPIO_CLR0 = 0b001 << 16;
	}
	return 0;
}
U_BOOT_CMD(led,2,1,do_led_on_off,"LED On Off","arg1:Start address");

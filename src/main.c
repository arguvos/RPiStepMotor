#include <bcm2835.h>

#define IN_A	RPI_GPIO_P1_24
#define IN_B	RPI_GPIO_P1_26
#define IN_C	RPI_GPIO_P1_16
#define IN_D	RPI_GPIO_P1_18
#define DELAY	50

int init()
{
	if (!bcm2835_init())
	{
		printf("Error in init bcm2835");
		return 1;
	}
	bcm2835_gpio_fsel(IN_A, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(IN_B, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(IN_C, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(IN_D, BCM2835_GPIO_FSEL_OUTP);
	return 0;
}

void set_pins(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	bcm2835_gpio_write(IN_A, a);
	bcm2835_gpio_write(IN_B, b);
	bcm2835_gpio_write(IN_C, c);
	bcm2835_gpio_write(IN_D, d);
}

void step_forward()
{
	set_pins(HIGH, LOW, LOW, LOW);
	bcm2835_delay(DELAY);
	
	set_pins(LOW, LOW, HIGH, LOW);
	bcm2835_delay(DELAY);
	
	set_pins(LOW, HIGH, LOW, LOW);
	bcm2835_delay(DELAY);
	
	set_pins(LOW, LOW, LOW, HIGH);
	bcm2835_delay(DELAY);
}

void step_back()
{	
	set_pins(LOW, LOW, LOW, HIGH);
	bcm2835_delay(DELAY);
	
	set_pins(LOW, HIGH, LOW, LOW);
	bcm2835_delay(DELAY);
	
	set_pins(LOW, LOW, HIGH, LOW);
	bcm2835_delay(DELAY);
	
	set_pins(HIGH, LOW, LOW, LOW);
	bcm2835_delay(DELAY);
}

void turn_off()
{
	bcm2835_gpio_write(IN_A, LOW);
	bcm2835_gpio_write(IN_B, LOW);
	bcm2835_gpio_write(IN_C, LOW);
	bcm2835_gpio_write(IN_D, LOW);
}

int main(int argc, char *argv[])
{	
	int i=0;
	int step_count;
	char * is_forward;
	
	if (init() != 0)
		return 1;
	
	sscanf(argv[1], "%d", &step_count);
	is_forward = argv[2];
	
	for(i=0; i<step_count; i++)
	{
		if (strcmp(is_forward, "TRUE")==0)
			step_forward();
		else if (strcmp(is_forward, "FALSE")==0)
			step_back();
		else
		{
			printf("Error in the second parameter. This parameter specifies the direction of movement.");
			return 1;
		}
	}
	
	turn_off();
	return 0;
}

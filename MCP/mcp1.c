#include <mcp3004.h>
#include <stdio.h>

#define BASE		100
#define SPI_CHAN	0

int main(void)
{

	mcp3004Setup(BASE, SPI_CHAN);
	while(1)
	{
		delay(200);
		int x = analogRead(BASE);
		printf("%d\n", x);
	}
}

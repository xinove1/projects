#include "stdio.h"
#include "unistd.h"
//#include "fnistd.h"


int main(void)
{
	write(1, "Please insert special character! \n", 34);
	char buf[100];
	int i = 0;
	while (1) {
		int red = read(0, &buf[i], 1);
		if (red) {
			if (buf[i] == '\n' && buf[i-1] == 'Q') {
				printf("Welcome to 0de5!\n");
				return (0);
			}
			i++;
		}
	}
	return (0);
}

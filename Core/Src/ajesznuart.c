/*
 * ajesznuart.c
 *
 *  Created on: May 24, 2024
 *      Author: Ajeszny
 */
#include <ajesznuart.h>
#include <stdarg.h>
#include "stm32l4xx_hal.h"

void init_uart() {
	RESET_CLOCK->APB1ENR2 |= (1 << 0);
	RESET_CLOCK->AHB2ENR |= (1 << 2);

	GPIO_PIN_C->AFR[0] |= (1 << 7) | (1 << 3);

	hal_gpios_init(GPIO_PIN_C, 0b1|0b10, ALTUSHKA);

	UART->LPUART_BRR = BLACK_MAGIC;
	UART->LPUART_CR1 |= (1 << 3)|(1 << 2);
	UART->LPUART_CR1 |= (1 << 0);


}

void send(char c) {
	while (!(UART->LPUART_ISR & (1 << 7)));
	UART->LPUART_TDR = c;
}

char get(void) {
	while ((UART->LPUART_ISR & (0x1UL << (5U))) == 0);
	return UART->LPUART_RDR;
}



void hal_gpios_init(Port_Addr* port, uint16_t pins, enum output_mode mode) {
	for (int i = 0; (pins >> i) != 0; ++i) {
		if ((pins >> i) % 2 != 0) {
		switch (mode) {
			case INPUT:
				port->MODER &= ~(11 << i*2);
				break;
			case OUTPUT:
				port->MODER &= ~(1 << (i*2 + 1));
				port->MODER |= (01 << i*2);
				break;
			case ALTUSHKA:
				port->MODER &= ~(1 << (i*2));
				port->MODER |= (01 << (i*2 + 1));
				break;
			case ANAL_OG:
				port->MODER |= (11 << (i*2));
				break;
			}
		}
	}
}

int print_int(int num)
{
    int retval = 0;
    if (num < 0) {
    	send('-');
        retval++;
    }
    num = abs(num);
    if (num / 10) {
        retval += print_int(num / 10);
    }
    char digit = (num % 10) + '0';
    send(digit);
    retval++;
    return retval;
}

int uprintf(char* format, ...)
{
    int retval = 0;
    va_list args;
    va_start(args, format);

    char buffer;
    char* str;
    int num;
    double numbruh;

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;

            switch (*format)
            {
                case 's':
                    str = va_arg(args, char*);
                    while (*str != '\0')
                    {
                        send(*str);
                        retval++;
                        str++;
                    }
                    break;
                case 'd':
                    num = va_arg(args, int);
                    retval += print_int(num);
                    break;
                case 'c':
                    buffer = (char) va_arg(args, int);
                    send(buffer);
                    retval++;
                    break;
                case 'f':
                    numbruh = va_arg(args, double);
                    if (numbruh < 0) {
                    	send('-');
                        retval++;
                    }
                    numbruh = fabs(numbruh);
                    int integer = (int) numbruh;
                    double fractional = numbruh - integer;
                    retval += print_int(integer);
                    send('.');
                    retval++;
                    int i;
                    for (i = 0; i < 5; i++) {
                        fractional *= 10;
                        char output = ((int) fractional % 10) + '0';
                        send(output);
                        retval++;
                    }
                    break;
                default:
                	send(*format);
                    retval++;
                    break;
            }
        }
        else
        {
        	send(*format);
            retval++;
        }

        format++;
    }
    va_end(args);
    return retval;
}

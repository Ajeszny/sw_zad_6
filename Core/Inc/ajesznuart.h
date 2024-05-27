/*
 * ajesznuart.h
 *
 *  Created on: May 24, 2024
 *      Author: Ajeszny
 */

#ifndef INC_AJESZNUART_H_
#define INC_AJESZNUART_H_
#include <stddef.h>
#include "stm32l4xx_hal.h"

typedef  struct
{
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFR[2];
  volatile uint32_t BRR;

} Port_Addr;

typedef  struct
{
	volatile uint32_t CR;
	volatile uint32_t ICSCR;
	volatile uint32_t CFGR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t PLLSAI1CFGR;
	volatile uint32_t PLLSAI2CFGR;
	volatile uint32_t CIER;
	volatile uint32_t CIFR;
	volatile uint32_t CICR;
  uint32_t      RESERVED0;
  volatile uint32_t AHB1RSTR;
  volatile uint32_t AHB2RSTR;
  volatile uint32_t AHB3RSTR;
  uint32_t      RESERVED1;
  volatile uint32_t APB1RSTR1;
  volatile uint32_t APB1RSTR2;
  volatile uint32_t APB2RSTR;
  uint32_t      RESERVED2;
  volatile uint32_t AHB1ENR;
  volatile uint32_t AHB2ENR;
  volatile uint32_t AHB3ENR;
  uint32_t      RESERVED3;
  volatile uint32_t APB1ENR1;
  volatile uint32_t APB1ENR2;
  volatile uint32_t APB2ENR;
  uint32_t      RESERVED4;
  volatile uint32_t AHB1SMENR;
  volatile uint32_t AHB2SMENR;
  volatile uint32_t AHB3SMENR;
  uint32_t      RESERVED5;
  volatile uint32_t APB1SMENR1;
  volatile uint32_t APB1SMENR2;
  volatile uint32_t APB2SMENR;
  uint32_t      RESERVED6;
  volatile uint32_t CCIPR;
  uint32_t      RESERVED7;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
  volatile uint32_t CRRCR;
  volatile uint32_t CCIPR2;
} RCC_Clock;

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t CR4;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t SCR;
  uint32_t RESERVED;
  volatile uint32_t PUCRA;
  volatile uint32_t PDCRA;
  volatile uint32_t PUCRB;
  volatile uint32_t PDCRB;
  volatile uint32_t PUCRC;
  volatile uint32_t PDCRC;
  volatile uint32_t PUCRD;
  volatile uint32_t PDCRD;
  volatile uint32_t PUCRE;
  volatile uint32_t PDCRE;
  volatile uint32_t PUCRF;
  volatile uint32_t PDCRF;
  volatile uint32_t PUCRG;
  volatile uint32_t PDCRG;
  volatile uint32_t PUCRH;
  volatile uint32_t PDCRH;
  volatile uint32_t PUCRI;
  volatile uint32_t PDCRI;
} Power_t;

enum output_mode {
	INPUT = 0b00,
	OUTPUT = 0b01,
	ALTUSHKA = 0b10,
	ANAL_OG = 0b11

};

typedef struct {
	volatile uint32_t LPUART_CR1;
	volatile uint32_t LPUART_CR2;
	volatile uint32_t LPUART_CR3;
	volatile uint32_t LPUART_BRR;
	volatile uint32_t LPUART_RQR;
	volatile uint32_t RESERVED1[2];
	volatile uint32_t LPUART_ISR;
	volatile uint32_t LPUART_ICR;
	volatile uint32_t LPUART_RDR;
	volatile uint32_t LPUART_TDR;
}uart;

#define GPIO_PIN_A ((Port_Addr*)0x48000000)
#define GPIO_PIN_B ((Port_Addr*)0x48000400)
#define GPIO_PIN_C ((Port_Addr*)0x48000800)
#define GPIO_PIN_D ((Port_Addr*)0x48000C00)
#define GPIO_PIN_E ((Port_Addr*)0x48001000)
#define GPIO_PIN_F ((Port_Addr*)0x48001400)
#define GPIO_PIN_G ((Port_Addr*)0x48001800)
#define GPIO_PIN_H ((Port_Addr*)0x48001C00)
#define GPIO_PIN_I ((Port_Addr*)0x48002000)
#define RESET_CLOCK ((RCC_Clock*)0x40021000)
#define POWER ((Power_t*)0x40007000)

#define UART ((uart*)0x40008000)

#define BLACK_MAGIC ((256 * 4000000)/9600) //115200 - szybkosc trasmisji

///ДЕФИНИТИВНЫЙ МАНУАЛ ПОД УАРТ:
///Создано by Маковски дурак sosiety
///ПИНЫ ПОД УАРТ - PC1, PC2
///
void init_uart();
void hal_gpios_init(Port_Addr* port, uint16_t pins, enum output_mode mode);
void send(char c);
char get(void);
#endif /* INC_AJESZNUART_H_ */

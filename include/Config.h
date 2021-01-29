//
// Created by Oleksandr Degtiar on 21.01.2021.
//

#ifndef ZD50_CONFIG_H
#define ZD50_CONFIG_H
#include <avr/io.h>


#ifdef ARDUINO_AVR_UNO
#endif

#ifdef __AVR_ATmega324PA__
#define LED_PIN PINB2

/* EXPANSION IO */
#define ZD50_GPIO1 3
#define ZD50_GPIO2 4

/* SERIAL DEBUG PORT */
#define ZD50_DEBUG_SERIAL
#define SERIAL_DEBUG_BAUD_230400
//#define SERIAL_DEBUG_BAUD_115200
//#define SERIAL_DEBUG_BAUD_38400
#define DEBUG_PIN_TX ZD50_GPIO1
#define DEBUG_PIN_RX ZD50_GPIO2

/* BACKLIGHT */
#define BACKLIGHT_PIN_MASK _BV(6)
#define BACKLIGHT_PORT PORTD

/* PUSH BUTTON */
#define BUTTON_PIN 4
#define BUTTON_BIT _BV(4)
#define BUTTON_PRESS_STATE() (PIND & BUTTON_BIT ? false : true)
#define BUTTON_INIT_PORT() DDRD &= ~(BUTTON_BIT); PORTD |= BUTTON_BIT;

/* ROTARY ENCODER */
#define ROTARY_DDR DDRD
#define ROTARY_PORT PORTD
#define ROTARY_PORTIN PIND
#define ROTARY_PIN_A_BIT _BV(3)
#define ROTARY_PIN_B_BIT _BV(2)

/* ATTENUATOR */
#define ATTENUATOR_PIN_CS_L (1 << 4)
#define ATTENUATOR_PIN_CS_R (1 << 5)
#define ATTENUATOR_PIN_DATA (1 << 6)
#define ATTENUATOR_PIN_CLK (1 << 7)
#define ATTENUATOR_IO_PORT PORTC
#define ATTENUATOR_IO_MASK (ATTENUATOR_PIN_CS_L | ATTENUATOR_PIN_CS_R | ATTENUATOR_PIN_DATA | ATTENUATOR_PIN_CLK)

#define ATTENUATOR_IO_INIT() ( DDRC |= ATTENUATOR_IO_MASK )
#define ATTENUATOR_IO_ALL_LO() ( ATTENUATOR_IO_PORT &= ~(ATTENUATOR_IO_MASK) )

#define ATTENUATOR_IO_CS_LO() ( ATTENUATOR_IO_PORT &= ~(ATTENUATOR_PIN_CS_L | ATTENUATOR_PIN_CS_R) )
#define ATTENUATOR_IO_CS_HI() ( ATTENUATOR_IO_PORT |= (ATTENUATOR_PIN_CS_L | ATTENUATOR_PIN_CS_R) )

#define ATTENUATOR_IO_DO_LO() ( ATTENUATOR_IO_PORT &= ~(ATTENUATOR_PIN_DATA) )
#define ATTENUATOR_IO_DO_HI() ( ATTENUATOR_IO_PORT |= (ATTENUATOR_PIN_DATA) )

#define ATTENUATOR_IO_CLK_LO() ( ATTENUATOR_IO_PORT &= ~(ATTENUATOR_PIN_CLK) )
#define ATTENUATOR_IO_CLK_HI() ( ATTENUATOR_IO_PORT |= (ATTENUATOR_PIN_CLK) )

/* DEBUG LED */

#define LED_ENABLE() DDRB |= _BV(LED_PIN)
#define LED_OFF() PORTB |= _BV(LED_PIN)
#define LED_ON() PORTB &= ~(_BV(LED_PIN))
#define LED_TOGGLE2() PORTB ^= _BV(LED_PIN)
#define LED_TOGGLE() PINB |= _BV(PINB2)

/* *** */


#endif

#ifdef ARDUINO_AVR_FEATHER32U4
#endif

#endif //ZD50_CONFIG_H
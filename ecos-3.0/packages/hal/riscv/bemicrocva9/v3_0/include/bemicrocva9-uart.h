/// Syntacore SCR* infra
///
/// @copyright (C) Syntacore 2015-2016. All rights reserved.
/// @author mn-sc
///
/// @brief UART defs and inline funcs

#ifndef SC1_FPGA_UART_H
#define SC1_FPGA_UART_H

#include <stdint.h>
#include <cyg/hal/hal_io.h>

#ifdef PLF_UART0_BASE

// FPGA UART ports
#define SC1F_UART0_PORT PLF_UART0_BASE

#ifdef PLF_UART0_16550
#define SC1F_UART_RXD       (0x00) // receive data
#define SC1F_UART_TXD       (0x00) // transmit data
#define SC1F_UART_IER       (0x04) // interrupt enable register
#define SC1F_UART_FCR       (0x08) // FIFO control register
#define SC1F_UART_CONTROL   (0x0c) // control register
#define SC1F_UART_MCR       (0x10) // modem control register
#define SC1F_UART_STATUS    (0x14) // status register
#define SC1F_UART_DIV_LO    (0x00) // baud rate divisor register, low
#define SC1F_UART_DIV_HI    (0x04) // baud rate divisor register, low

// UART status register bits
#define SC1F_UART_ST_TEMPTY (1 << 6) // tx empty
#define SC1F_UART_ST_TRDY   (1 << 5) // tx not full
#define SC1F_UART_ST_RRDY   (1 << 0) // rx not empty
#elif defined(PLF_UART0_SCR_RTL)
#define SC1F_UART_TXD       (0x00) // transmit data
#define SC1F_UART_RXD       (0x00) // receive data
#else // PLF_UART0_16550
// UART regs
#define SC1F_UART_RXD       (0x00) // receive data
#define SC1F_UART_TXD       (0x04) // transmit data
#define SC1F_UART_STATUS    (0x08) // status register
#define SC1F_UART_CONTROL   (0x0c) // control register
#define SC1F_UART_BRATE     (0x10) // baud rate divisor register

// UART status register bits
#define SC1F_UART_ST_TEMPTY (0x20) // tx empty
#define SC1F_UART_ST_TRDY   (0x40) // tx not full
#define SC1F_UART_ST_RRDY   (0x80) // rx not empty
#endif // PLF_UART0_16550

// uart low level i/o
static inline void sc1f_uart_write(uintptr_t uart_base, unsigned reg, uint16_t val)
{
    *(volatile uint32_t *)(uart_base + reg) = val;
}

static inline uint16_t sc1f_uart_read(uintptr_t uart_base, unsigned reg)
{
    return *(volatile uint32_t *)(uart_base + reg);
}

// inlines

static inline int sc1f_uart_rx_ready(void)
{
#if defined(PLF_UART0_SCR_RTL)
    return 0;
#else
    return sc1f_uart_read(SC1F_UART0_PORT, SC1F_UART_STATUS) & SC1F_UART_ST_RRDY;
#endif
}

static inline int sc1f_uart_tx_ready(void)
{
#if defined(PLF_UART0_SCR_RTL)
    return 1;
#else
    return sc1f_uart_read(SC1F_UART0_PORT, SC1F_UART_STATUS) & SC1F_UART_ST_TRDY;
#endif
}

static inline void sc1f_uart_tx_flush(void)
{
#if defined(PLF_UART0_SCR_RTL)
#else
    while ((sc1f_uart_read(SC1F_UART0_PORT, SC1F_UART_STATUS) & SC1F_UART_ST_TEMPTY) == 0);
#endif
}

static inline void sc1f_uart_put(uint8_t v)
{
    while (!sc1f_uart_tx_ready());
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_TXD, v);
}

static inline int sc1f_uart_getch_nowait(void)
{
#if defined(PLF_UART0_SCR_RTL)
    return -1; // no input
#else
    if (sc1f_uart_rx_ready())
        return sc1f_uart_read(SC1F_UART0_PORT, SC1F_UART_RXD);
    return -1; // no input
#endif
}

static inline int sc1f_uart_getch(void)
{
    int c;

    do {
        c = sc1f_uart_getch_nowait();
    } while (c == -1);

    return c;
}

// complex uart init/io
/* void sc1f_uart_init(void);
int sc1f_uart_putchar(int v);
void uart_puthex4(uint8_t val);
void uart_puthex8(uint8_t val);
void uart_puthex16(uint16_t val);
void uart_puthex32(uint32_t val);
void uart_putdec(uint32_t v);
void uart_puts(const char *s);
uint32_t uart_read_hex(void); */

// inlines
static inline void sc1f_uart_puthex(uint32_t val) {
    uart_puthex32(val);
}
static inline int uart_putc(int c)
{
    return sc1f_uart_putchar(c);
}
static inline int hal_if_diag_read_char(void) //hal_if_diag_read_char
{
    return sc1f_uart_getch();
}

#endif // PLF_UART0_BASE

#endif // SC1_FPGA_UART_H

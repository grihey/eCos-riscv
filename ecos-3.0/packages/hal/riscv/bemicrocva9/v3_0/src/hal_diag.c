/// Syntacore SCR* infra
///
/// @copyright (C) Syntacore 2015-2016. All rights reserved.
/// @author mn-sc
///
/// @brief implementation of UART i/o funcs

#include <pkgconf/bemicrocva9.h>
#include <pkgconf/system.h>
#include <stdint.h>

enum Uart_consts {
    UART_CLK_FREQ = CYGHWR_HAL_RISCV_CPU_FREQ,
    UART_BAUD_RATE = CYGHWR_UART0_BAUDRATE,
#ifdef CYGHWR_UART0_TYPE_16550
    UART_115200_CLK_DIVISOR = (UART_CLK_FREQ / UART_BAUD_RATE + 7) / 16,
#else // CYGHWR_UART0_TYPE_16550
    UART_115200_CLK_DIVISOR = UART_CLK_FREQ / UART_BAUD_RATE,
#endif // CYGHWR_UART0_TYPE_16550
};

#ifdef CYGHWR_UART0_BASE// in PLATFORM_INC

// FPGA UART ports
#define SC1F_UART0_PORT CYGHWR_UART0_BASE

#ifdef CYGHWR_UART0_TYPE_16550 // to PLATFORM_INC

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
#else // CYGHWR_UART0_TYPE_16550
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
#endif // CYGHWR_UART0_TYPE_16550


// uart low level i/o
void sc1f_uart_write(uintptr_t uart_base, unsigned reg, uint16_t val)
{
    *(volatile uint32_t *)(uart_base + reg) = val;
}

uint16_t sc1f_uart_read(uintptr_t uart_base, unsigned reg)
{
    return *(volatile uint32_t *)(uart_base + reg);
}

int sc1f_uart_rx_ready(void)
{
    return sc1f_uart_read(SC1F_UART0_PORT, SC1F_UART_STATUS) & SC1F_UART_ST_RRDY;
}

int sc1f_uart_tx_ready(void)
{
    return sc1f_uart_read(SC1F_UART0_PORT, SC1F_UART_STATUS) & SC1F_UART_ST_TRDY;
}

void sc1f_uart_tx_flush(void)
{
    while ((sc1f_uart_read(SC1F_UART0_PORT, SC1F_UART_STATUS) & SC1F_UART_ST_TEMPTY) == 0);
}

void sc1f_uart_put(uint8_t v)
{
    while (!sc1f_uart_tx_ready());
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_TXD, v);
}

int sc1f_uart_getch_nowait(void)
{
    if (sc1f_uart_rx_ready())
        return sc1f_uart_read(SC1F_UART0_PORT, SC1F_UART_RXD);
    return -1; // no input
}

void uart_puthex4(uint8_t val)
{
    uint8_t c = val & 0xf;
    sc1f_uart_put(c + (c > 9 ? ('A' - 10) : '0'));
}

void uart_puthex8(uint8_t val)
{
    uart_puthex4(val >> 4);
    uart_puthex4(val);
}

void uart_puthex16(uint16_t val)
{
    uart_puthex8(val >> 8);
    uart_puthex8(val);
}

void uart_puthex32(uint32_t val)
{
    uart_puthex16(val >> 16);
    uart_puthex16(val);
}

int sc1f_uart_getch(void)
{
    int c;

    do {
        c = sc1f_uart_getch_nowait();
    } while (c == -1);

    return c;
}

int sc1f_uart_putchar(int c)
{
    if (c == '\n')
        sc1f_uart_put('\r');
    sc1f_uart_put(c);
    return c;
}
void sc1f_uart_puthex(uint32_t val) {
    uart_puthex32(val);
}

int hal_diag_write_char(int c)
{
    return sc1f_uart_putchar(c);
}

void hal_diag_init(void) //hal_if_diag_init
{
#ifdef CYGHWR_UART0_TYPE_16550
    // disable interrupts
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_IER, 0);
    // init MCR
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_MCR, 0);
    // setup baud rate
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_CONTROL, 0x7 | 0x80);
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_DIV_LO, UART_115200_CLK_DIVISOR & 0xff);
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_DIV_HI, (UART_115200_CLK_DIVISOR >> 8) & 0xff);
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_CONTROL, 0x7);
    // reset fifo and disable
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_FCR, (1 << 2) | (1 << 1) | (0 << 0));
#else // CYGHWR_UART0_TYPE_16550
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_BRATE, UART_115200_CLK_DIVISOR);
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_CONTROL, 0);
#endif // CYGHWR_UART0_TYPE_16550
}


int putchar(int ch) __attribute__((weak, alias("sc1f_uart_putchar")));

int hal_diag_read_char(void)
{
    return sc1f_uart_getch();
}

void uart_putdec(uint32_t v)
{
    unsigned res0 = 0;
    unsigned i0 = 0;

    if (!v) {
        sc1f_uart_putchar('0');
        return;
    }

    for (; i0 < 8 && v; ++i0) {
        res0 = (res0 << 4) | v % 10;
        v /= 10;
    }

    if (v) {
        unsigned res1 = 0;
        unsigned i1 = 0;
        for (; i1 < 2 && v; ++i1) {
            res1 = (res1 << 4) | v % 10;
            v /= 10;
        }
        while (i1--) {
            sc1f_uart_putchar((res1 & 0xf) + '0');
            res1 >>= 4;
        }
    }
    while (i0--) {
        sc1f_uart_putchar((res0 & 0xf) + '0');
        res0 >>= 4;
    }
}

uint32_t uart_read_hex(void)
{
    unsigned len = 0;
    uint32_t res = 0;
    while (1) {
        int c = hal_diag_read_char();
        if ((c >= '0' && c <= '9') || ((c & ~0x20) >= 'A' && (c & ~0x20) <= 'F')) {
            if (len > 7)
                continue;
            sc1f_uart_put(c);
            if (c > '9')
                c = (c & ~0x20) - 'A' + 10;
            else
                c = c - '0';
            ++len;
            res = (res << 4) + (c & 0xf);
        } else if (c == 0x7f || c == 0x8) {
            if (!len)
                continue;
            --len;
            res >>= 4;
            sc1f_uart_put(0x8);
            sc1f_uart_put(' ');
            sc1f_uart_put(0x8);
        } else if (c == '\r') {
            sc1f_uart_put('\n');
            break;
        }
    }

    return res;
}

#endif // PLF_UART0_BASE

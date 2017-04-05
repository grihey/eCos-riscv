/// Syntacore SCR* infra
///
/// @copyright (C) Syntacore 2015-2016. All rights reserved.
/// @author mn-sc
///
/// @brief implementation of UART i/o funcs

#include <cyg/hal/bemicrocva9-uart.h>

enum Uart_consts {
    UART_CLK_FREQ = PLF_SYS_FREQ,
    UART_BAUD_RATE = PLF_UART_BAUDRATE,
#ifdef PLF_UART0_16550
    UART_115200_CLK_DIVISOR = (UART_CLK_FREQ / UART_BAUD_RATE + 7) / 16,
#elif defined(PLF_UART0_SCR_RTL)
#else // PLF_UART0_16550
    UART_115200_CLK_DIVISOR = UART_CLK_FREQ / UART_BAUD_RATE,
#endif // PLF_UART0_16550
};

// uart init
void hal_if_diag_init(void) //hal_if_diag_init
{
#ifdef PLF_UART0_16550
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
#elif defined(PLF_UART0_SCR_RTL)
#else // PLF_UART0_16550
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_BRATE, UART_115200_CLK_DIVISOR);
    sc1f_uart_write(SC1F_UART0_PORT, SC1F_UART_CONTROL, 0);
#endif // PLF_UART0_16550
}

int sc1f_uart_putchar(int c)
{
    if (c == '\n')
        sc1f_uart_put('\r');
    sc1f_uart_put(c);
    return c;
}

int putchar(int ch) __attribute__((weak, alias("sc1f_uart_putchar")));

void hal_if_diag_write_char(const char *s) //hal_if_diag_write_char
{
    while (*s)
        sc1f_uart_putchar(*s++);
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
        int c = hal_if_diag_read_char();
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

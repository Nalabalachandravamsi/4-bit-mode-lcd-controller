void port_intialization(void);
void delay1(long);
void outdata(unsigned char);
void command(unsigned char);
void lcd_initialization(void);
void enable(void);
void go_data(void);
void write_string(char *);

void port_intialization(void) {
    volatile char *outf, *dirf, *outk, *dirk;
    dirf = (volatile char*)0x30;
    dirk = (volatile char*)0x107;
    *dirf = 0xff;
    *dirk = 0x03;
    outf = (volatile char*)0x31;
    outk = (volatile char*)0x108;
}

void delay1(long num) {
    volatile long i;
    while(num) {
        for(i = 0; i < 1000; i++);
        num--;
    }
}

void command(unsigned char data1) {
    volatile char *outf, *outk;
    outf = (volatile char*)0x31;
    outk = (volatile char*)0x108;
    *outf = (data1 & 0xf0);
    enable();
    *outf = ((data1 << 4) & 0xf0);
    enable();
}

void enable(void) {
    volatile char *outk;
    outk = (volatile char*)0x108;
    *outk = 0x01;
    delay1(1);
    *outk = 0x00;
    delay1(1);
}

void outdata(unsigned char data) {
    volatile char *outf, *outk;
    outf = (volatile char*)0x31;
    outk = (volatile char*)0x108;
    *outf = (data & 0xf0);
    go_data();
    *outf = ((data << 4) & 0xf0);
    go_data();
}

void lcd_initialization(void) {
    command(0x02); // return home
    command(0x01); // Clear display    
    command(0x0f); // Display on, cursor off, blink off
    command(0x28); // 4-bit mode, 2 lines, 5x7 font
    command(0x06); // Entry mode set: increment cursor
     
}

void go_data(void) {
    volatile char *outk;
    outk = (volatile char*)0x108;
    *outk = 0x02;
    delay1(1);
    *outk = 0x03;
    delay1(1);
    *outk = 0x02;
    delay1(1);
}

void write_string(char *ptr) {
    while(*ptr) {
        outdata(*ptr);
        ptr++;
    }
}

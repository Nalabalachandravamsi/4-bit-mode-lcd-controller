#include "ECEN.h"

void setup() {
    port_intialization();
    lcd_initialization();
    write_string("   Welcome");
    command(0xc0);
    write_string("To ECEN academy");
}

void loop() {
}

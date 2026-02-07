/* for standalone testing of this file by itself using the simulator,
   keep the following line, but for in-lab activity with the Monitor Program
   to have a multi-file project, comment out the following line */

#define TEST_CHARIO


/* no #include statements should be required, as the character I/O functions
   do not rely on any other code or definitions (the .h file for these
   functions would be included in _other_ .c files) */


/* because all character-I/O code is in this file, the #define statements
   for the JTAG UART pointers can be placed here; they should not be needed
   in any other file */

#define JTAG_UART_DATA   ((volatile unsigned int*)0x10001000)
#define JTAG_UART_STATUS ((volatile unsigned int*)0x10001004)




/* place the full function definitions for the character-I/O routines here */

// star means dereferencing the pointer-- reads value stored at the address instead of the address itself


void PrintChar(int ch)
{
    unsigned int st;
    do
    {
        st = *JTAG_UART_STATUS;
        st = st & 0xFFFF0000;
    } while (st == 0);
    *JTAG_UART_DATA = (unsigned int) ch;
}

void PrintString(char *s)
{
    while (*s != '\0') {
        PrintChar(*s);
        s = s + 1;
    }
}

void PrintHexDigit (unsigned int n) {
    unsigned int ch;

    if (n < 10 ) {
        ch = '0' + n;

    } else {
        ch = 'A' + (n-10);
    }

    PrintChar(ch);
}

unsigned int GetChar(void) {
    unsigned int st, data;

    do {
        st = *JTAG_UART_DATA;
    } while ((st & 0x8000) == 0);

    data = st & 0xFF;

    return data;
}




#ifdef TEST_CHARIO

/* this portion is conditionally compiled based on whether or not
   the symbol exists; it is only for standalone testing of the routines
   using the simulator; there is a main() routine in lab4.c, so
   for the in-lab activity, the following code would conflict with it */

int main (void)
{

  /* place calls here to the various character-I/O routines
     to test their behavior, e.g., PrintString("hello\n");  */
    
    PrintString("Testing PrintString...\n");

    PrintChar('A');
    PrintChar('\n');

    PrintHexDigit(0);
    PrintHexDigit(9);
    PrintHexDigit(10);
    PrintHexDigit(15);
    PrintChar('\n');

    PrintString("Type something: ");
    unsigned int c = GetChar();
    PrintChar('\n');
    PrintString("You typed: ");
    PrintChar(c);
    PrintChar('\n');


    return 0;
} 

#endif /* TEST_CHARIO */

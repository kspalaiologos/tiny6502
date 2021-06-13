# tiny6502
a small (~140 line) and portable 6502 emulator demo.

## files

`test1.bin` and it's disassembly `test1.asm` - a fairly complex 6502 CPU test case that helps to nail most emulation inaccurancies. The default machine is configured to running these.

`6502.c` - the 6502 emulator and a simple test runner attached to it.

`dis6502.c` - 6502 disassembler.

## defining your own machine

First, start off by modifying these:

```c
// Tweak these to your liking.

// Memory size
#define MEM 0x10000
// Stack start address
#define STK 0x200
// BRK vector
#define BRKV 0xF800
// NMI vector
#define NMIV 0xF802
// Reset vector
#define RESV 0xFFFC
// IRQ vector
#define IRQV 0xFFFE
```

...to reflect the position of the IRQ vector, RESET vector, NMI vector and BRK vector. It's recommended to not change the memory size. You can change the stack location. The stack always grows downwards and is not protected against overflows and underflows.

Then, modify the test function to load your ROM:

```c
ZFN(void, test1) {
    memset(m, 0, MEM);
    loadmem("test1.bin", 0x4000);
    init(); res();

    for(;;) {
        step();

        if (pc == 0x45C0) {
            printf("%s\n", m[0x0210] == 0xFF ? "passed" : "failed");
            return;
        }
    }
}
```

Replace `0x4000` with the location where your ROM needs to be loaded and readjust the value of `pc` global variable to set the entry point (after `res`). Then, inside the loop with `step();`, you can add more `if` conditions to define something akin to call gates. For example, before entering the loop, you can set `m[0xFF00] = 0x60;` (put a `RTS` instruction on `$FF00`). Then, we modify the loop accordingly:

```c
    for(;;) {
        step();

        if (pc == 0xFF00) {
            putchar(a);
        }
    }
```

Consequently, `LDA #$30 / JSR $FF00` will print `0`.

MEMORY
{
    VECTBL (rw) : ORIGIN = 0, LENGTH = 0x400
    RAM (rwx) : ORIGIN = 0x400, LENGTH = 1M - 0x400
    ROM (rx) : ORIGIN = 0xe00000, LENGTH = 1M
}

SECTIONS
{
    ENTRY(_start)
    _SSP = ORIGIN(RAM)+LENGTH(RAM);
    _USP = _SSP - 4k;
    .vectors : {*(.vectors)} > VECTBL AT > ROM
    .data : {*(.data)} > RAM AT > ROM
    .bss : {*(.bss) *(COMMON)} > RAM
    .text : {*(.text) *(.rodata)} > ROM
    .rodata : {*(.rodata) *(.rodata*)} > ROM
    _data = ADDR(.data);
    _edata = ADDR(.data) + SIZEOF(.data);
    _ldata = LOADADDR(.data);
    _bss = ADDR(.bss);
    _ebss = ADDR(.bss) + SIZEOF(.bss);
    _vectors = ADDR(.vectors);
    _lvectors = LOADADDR(.vectors);
    _evectors = ADDR(.vectors) + SIZEOF(.vectors);
}

OUTPUT_ARCH(i386:x86-64)
OUTPUT_FORMAT("pei-x86-64")
OUTPUT(./out/bin/main.bin)
STARTUP(./../CRT0/out/lib/crt0.lib)
ENTRY(__start__)
SECTIONS
{
  . = __ImageBase + 0x1000;
  .text : AT(ADDR(.text) - __ImageBase) { *(.text) }
  .data : AT(ADDR(.data) - __ImageBase) { *(.data) }
  .rodata : AT(ADDR(.rodata) - __ImageBase) {*(.rodata)}
  .bss  : AT(ADDR(.bss) - __ImageBase) {
    _BSS_START_ = .;
    *(.bss)
    *(COMMON)
    *(.bss*)
    *(.stack)    
    _BSS_END_ = .;
  }
}
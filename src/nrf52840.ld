MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x100000
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x40000
}

SECTIONS
{
  .text :
  {
    KEEP(*(.vectors))
    *(.text*)
  } > FLASH

  .data :
  {
    *(.data*)
  } > RAM

  .bss :
  {
    *(.bss*)
  } > RAM
}

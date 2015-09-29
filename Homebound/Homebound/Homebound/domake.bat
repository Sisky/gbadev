path=C:\Users\Siisky\Desktop\GBA_Dev\devkitadv-r5-beta-3\bin

REM compiling with below line makes things run very slow
REM gcc  -o homebound.elf main.c gfx.c -lm

gcc -c -O3 -mthumb -mthumb-interwork gfx.c
gcc -c -O3 -mthumb -mthumb-interwork main.c

gcc -mthumb -mthumb-interwork -o homebound.elf main.o gfx.o 

objcopy -O binary homebound.elf homebound.gba

pause
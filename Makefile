CC = arm-none-eabi-gcc
MACH = cortex-m4
CFLAGS = -c -mcpu=$(MACH) -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -std=gnu11 -Wall
LDFLAGS = -nostdlib -T stm32_ls.ld -Wl,-Map=final.map

all: BFILES final.elf
BFILES:
	mkdir -p BFILES

BFILES/%.o: %.c | BFILES
	$(CC) $(CFLAGS) $< -o $@

BFILES/%.o: sources/%.c | BFILES
	$(CC) $(CFLAGS) $< -o $@

final.elf: BFILES/main.o BFILES/USART.o BFILES/DMA.o BFILES/ADC.o BFILES/TIMERS.o BFILES/RCC.o BFILES/GPIO.o BFILES/I2C.o BFILES/SPI.o BFILES/stm32_startup.o BFILES/stm32fx.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -rf BFILES *.o *.elf

load:
	openocd -f board/st_nucleo_f4.cfg 

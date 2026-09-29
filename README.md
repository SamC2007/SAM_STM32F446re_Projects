# SAM STM32F446re Nucleo Library

Summary: This is a GitHub repo of a journey that displays my experience in learning the STM32 
microcontroller. Throughout this journey I was able to learn about registers and bitwise operations
in order to program such registers. One thing that was challenging in this journey was learning the 
I2C peripheral. The reason being is that unlike SPI and UART, this serial communicator involved more 
complex protocols and external hardware like pull resistors. I ran into a lot of I2C errors like 
ack failure, and the controller hogging the bus resulting in a stuck bus. I overcame these challenges by 
using debugging tools such as GDB and logic analyzer; helped by pinpointing where I went wrong. Overall 
this was a great journey that allowed me to create cool projects of my own.

## This GitHub Repository Includes:
* Header Files
* Source Files
* Projects
* Startup Code

### Header Files
The header files contain type definitions, function definitions and struct definitions. The file 
[stm32fx.h](https://github.com/SamC2007/SAM_STM32F446re_Projects/blob/main/headers/stm32fx.h) is 
different because it contains type defintions of NVIC found in the arm cortex m4. It also contains 
print functions and declarations of certain hardware such as USART2 and TIM6. USART2 is manily used 
to define print functions found in [stm32fx.c](https://github.com/SamC2007/SAM_STM32F446re_Projects/blob/main/headers/stm32fx.c). 
There is also a delay function prototype.

As mentioned, the peripheral headers files contain type definitions, function definitons, and struct 
definitions. In the struct defintions for each peripheral I define three: handler register, configuration 
register and the actual hardware register.
### Source Files
The source files contain the implementation of the function definitions found in [stm32fx.h](https://github.com/SamC2007/SAM_STM32F446re_Projects/blob/main/headers/stm32fx.h). 
Here I take what the user defined in their configuration struct, and turn that into the real 
register implementation for that peripheral.

### Projects
Here are some projects that I wanted to share to give an idea of how to use the library. My first project 
is a joystick module, where I utilize ADC and DMA to measure the joy stick x and y axis. The second 
project is a ultrasonic sensor where I configure two general purpose timer, one for input and the other 
for output capture. The input capture is used to capture the ultrasonic reads, and the output capture is 
configured in PWM mode to drive the LED brightness based on the distance between an object and the sensor. 

### Startup Code
The .c file is used to help the MCU call main and to copy the .data section into RAM. Not only that but 
it also defines the interrupt handlers to be later used by the programmer. The linker script (.ld) is used 
to tell the Linker how to map the binary code and data to the physical memory layout.

################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/core.c \
../Src/delay.c \
../Src/fonts.c \
../Src/i2c.c \
../Src/main.c \
../Src/spi.c \
../Src/st7789.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/core.o \
./Src/delay.o \
./Src/fonts.o \
./Src/i2c.o \
./Src/main.o \
./Src/spi.o \
./Src/st7789.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/core.d \
./Src/delay.d \
./Src/fonts.d \
./Src/i2c.d \
./Src/main.d \
./Src/spi.d \
./Src/st7789.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE=STM32F411xE -c -I"C:/Moje_pliki/Programowanie/STM/TFT_Display_test/Inne/ST7789_IPS_TFT/Inc" -I"C:/Moje_pliki/Programowanie/STM/TFT_Display_test/Inne/ST7789_IPS_TFT/F4_chip_headers/CMSIS/Include" -I"C:/Moje_pliki/Programowanie/STM/TFT_Display_test/Inne/ST7789_IPS_TFT/F4_chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/core.cyclo ./Src/core.d ./Src/core.o ./Src/core.su ./Src/delay.cyclo ./Src/delay.d ./Src/delay.o ./Src/delay.su ./Src/fonts.cyclo ./Src/fonts.d ./Src/fonts.o ./Src/fonts.su ./Src/i2c.cyclo ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/spi.cyclo ./Src/spi.d ./Src/spi.o ./Src/spi.su ./Src/st7789.cyclo ./Src/st7789.d ./Src/st7789.o ./Src/st7789.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src


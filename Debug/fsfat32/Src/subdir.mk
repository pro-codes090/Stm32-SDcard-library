################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fsfat32/Src/fsfat32.c 

OBJS += \
./fsfat32/Src/fsfat32.o 

C_DEPS += \
./fsfat32/Src/fsfat32.d 


# Each subdirectory must supply rules for building sources it contributes
fsfat32/Src/%.o: ../fsfat32/Src/%.c fsfat32/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/pro/Documents/stm32drivers/stm32f4_sdcard_spi/fsfat32" -I"C:/Users/pro/Documents/stm32drivers/stm32f4_sdcard_spi/fsfat32/Inc" -I"C:/Users/pro/Documents/stm32drivers/stm32f4_sdcard_spi/fsfat32/Src" -I"C:/Users/pro/Documents/stm32drivers/stm32f4_sdcard_spi/drivers/Inc" -I"C:/Users/pro/Documents/stm32drivers/stm32f4_sdcard_spi/drivers/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-fsfat32-2f-Src

clean-fsfat32-2f-Src:
	-$(RM) ./fsfat32/Src/fsfat32.d ./fsfat32/Src/fsfat32.o

.PHONY: clean-fsfat32-2f-Src


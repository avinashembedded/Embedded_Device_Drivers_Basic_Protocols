################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/src/gpio.c \
../Driver/src/i2c.c \
../Driver/src/spi.c \
../Driver/src/stm32f0xx_rcc_driver.c \
../Driver/src/usart.c 

OBJS += \
./Driver/src/gpio.o \
./Driver/src/i2c.o \
./Driver/src/spi.o \
./Driver/src/stm32f0xx_rcc_driver.o \
./Driver/src/usart.o 

C_DEPS += \
./Driver/src/gpio.d \
./Driver/src/i2c.d \
./Driver/src/spi.d \
./Driver/src/stm32f0xx_rcc_driver.d \
./Driver/src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/src/%.o Driver/src/%.su Driver/src/%.cyclo: ../Driver/src/%.c Driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DNUCLEO_G070RB -DSTM32G070RBTx -DSTM32 -DSTM32G0 -c -I../Inc -I"E:/Avinash_STM32CubeIDE_Workspace/RTOS_Workspace/GPIO_DRIVER/Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-src

clean-Driver-2f-src:
	-$(RM) ./Driver/src/gpio.cyclo ./Driver/src/gpio.d ./Driver/src/gpio.o ./Driver/src/gpio.su ./Driver/src/i2c.cyclo ./Driver/src/i2c.d ./Driver/src/i2c.o ./Driver/src/i2c.su ./Driver/src/spi.cyclo ./Driver/src/spi.d ./Driver/src/spi.o ./Driver/src/spi.su ./Driver/src/stm32f0xx_rcc_driver.cyclo ./Driver/src/stm32f0xx_rcc_driver.d ./Driver/src/stm32f0xx_rcc_driver.o ./Driver/src/stm32f0xx_rcc_driver.su ./Driver/src/usart.cyclo ./Driver/src/usart.d ./Driver/src/usart.o ./Driver/src/usart.su

.PHONY: clean-Driver-2f-src


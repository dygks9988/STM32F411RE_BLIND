################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hw/driver/button.c \
../hw/driver/hw_adc.c \
../hw/driver/hw_motor.c \
../hw/driver/hw_tim.c \
../hw/driver/lcd.c \
../hw/driver/led.c \
../hw/driver/uart.c 

OBJS += \
./hw/driver/button.o \
./hw/driver/hw_adc.o \
./hw/driver/hw_motor.o \
./hw/driver/hw_tim.o \
./hw/driver/lcd.o \
./hw/driver/led.o \
./hw/driver/uart.o 

C_DEPS += \
./hw/driver/button.d \
./hw/driver/hw_adc.d \
./hw/driver/hw_motor.d \
./hw/driver/hw_tim.d \
./hw/driver/lcd.d \
./hw/driver/led.d \
./hw/driver/uart.d 


# Each subdirectory must supply rules for building sources it contributes
hw/driver/%.o hw/driver/%.su hw/driver/%.cyclo: ../hw/driver/%.c hw/driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"C:/stm_workspace_1.16.1/stm32f411_RE/rtos" -I../Core/Inc -I"C:/stm_workspace_1.16.1/stm32f411_RE/ap" -I"C:/stm_workspace_1.16.1/stm32f411_RE/hw" -I"C:/stm_workspace_1.16.1/stm32f411_RE/ap/module" -I"C:/stm_workspace_1.16.1/stm32f411_RE/hw/driver" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-hw-2f-driver

clean-hw-2f-driver:
	-$(RM) ./hw/driver/button.cyclo ./hw/driver/button.d ./hw/driver/button.o ./hw/driver/button.su ./hw/driver/hw_adc.cyclo ./hw/driver/hw_adc.d ./hw/driver/hw_adc.o ./hw/driver/hw_adc.su ./hw/driver/hw_motor.cyclo ./hw/driver/hw_motor.d ./hw/driver/hw_motor.o ./hw/driver/hw_motor.su ./hw/driver/hw_tim.cyclo ./hw/driver/hw_tim.d ./hw/driver/hw_tim.o ./hw/driver/hw_tim.su ./hw/driver/lcd.cyclo ./hw/driver/lcd.d ./hw/driver/lcd.o ./hw/driver/lcd.su ./hw/driver/led.cyclo ./hw/driver/led.d ./hw/driver/led.o ./hw/driver/led.su ./hw/driver/uart.cyclo ./hw/driver/uart.d ./hw/driver/uart.o ./hw/driver/uart.su

.PHONY: clean-hw-2f-driver


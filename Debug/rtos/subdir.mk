################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rtos/display_task.c \
../rtos/rtos_task.c \
../rtos/sensor_task.c \
../rtos/servo_motor_task.c \
../rtos/smart_blind_task.c \
../rtos/stopwatch_task.c \
../rtos/uart_cmd_task.c 

OBJS += \
./rtos/display_task.o \
./rtos/rtos_task.o \
./rtos/sensor_task.o \
./rtos/servo_motor_task.o \
./rtos/smart_blind_task.o \
./rtos/stopwatch_task.o \
./rtos/uart_cmd_task.o 

C_DEPS += \
./rtos/display_task.d \
./rtos/rtos_task.d \
./rtos/sensor_task.d \
./rtos/servo_motor_task.d \
./rtos/smart_blind_task.d \
./rtos/stopwatch_task.d \
./rtos/uart_cmd_task.d 


# Each subdirectory must supply rules for building sources it contributes
rtos/%.o rtos/%.su rtos/%.cyclo: ../rtos/%.c rtos/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"C:/stm_workspace_1.16.1/stm32f411_RE/rtos" -I../Core/Inc -I"C:/stm_workspace_1.16.1/stm32f411_RE/ap" -I"C:/stm_workspace_1.16.1/stm32f411_RE/hw" -I"C:/stm_workspace_1.16.1/stm32f411_RE/ap/module" -I"C:/stm_workspace_1.16.1/stm32f411_RE/hw/driver" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-rtos

clean-rtos:
	-$(RM) ./rtos/display_task.cyclo ./rtos/display_task.d ./rtos/display_task.o ./rtos/display_task.su ./rtos/rtos_task.cyclo ./rtos/rtos_task.d ./rtos/rtos_task.o ./rtos/rtos_task.su ./rtos/sensor_task.cyclo ./rtos/sensor_task.d ./rtos/sensor_task.o ./rtos/sensor_task.su ./rtos/servo_motor_task.cyclo ./rtos/servo_motor_task.d ./rtos/servo_motor_task.o ./rtos/servo_motor_task.su ./rtos/smart_blind_task.cyclo ./rtos/smart_blind_task.d ./rtos/smart_blind_task.o ./rtos/smart_blind_task.su ./rtos/stopwatch_task.cyclo ./rtos/stopwatch_task.d ./rtos/stopwatch_task.o ./rtos/stopwatch_task.su ./rtos/uart_cmd_task.cyclo ./rtos/uart_cmd_task.d ./rtos/uart_cmd_task.o ./rtos/uart_cmd_task.su

.PHONY: clean-rtos


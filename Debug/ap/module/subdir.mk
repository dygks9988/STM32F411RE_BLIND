################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ap/module/ap_lcd.c \
../ap/module/cds.c \
../ap/module/servo_motor.c \
../ap/module/stopwatch.c \
../ap/module/uart_cmd.c 

OBJS += \
./ap/module/ap_lcd.o \
./ap/module/cds.o \
./ap/module/servo_motor.o \
./ap/module/stopwatch.o \
./ap/module/uart_cmd.o 

C_DEPS += \
./ap/module/ap_lcd.d \
./ap/module/cds.d \
./ap/module/servo_motor.d \
./ap/module/stopwatch.d \
./ap/module/uart_cmd.d 


# Each subdirectory must supply rules for building sources it contributes
ap/module/%.o ap/module/%.su ap/module/%.cyclo: ../ap/module/%.c ap/module/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"C:/stm_workspace_1.16.1/stm32f411_RE/rtos" -I../Core/Inc -I"C:/stm_workspace_1.16.1/stm32f411_RE/ap" -I"C:/stm_workspace_1.16.1/stm32f411_RE/hw" -I"C:/stm_workspace_1.16.1/stm32f411_RE/ap/module" -I"C:/stm_workspace_1.16.1/stm32f411_RE/hw/driver" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ap-2f-module

clean-ap-2f-module:
	-$(RM) ./ap/module/ap_lcd.cyclo ./ap/module/ap_lcd.d ./ap/module/ap_lcd.o ./ap/module/ap_lcd.su ./ap/module/cds.cyclo ./ap/module/cds.d ./ap/module/cds.o ./ap/module/cds.su ./ap/module/servo_motor.cyclo ./ap/module/servo_motor.d ./ap/module/servo_motor.o ./ap/module/servo_motor.su ./ap/module/stopwatch.cyclo ./ap/module/stopwatch.d ./ap/module/stopwatch.o ./ap/module/stopwatch.su ./ap/module/uart_cmd.cyclo ./ap/module/uart_cmd.d ./ap/module/uart_cmd.o ./ap/module/uart_cmd.su

.PHONY: clean-ap-2f-module


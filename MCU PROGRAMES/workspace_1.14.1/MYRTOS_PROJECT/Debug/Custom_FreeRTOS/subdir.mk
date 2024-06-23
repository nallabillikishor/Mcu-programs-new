################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Custom_FreeRTOS/croutine.c \
../Custom_FreeRTOS/event_groups.c \
../Custom_FreeRTOS/list.c \
../Custom_FreeRTOS/queue.c \
../Custom_FreeRTOS/stream_buffer.c \
../Custom_FreeRTOS/tasks.c \
../Custom_FreeRTOS/timers.c 

OBJS += \
./Custom_FreeRTOS/croutine.o \
./Custom_FreeRTOS/event_groups.o \
./Custom_FreeRTOS/list.o \
./Custom_FreeRTOS/queue.o \
./Custom_FreeRTOS/stream_buffer.o \
./Custom_FreeRTOS/tasks.o \
./Custom_FreeRTOS/timers.o 

C_DEPS += \
./Custom_FreeRTOS/croutine.d \
./Custom_FreeRTOS/event_groups.d \
./Custom_FreeRTOS/list.d \
./Custom_FreeRTOS/queue.d \
./Custom_FreeRTOS/stream_buffer.d \
./Custom_FreeRTOS/tasks.d \
./Custom_FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Custom_FreeRTOS/%.o Custom_FreeRTOS/%.su Custom_FreeRTOS/%.cyclo: ../Custom_FreeRTOS/%.c Custom_FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/tarun/STM32CubeIDE/workspace_1.14.1/MYRTOS_PROJECT/Custom_FreeRTOS/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Custom_FreeRTOS

clean-Custom_FreeRTOS:
	-$(RM) ./Custom_FreeRTOS/croutine.cyclo ./Custom_FreeRTOS/croutine.d ./Custom_FreeRTOS/croutine.o ./Custom_FreeRTOS/croutine.su ./Custom_FreeRTOS/event_groups.cyclo ./Custom_FreeRTOS/event_groups.d ./Custom_FreeRTOS/event_groups.o ./Custom_FreeRTOS/event_groups.su ./Custom_FreeRTOS/list.cyclo ./Custom_FreeRTOS/list.d ./Custom_FreeRTOS/list.o ./Custom_FreeRTOS/list.su ./Custom_FreeRTOS/queue.cyclo ./Custom_FreeRTOS/queue.d ./Custom_FreeRTOS/queue.o ./Custom_FreeRTOS/queue.su ./Custom_FreeRTOS/stream_buffer.cyclo ./Custom_FreeRTOS/stream_buffer.d ./Custom_FreeRTOS/stream_buffer.o ./Custom_FreeRTOS/stream_buffer.su ./Custom_FreeRTOS/tasks.cyclo ./Custom_FreeRTOS/tasks.d ./Custom_FreeRTOS/tasks.o ./Custom_FreeRTOS/tasks.su ./Custom_FreeRTOS/timers.cyclo ./Custom_FreeRTOS/timers.d ./Custom_FreeRTOS/timers.o ./Custom_FreeRTOS/timers.su

.PHONY: clean-Custom_FreeRTOS


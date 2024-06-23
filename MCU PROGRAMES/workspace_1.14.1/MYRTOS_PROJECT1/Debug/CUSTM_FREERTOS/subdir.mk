################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CUSTM_FREERTOS/croutine.c \
../CUSTM_FREERTOS/event_groups.c \
../CUSTM_FREERTOS/list.c \
../CUSTM_FREERTOS/queue.c \
../CUSTM_FREERTOS/stream_buffer.c \
../CUSTM_FREERTOS/tasks.c \
../CUSTM_FREERTOS/timers.c 

OBJS += \
./CUSTM_FREERTOS/croutine.o \
./CUSTM_FREERTOS/event_groups.o \
./CUSTM_FREERTOS/list.o \
./CUSTM_FREERTOS/queue.o \
./CUSTM_FREERTOS/stream_buffer.o \
./CUSTM_FREERTOS/tasks.o \
./CUSTM_FREERTOS/timers.o 

C_DEPS += \
./CUSTM_FREERTOS/croutine.d \
./CUSTM_FREERTOS/event_groups.d \
./CUSTM_FREERTOS/list.d \
./CUSTM_FREERTOS/queue.d \
./CUSTM_FREERTOS/stream_buffer.d \
./CUSTM_FREERTOS/tasks.d \
./CUSTM_FREERTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
CUSTM_FREERTOS/%.o CUSTM_FREERTOS/%.su CUSTM_FREERTOS/%.cyclo: ../CUSTM_FREERTOS/%.c CUSTM_FREERTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/tarun/STM32CubeIDE/workspace_1.14.1/MYRTOS_PROJECT1/Drivers/CMSIS/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CUSTM_FREERTOS

clean-CUSTM_FREERTOS:
	-$(RM) ./CUSTM_FREERTOS/croutine.cyclo ./CUSTM_FREERTOS/croutine.d ./CUSTM_FREERTOS/croutine.o ./CUSTM_FREERTOS/croutine.su ./CUSTM_FREERTOS/event_groups.cyclo ./CUSTM_FREERTOS/event_groups.d ./CUSTM_FREERTOS/event_groups.o ./CUSTM_FREERTOS/event_groups.su ./CUSTM_FREERTOS/list.cyclo ./CUSTM_FREERTOS/list.d ./CUSTM_FREERTOS/list.o ./CUSTM_FREERTOS/list.su ./CUSTM_FREERTOS/queue.cyclo ./CUSTM_FREERTOS/queue.d ./CUSTM_FREERTOS/queue.o ./CUSTM_FREERTOS/queue.su ./CUSTM_FREERTOS/stream_buffer.cyclo ./CUSTM_FREERTOS/stream_buffer.d ./CUSTM_FREERTOS/stream_buffer.o ./CUSTM_FREERTOS/stream_buffer.su ./CUSTM_FREERTOS/tasks.cyclo ./CUSTM_FREERTOS/tasks.d ./CUSTM_FREERTOS/tasks.o ./CUSTM_FREERTOS/tasks.su ./CUSTM_FREERTOS/timers.cyclo ./CUSTM_FREERTOS/timers.d ./CUSTM_FREERTOS/timers.o ./CUSTM_FREERTOS/timers.su

.PHONY: clean-CUSTM_FREERTOS


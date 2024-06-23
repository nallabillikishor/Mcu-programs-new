################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CUSTM_FREERTOS/portable/MemMang/heap_4.c 

OBJS += \
./CUSTM_FREERTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./CUSTM_FREERTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
CUSTM_FREERTOS/portable/MemMang/%.o CUSTM_FREERTOS/portable/MemMang/%.su CUSTM_FREERTOS/portable/MemMang/%.cyclo: ../CUSTM_FREERTOS/portable/MemMang/%.c CUSTM_FREERTOS/portable/MemMang/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/tarun/STM32CubeIDE/workspace_1.14.1/MYRTOS_PROJECT1/Drivers/CMSIS/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-CUSTM_FREERTOS-2f-portable-2f-MemMang

clean-CUSTM_FREERTOS-2f-portable-2f-MemMang:
	-$(RM) ./CUSTM_FREERTOS/portable/MemMang/heap_4.cyclo ./CUSTM_FREERTOS/portable/MemMang/heap_4.d ./CUSTM_FREERTOS/portable/MemMang/heap_4.o ./CUSTM_FREERTOS/portable/MemMang/heap_4.su

.PHONY: clean-CUSTM_FREERTOS-2f-portable-2f-MemMang


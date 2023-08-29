################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/streambuffer/cmd_buffer.c 

OBJS += \
./user/streambuffer/cmd_buffer.o 

C_DEPS += \
./user/streambuffer/cmd_buffer.d 


# Each subdirectory must supply rules for building sources it contributes
user/streambuffer/%.o user/streambuffer/%.su user/streambuffer/%.cyclo: ../user/streambuffer/%.c user/streambuffer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../user/streambuffer -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-user-2f-streambuffer

clean-user-2f-streambuffer:
	-$(RM) ./user/streambuffer/cmd_buffer.cyclo ./user/streambuffer/cmd_buffer.d ./user/streambuffer/cmd_buffer.o ./user/streambuffer/cmd_buffer.su

.PHONY: clean-user-2f-streambuffer


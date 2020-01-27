################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pressure/lps25hb.c 

OBJS += \
./pressure/lps25hb.o 

C_DEPS += \
./pressure/lps25hb.d 


# Each subdirectory must supply rules for building sources it contributes
pressure/lps25hb.o: ../pressure/lps25hb.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DEXTERNAL_CLOCK_VALUE=8000000' '-DHSE_VALUE=8000000' '-DHSE_STARTUP_TIMEOUT=100' -DDEBUG '-DLSE_STARTUP_TIMEOUT=5000' '-DLSE_VALUE=32768' '-DVDD_VALUE=3300' '-DLSI_VALUE=40000' '-DHSI_VALUE=8000000' -DSTM32F303x8 -DUSE_FULL_LL_DRIVER '-DPREFETCH_ENABLE=1' -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../display -I../humidity_temperature -I../accelerometer -I../pressure -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"pressure/lps25hb.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


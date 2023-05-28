################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AFIO_program.c \
../src/APP.c \
../src/DIO_program.c \
../src/Delay.c \
../src/EXTI_program.c \
../src/IR_program.c \
../src/LEDMRX_program.c \
../src/NVIC_program.c \
../src/RCC_program.c \
../src/SYSTICK_program.c 

OBJS += \
./src/AFIO_program.o \
./src/APP.o \
./src/DIO_program.o \
./src/Delay.o \
./src/EXTI_program.o \
./src/IR_program.o \
./src/LEDMRX_program.o \
./src/NVIC_program.o \
./src/RCC_program.o \
./src/SYSTICK_program.o 

C_DEPS += \
./src/AFIO_program.d \
./src/APP.d \
./src/DIO_program.d \
./src/Delay.d \
./src/EXTI_program.d \
./src/IR_program.d \
./src/LEDMRX_program.d \
./src/NVIC_program.d \
./src/RCC_program.d \
./src/SYSTICK_program.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



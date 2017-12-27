################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../._main.c \
../adc-api.c \
../cloud-api.c \
../command.c \
../examples-api.c \
../gpio-api.c \
../http-api.c \
../module-api.c \
../pwm-api.c \
../security-api.c \
../websocket-api.c \
../wifi-api.c \
../wifi-auto.c 

OBJS += \
./._main.o \
./adc-api.o \
./cloud-api.o \
./command.o \
./examples-api.o \
./gpio-api.o \
./http-api.o \
./module-api.o \
./pwm-api.o \
./security-api.o \
./websocket-api.o \
./wifi-api.o \
./wifi-auto.o 

C_DEPS += \
./._main.d \
./adc-api.d \
./cloud-api.d \
./command.d \
./examples-api.d \
./gpio-api.d \
./http-api.d \
./module-api.d \
./pwm-api.d \
./security-api.d \
./websocket-api.d \
./wifi-api.d \
./wifi-auto.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARTIK GCC C Compiler'
	arm-none-eabi-gcc  -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/include" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/include/apps" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/framework_include" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/apps_include" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/apps_include/netutils" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/artik-sdk_include" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/artik-sdk_include/base" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/artik-sdk_include/connectivity" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/artik-sdk_include/systemio" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/artik-sdk_include/wifi" -I"C:/ARTIK/SDK/A053/v1.2/libsdk/typical/artik-sdk_include/lwm2m" -O0 -ffunction-sections -fdata-sections -fno-builtin -fno-strict-aliasing -fno-strength-reduce -fomit-frame-pointer -Wstrict-prototypes -Wshadow -Wno-implicit-function-declaration -Wno-unused-function -Wno-unused-but-set-variable -DAPP_STACKSIZE=18432 -DAPP_PRIORITY=100 -mcpu=cortex-r4 -mfpu=vfpv3 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



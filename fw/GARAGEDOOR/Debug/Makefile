################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../src/ \
../src/asf/ \
../src/asf/common/ \
../src/asf/common/boards/ \
../src/asf/common/services/ \
../src/asf/common/services/clock/ \
../src/asf/common/services/clock/mega/ \
../src/asf/common/services/delay/ \
../src/asf/common/services/delay/mega/ \
../src/asf/common/services/gpio/ \
../src/asf/common/services/gpio/mega_gpio/ \
../src/asf/common/services/ioport/ \
../src/asf/common/services/ioport/mega/ \
../src/asf/common/utils/ \
../src/asf/common/utils/interrupt/ \
../src/asf/common/utils/make/ \
../src/asf/mega/ \
../src/asf/mega/drivers/ \
../src/asf/mega/drivers/cpu/ \
../src/asf/mega/utils/ \
../src/asf/mega/utils/assembler/ \
../src/config/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../src/asf/common/services/clock/mega/sysclk.c \
../src/inputs.c \
../src/relays.c \
../src/rtc.c \
../src/sm.c \
../src/uart.c \
../src/main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
src/asf/common/services/clock/mega/sysclk.o \
src/inputs.o \
src/relays.o \
src/rtc.o \
src/sm.o \
src/uart.o \
src/main.o


OBJS_AS_ARGS +=  \
src/asf/common/services/clock/mega/sysclk.o \
src/inputs.o \
src/relays.o \
src/rtc.o \
src/sm.o \
src/uart.o \
src/main.o


C_DEPS +=  \
src/asf/common/services/clock/mega/sysclk.d \
src/inputs.d \
src/relays.d \
src/rtc.d \
src/sm.d \
src/uart.d \
src/main.d


C_DEPS_AS_ARGS +=  \
src/asf/common/services/clock/mega/sysclk.d \
src/inputs.d \
src/relays.d \
src/rtc.d \
src/sm.d \
src/uart.d \
src/main.d


OUTPUT_FILE_PATH +=GARAGEDOOR.elf

OUTPUT_FILE_PATH_AS_ARGS +=GARAGEDOOR.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler















src/asf/common/services/clock/mega/%.o: ../src/asf/common/services/clock/mega/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -DBOARD=STK600_MEGA  -I"../src" -I"../src/asf/common/applications/user_application/atmega16_stk600-mega" -I"../src/asf/common/boards" -I"../src/asf/common/utils" -I"../src/asf/mega/utils" -I"../src/config" -I"../src/asf/mega/drivers/cpu" -I"../src/asf/common/services/clock" -I"../src/asf/common/services/delay" -I"../src/asf/common/services/gpio" -I"../src/asf/common/services/ioport"  -O1 -fdata-sections -ffunction-sections -g3 -Wall -c -Werror-implicit-function-declaration -Wmissing-prototypes -Wpointer-arith -Wstrict-prototypes -mrelax -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega16a   -o"$@" "$<" 
	@echo Finished building: $<

src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -DBOARD=STK600_MEGA  -I"../src" -I"../src/asf/common/applications/user_application/atmega16_stk600-mega" -I"../src/asf/common/boards" -I"../src/asf/common/utils" -I"../src/asf/mega/utils" -I"../src/config" -I"../src/asf/mega/drivers/cpu" -I"../src/asf/common/services/clock" -I"../src/asf/common/services/delay" -I"../src/asf/common/services/gpio" -I"../src/asf/common/services/ioport"  -O1 -fdata-sections -ffunction-sections -g3 -Wall -c -Werror-implicit-function-declaration -Wmissing-prototypes -Wpointer-arith -Wstrict-prototypes -mrelax -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega16a   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="GARAGEDOOR.map" -Wl,--start-group  -Wl,--end-group -Wl,--gc-sections -mrelax -Wl,--relax  -mmcu=atmega16a  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "GARAGEDOOR.elf" "GARAGEDOOR.hex"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "GARAGEDOOR.elf" "GARAGEDOOR.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objdump.exe" -h -S "GARAGEDOOR.elf" > "GARAGEDOOR.lss"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "GARAGEDOOR.elf" "GARAGEDOOR.srec"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-size.exe" "GARAGEDOOR.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "GARAGEDOOR.elf" "GARAGEDOOR.a" "GARAGEDOOR.hex" "GARAGEDOOR.lss" "GARAGEDOOR.eep" "GARAGEDOOR.map" "GARAGEDOOR.srec"
	
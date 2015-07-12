################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
display.obj: ../display.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Development/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="D:/Development/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/example/common" -g --define=cc3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="display.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Development/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="D:/Development/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/example/common" -g --define=cc3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pin_mux_config.obj: ../pin_mux_config.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Development/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="D:/Development/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/example/common" -g --define=cc3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="pin_mux_config.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart_if.obj: D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/example/common/uart_if.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"D:/Development/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="D:/Development/TI/ccsv6/tools/compiler/ti-cgt-arm_5.2.4/include" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/driverlib" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/inc" --include_path="D:/Development/TI/CC3200SDK_1.1.0/cc3200-sdk/example/common" -g --define=cc3200 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="uart_if.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



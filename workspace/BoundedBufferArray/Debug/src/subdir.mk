################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Test.cpp \
../src/bounded_buffer_content_suite.cpp \
../src/bounded_buffer_content_suite_no_default.cpp \
../src/bounded_buffer_default_behavior_suite.cpp \
../src/bounded_buffer_semantic_suite.cpp \
../src/bounded_buffer_semantic_suite_no_default.cpp \
../src/bounded_buffer_signatures_suite.cpp \
../src/bounded_buffer_student_suite.cpp 

CPP_DEPS += \
./src/Test.d \
./src/bounded_buffer_content_suite.d \
./src/bounded_buffer_content_suite_no_default.d \
./src/bounded_buffer_default_behavior_suite.d \
./src/bounded_buffer_semantic_suite.d \
./src/bounded_buffer_semantic_suite_no_default.d \
./src/bounded_buffer_signatures_suite.d \
./src/bounded_buffer_student_suite.d 

OBJS += \
./src/Test.o \
./src/bounded_buffer_content_suite.o \
./src/bounded_buffer_content_suite_no_default.o \
./src/bounded_buffer_default_behavior_suite.o \
./src/bounded_buffer_semantic_suite.o \
./src/bounded_buffer_semantic_suite_no_default.o \
./src/bounded_buffer_signatures_suite.o \
./src/bounded_buffer_student_suite.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1z -I"/Users/sop/Documents/talks/Firmenkurse/workshop/sources/CPPCourseExpert/workspace/BoundedBufferArray/cute" -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Test.d ./src/Test.o ./src/bounded_buffer_content_suite.d ./src/bounded_buffer_content_suite.o ./src/bounded_buffer_content_suite_no_default.d ./src/bounded_buffer_content_suite_no_default.o ./src/bounded_buffer_default_behavior_suite.d ./src/bounded_buffer_default_behavior_suite.o ./src/bounded_buffer_semantic_suite.d ./src/bounded_buffer_semantic_suite.o ./src/bounded_buffer_semantic_suite_no_default.d ./src/bounded_buffer_semantic_suite_no_default.o ./src/bounded_buffer_signatures_suite.d ./src/bounded_buffer_signatures_suite.o ./src/bounded_buffer_student_suite.d ./src/bounded_buffer_student_suite.o

.PHONY: clean-src


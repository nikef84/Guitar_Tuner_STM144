# C source files
PROJECT_CSRC 	= 	src/main.c \
					src/terminal_write.c \
					src/micro/adc_lld.c \
					src/micro/signal_recording.c \
					src/findPeaks/power_fft.c \
					src/findPeaks/find_peaks.c \
					src/modes/one_string_mode.c \
					src/modes/six_string_mode.c \
					src/modes/find_string_freqs.c \
					tests/one_string_mode_test.c \
					tests/six_string_mode_test.c \
					tests/find_string_freqs_test.c \
					tests/labview_test.c \
					tests/blink_test.c \
					tests/stepper_motor_test.c \
					tests/terminal_write_test.c \
					tests/adc_test.c \
					tests/signal_recording_test.c \
					tests/fft_test.c \
					tests/find_peaks_test.c \
					tests/sort_funcs_test.c \
					tests/pwm_test.c \	
					
					
							

# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include \
                  include/findPeaks \
                  include/modes \
                  include/micro \
 

# Additional libraries
PROJECT_LIBS	= -lm
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1 -specs=nano.specs -specs=nosys.specs

# Additional .mk files are included here
CSRC = $(ALLCSRC) \
       $(TESTSRC) \
       $(PROJECT_CSRC) \
       $(CHIBIOS)/os/various/evtimer.c
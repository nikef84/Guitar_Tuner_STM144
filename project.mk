# C source files
PROJECT_CSRC 	= 	src/main.c \
					src/terminal_write.c \
					src/adc_lld.c \
					src/signal_recording.c \
					src/findPeaks/power_fft.c \
					src/findPeaks/findPeaks.c \
					src/modes/one_string_mode.c \
					tests/one_string_mode_test.c \
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
                  tests \
                  include/findPeaks \
                  include/modes \
 

# Additional libraries
PROJECT_LIBS	= -lm
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1 -specs=nano.specs -specs=nosys.specs

# Additional .mk files are included here
CSRC = $(ALLCSRC) \
       $(TESTSRC) \
       $(PROJECT_CSRC) \
       $(CHIBIOS)/os/various/evtimer.c
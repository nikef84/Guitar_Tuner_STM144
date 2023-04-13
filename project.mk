# C source files
PROJECT_CSRC 	= 	src/main.c \
					src/findPeaks/find_peaks.c \
					src/findPeaks/power_fft.c \
					src/indication/indication.c \
					src/micro/adc_lld.c \
					src/micro/signal_recording.c \
					src/modes/find_string_freqs.c \
					src/modes/one_string_mode.c \
					src/modes/six_string_mode.c \
					src/servo/servo_control.c \
					src/servo/servo_lld.c \
					src/terminal_write/terminal_write.c \
					
					
					
TESTSRC 	= 		tests/findPeaks/fft_test.c \
					tests/findPeaks/find_peaks_test.c \
					tests/indication/indication_test.c \
					tests/micro/adc_test.c \
					tests/micro/signal_recording_test.c \
					tests/modes/find_string_freqs_test.c \
					tests/modes/labview_test.c \
					tests/modes/one_string_mode_test.c \
					tests/modes/six_string_mode_test.c \
					tests/servo/mailbox_test.c \
					tests/servo/servo_control_test.c \
					tests/servo/servo_simple_test.c \
					tests/servo/servo_with_micro_test.c \
					
					
					

# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include \
                  include/findPeaks \
                  include/indication \
                  include/micro \
                  include/modes \
                  include/servo \
                  include/terminal_write \
 

# Additional libraries
PROJECT_LIBS	= -lm
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1 -specs=nano.specs -specs=nosys.specs

# Additional .mk files are included here
CSRC = $(ALLCSRC) \
       $(TESTSRC) \
       $(PROJECT_CSRC) \
       $(CHIBIOS)/os/various/evtimer.c
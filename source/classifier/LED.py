import RPi.GPIO as GPIO
import sys

# When calling the function:
#  Let 1 indicate the block is in the set
#      2 indicate the block is not in the set

def inSet( clr ):
    "This function will flash a green or red light if the block is or is not in the set respectively"
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(5, GPIO.OUT)
    GPIO.setup(6, GPIO.OUT)
    GPIO.setup(13, GPIO.OUT)

    if clr==1:
        # Turn the LED green
        GPIO.output(5, GPIO.LOW)
        GPIO.output(6, GPIO.LOW)
        GPIO.output(13, GPIO.HIGH)
    elif clr==2:
        # Turn the LED red
        GPIO.output(5, GPIO.HIGH)
        GPIO.output(6, GPIO.LOW)
        GPIO.output(13, GPIO.LOW)
    else:
        # Default: turn the LED blue if input was recieved but invalid
        GPIO.output(5, GPIO.LOW)
        GPIO.output(6, GPIO.HIGH)
        GPIO.output(13, GPIO.LOW)

    
    GPIO.output(5, GPIO.LOW)
    GPIO.output(6, GPIO.LOW)
    GPIO.output(13, GPIO.LOW)
    GPIO.cleanup()
    return;

inSet(int(sys.argv[1]))

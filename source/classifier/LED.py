import RPi.GPIO as GPIO

# When calling the function:
#  Let 1 indicate the block is in the set
#      2 indicate the block is not in the set

def inSet( clr ):
    "This function will flash a green or red light if the block is or is not in the set respectively"
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(29, GPIO.OUT)
    GPIO.setup(31, GPIO.OUT)
    GPIO.setup(33, GPIO.OUT)

    if clr==1:
        GPIO.output(29, GPIO.LOW)
        GPIO.output(31, GPIO.LOW)
        GPIO.output(33, GPIO.HIGH)
    elif clr==2:
        GPIO.output(29, GPIO.HIGH)
        GPIO.output(31, GPIO.LOW)
        GPIO.output(33, GPIO.LOW)
    else:
        GPIO.output(29, GPIO.LOW)
        GPIO.output(31, GPIO.HIGH)
        GPIO.output(33, GPIO.LOW)

    
    GPIO.output(29, GPIO.LOW)
    GPIO.output(31, GPIO.LOW)
    GPIO.output(33, GPIO.LOW)
    GPIO.cleanup()
    return;
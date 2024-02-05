import RPi.GPIO as GPIO
import time

NUM_PIXELS = 8
PIXEL_PIN = 18
DELAY = 0.2

GPIO.setmode(GPIO.BCM)

GPIO.setup(PIXEL_PIN, GPIO.OUT)

for x in range(NUM_PIXELS):
    GPIO.output(PIXEL_PIN, GPIO.HIGH)
    time.sleep(0.2)
    GPIO.output(PIXEL_PIN, GPIO.LOW)
    time.sleep(DELAY - 0.2)
    
GPIO.output(PIXEL_PIN, GPIO.LOW)

GPIO.cleanup()

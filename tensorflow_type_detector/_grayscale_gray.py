
import os
import numpy as np
import sys
import cv2

for file in os.listdir(sys.argv[1]):
    filename = os.fsdecode(file)
    if filename.endswith(".jpg"):
        img = cv2.imread(filename)
        gray = cv2.cvtColor(img, cv2.COLOR_RGBA2GRAY)

        gaussian_3 = cv2.GaussianBlur(gray, (9, 9), 10.0)
        unsharp = cv2.addWeighted(gray, 1.5, gaussian_3, -0.5, 0, img)

        cv2.imwrite(filename, unsharp)
        print(filename)



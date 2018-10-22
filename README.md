This project will sort lego pieces into their distinct colour and shape groups (ie, 3x2 thin yellow block), and sort them into full lego sets. It uses a camera connected to a raspberry pi to take pictures of the blocks, then uses OpenCV to detect if there is a block in the image. It then uses a retrained tensorflow neural network (InceptionV3) to recognize the block shape and colour, and check if the block is within a user-inputted lego set. It flashes an LED to indicate if it is within the set.

Includes:
1) Source contains the overview code to run the detection on the RaspberryPi. It also contains the initial code to perform block detection and classification using OpenCV, as well as the set management code
2) tensorflow_color_detector includes the retrained model InceptionV3, trained to recognize block colour, as well as a function to augment the cour dataset by rotating images
3) tensorflow_detect_block includes the retrained model InceptionV3, trained to recognize if there is a block in the image, as well as the greyscale functions to augment the dataset by greyscaling and rotating images
4) tensorflow_type_detector includes the retrained model InceptionV3, trained to recognize lego block type, as well as the greyscale functions to augment the dataset by greyscaling and rotating images

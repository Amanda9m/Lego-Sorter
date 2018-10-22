# Overview

This directory includes the InceptionV3 Tensorflow model, retrained to predict the types of lego blocks.  The actual training occurs under the tf_files subheader, and all pictures are sorted into the Lego_block_pictures folder. This folder also contains code to greyscale the blocks, and include rotated and differently greyscaled versions of each block to augment the dataset. To run the currently trained module, use command:

python3 -m scripts.label_image \
--graph=tf_files/retrained_graph.pb  \
--image=[wheretheimageis]

for example

python3 -m scripts.label_image \
--graph=tf_files/retrained_graph.pb  \
--image=tf_files/Lego_block_pictures_color/red/img_0013.jpg

to retrain, use:

python3 -m scripts.retrain \
--bottleneck_dir=tf_files/bottlenecks \
--model_dir=tf_files/models/"${ARCHITECTURE}" \
--summaries_dir=tf_files/training_summaries/"${ARCHITECTURE}" \
--output_graph=tf_files/retrained_graph.pb \
--output_labels=tf_files/retrained_labels.txt \
--architecture="${ARCHITECTURE}" \
--image_dir=tf_files/Lego_block_pictures_color

This code is based upon the module at: https://codelabs.developers.google.com/codelabs/tensorflow-for-poets/#3

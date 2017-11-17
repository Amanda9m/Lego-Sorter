# Overview

This repo contains code for the
["TensorFlow for poets 2" codelab](https://codelabs.developers.google.com/codelabs/tensorflow-for-poets-2).

This repo contains a simplified and trimmed down version of tensorflow's
[android image classification example](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/examples/android)
in the `android/` directory.

The `scripts` directory contains helpers for the codelab.

This has been edited to work for lego blocks. The actual training occurs under the tf_files subheader, and all pictures are sorted into the Lego_block_pictures folder. To run the currently trained module, use command

python3 -m scripts.label_image \
--graph=tf_files/retrained_graph.pb  \
--image=[wheretheimageis]

for example

python3 -m scripts.label_image \
--graph=tf_files/retrained_graph.pb  \
--image=tf_files/Lego_block_pictures/rectangular_4x2/img_0013.jpg

to retrain, use:

python -m scripts.retrain \
--bottleneck_dir=tf_files/bottlenecks \
--model_dir=tf_files/models/"${ARCHITECTURE}" \
--summaries_dir=tf_files/training_summaries/"${ARCHITECTURE}" \
--output_graph=tf_files/retrained_graph.pb \
--output_labels=tf_files/retrained_labels.txt \
--architecture="${ARCHITECTURE}" \
--image_dir=tf_files/Lego_block_pictures

All commands and knowledge comes from this module: https://codelabs.developers.google.com/codelabs/tensorflow-for-poets/#3

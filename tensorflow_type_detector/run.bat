
python -m scripts.retrain --bottleneck_dir=tf_files/bottlenecks --model_dir=tf_files/models/mobilenet_0.50_224 --summaries_dir=tf_files/training_summaries/mobilenet_0.50_224 --output_graph=tf_files/retrained_graph.pb --output_labels=tf_files/retrained_labels.txt --architecture=mobilenet_0.50_224 --image_dir=tf_files/Lego_block_pictures

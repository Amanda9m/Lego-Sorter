
@echo off

rem python -m scripts.retrain  ^
rem 	--bottleneck_dir=tf_files/bottlenecks ^
rem 	--model_dir=tf_files/models/mobilenet_0.50_224 ^
rem 	--summaries_dir=tf_files/training_summaries/mobilenet_0.50_224 ^
rem 	--output_graph=tf_files/retrained_graph.pb ^
rem 	--output_labels=tf_files/retrained_labels.txt ^
rem 	--architecture=mobilenet_0.50_224 ^
rem 	--image_dir=tf_files/Lego_block_pictures_color
	
python -m tensorflow.python.tools.optimize_for_inference ^
	--input  tf_files/retrained_graph.pb ^
	--output tf_files/retrained_graph.pb ^
	--input_names input ^
	--output_names final_result


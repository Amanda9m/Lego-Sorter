
@echo off

rem python -m scripts.retrain  ^
rem 	--bottleneck_dir=tf_files/bottlenecks ^
rem 	--model_dir=tf_files/models/mobilenet_0.50_224 ^
rem 	--summaries_dir=tf_files/training_summaries/mobilenet_0.50_224 ^
rem 	--output_graph=tf_files/out1_graph.pb ^
rem 	--output_labels=tf_files/retrained_labels.txt ^
rem 	--architecture=mobilenet_0.50_224 ^
rem 	--image_dir=tf_files/Lego_block_pictures
	
@echo on
	
python -m tensorflow.python.tools.freeze_graph ^
	--input_graph tf_files/out1_graph.pb ^
	--output_graph tf_files/out2_graph.pb ^
	--output_node_names final_result
	
python -m tensorflow.tools.graph_transforms.transform_graph ^
	--in_graph tf_files/out2_graph.pb ^
	--out_graph tf_files/out3_graph.pb ^
	--inputs input ^
	--outputs final_result ^
	--transforms "fold_constants sort_by_execution_order"
	
python -m tensorflow.python.tools.optimize_for_inference ^
	--input  tf_files/out3_graph.pb ^
	--output tf_files/retrained_graph.pb ^
	--input_names input ^
	--output_names final_result
	
rem python -m tensorflow.python.tools.optimize_for_inference ^
	rem --input tf_files/retrained_graph.pb ^
	rem --output tf_files/opt_graph.pb ^
	rem --frozen_graph True


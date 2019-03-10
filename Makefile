images := output.yuv*

yv_nv: jni/yv12_nv21.cpp
	g++ -std=c++17 jni/yv12_nv21.cpp -o $@

output.yuv: input.jpg
	ffmpeg -i $< -f rawvideo -pix_fmt yuv420p $@

output.nv21.yuv: yv_nv output.yuv
	./$< output.yuv 3840 2160

output.nv21.yuv.png: output.nv21.yuv
	ffmpeg -f rawvideo -pix_fmt nv21 -s 3840x2160 -i $< $@

output.nv21.yuv.gray.png: output.nv21.yuv
	ffmpeg -f rawvideo -pix_fmt gray -s 3840x3240 -i $< $@

view: output.nv21.yuv.png
	display $<

clean:
	rm -f $(images)

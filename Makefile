images := dsc.yuv*

yv_nv: jni/yv12_nv21.cpp
	g++ -std=c++17 jni/yv12_nv21.cpp -o $@

dsc.yuv: input.jpg
	ffmpeg -i $< -f rawvideo -pix_fmt yuv420p $@

dsc.yuv.nv21: yv_nv dsc.yuv
	./$< dsc.yuv 3840 2160

dsc.yuv.nv21.png: dsc.yuv.nv21
	ffmpeg.exe -f rawvideo -pix_fmt nv21 -s 3840x2160 -i $< $@

dsc.yuv.nv21.gray.png: dsc.yuv.nv21
	ffmpeg.exe -f rawvideo -pix_fmt gray -s 3840x3240 -i $< $@

view: dsc.yuv.nv21.png
	display $<

clean:
	rm $(images)

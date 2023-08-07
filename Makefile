build:
	g++ -std=c++11 -o project2.out src/*.cpp

run:
	./project2.out output/part1.tga input/layer1.tga multiply input/pattern1.tga
	./project2.out output/part2.tga input/layer2.tga subtract input/car.tga
	./project2.out output/part3.tga input/layer1.tga multiply input/pattern2.tga screen input/text.tga
	./project2.out output/part4.tga input/layer2.tga multiply input/circles.tga subtract input/pattern2.tga
	./project2.out output/part5.tga input/layer1.tga overlay input/pattern1.tga
	./project2.out output/part6.tga input/car.tga addgreen 200
	./project2.out output/part7.tga input/car.tga scalered 4 scaleblue 0
	./project2.out output/part8_r.tga input/car.tga onlyred
	./project2.out output/part8_b.tga input/car.tga onlyblue
	./project2.out output/part8_g.tga input/car.tga onlygreen
	./project2.out output/part9.tga input/layer_red.tga combine input/layer_blue.tga input/layer_green.tga
	./project2.out output/part10.tga input/text2.tga flip

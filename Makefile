main:main.cc
	g++ $^ -o $@ -g 

.PHONY:clean
clean:
	rm main

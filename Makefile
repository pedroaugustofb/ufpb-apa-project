FILES := $(wildcard ./input/*.txt)

run: main.cpp
	g++ main.cpp entities/*.cpp components/*.cpp -o main
	@$(foreach file,$(FILES), main $(file) -m $())

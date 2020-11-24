LIB = -lm -lwiringPi -lpthread
# -lcrypt -lrt
STD = --std=c++2a
CPP = g++
OUT = mq
#-Wshadow -fsanitize=address -fsanitize=undefined -fno-sanitize-recover
all: clean
	$(CPP) $(STD) -Wall main.cpp config.cpp functions.cpp homme.cpp info.cpp message.cpp sensors.cpp server.cpp $(LIB) -o $(OUT)
clean:
	rm -rf $(OUT)
	rm -rf ./$(OUT)_mem
#install:
#	sudo cp homme.service /etc/systemd/system/homme.service
#	sudo systemctl daemon-reload
#	sudo systemctl enable homme
#	sudo systemctl start homme
check:
	#cppcheck $(STD) --suppress=missingIncludeSystem -x c --platform=unix64 --force --enable=all --inconclusive ./
	rm -rf ./$(OUT)_mem
	$(CPP) $(STD) -O0 -g -Wall main.cpp config.cpp functions.cpp homme.cpp info.cpp message.cpp sensors.cpp server.cpp $(LIB) -o $(OUT)_mem
	sudo valgrind --leak-check=full --show-leak-kinds=all ./$(OUT)_mem

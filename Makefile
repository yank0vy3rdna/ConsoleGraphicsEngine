all:
	g++ main.cpp -D_GNU_SOURCE -D_DEFAULT_SOURCE -I/usr/include/ncursesw -lncursesw -ltinfo 

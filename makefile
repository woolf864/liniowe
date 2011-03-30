all : asd

asd : asd.cc main.cc
	clang++ asd.cc timer.cc main.cc -o asd 
	
del :
	rm asd
debug : asd.cc
	clang++ -g asd.cc /home/common/dyd/aisdi/liniowe/timer.cc /home/common/dyd/aisdi/liniowe/main.cc /home/common/dyd/aisdi/tests/ltest_liniowe.so -o asd_debug
	gdb asd_debug 
	

view:
	lynx /home/common/dyd/aisdi/liniowe/info/index.html

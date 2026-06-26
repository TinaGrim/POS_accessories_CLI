ifeq ($(OS), Windows_NT)
	target = main.exe
	remove = if exit $(target) del $(target)
else
	target = main
	remove = rm -f
endif
scrs = main.cpp scr/mystack.cpp scr/Items.cpp scr/login.cpp util/urlpath.cpp scr/windowmanager.cpp util/myString.cpp
linkflags = -D_XOPEN_SOURCE_EXTENDED
flags = -lncursesw -lqrencode


all: $(target)

$(target) : $(scrs)
	g++ -o $@ $(linkflags) $(scrs) $(flags)  

run: $(target)
	./$(target)

clean: 
	$(remove)

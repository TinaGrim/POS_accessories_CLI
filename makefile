scrs = main.cpp scr/mystack.cpp scr/Items.cpp util/urlpath.cpp util/windowmanager.cpp
flags = -lncursesw -lqrencode
target = main


all: $(target)

$(target) : $(scrs)
	g++ -o $@ $(scrs) $(flags)  

run: $(target)
	./$(target)

clean: 
	rm -f $(target)

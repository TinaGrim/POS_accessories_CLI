scrs = main.cpp mystack.cpp Items.cpp 
flags = -lncursesw
target = main


all: $(target)

$(target) : $(scrs)
	g++ -o $@ $(scrs) $(flags)  

run: $(target)
	./$(target)

clean: 
	rm -f $(target)

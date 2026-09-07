ifeq ($(OS), Windows_NT)
	PLATFORM = windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Darwin)
		PLATFORM = macos
	else ifeq ($(UNAME_S), Linux)
		PLATFORM = linux
	endif
endif

scrs = main.cpp scr/mystack.cpp scr/Items.cpp scr/login.cpp util/urlpath.cpp scr/windowmanager.cpp util/myString.cpp

CXXFLAGS = -std=c++17 -D_XOPEN_SOURCE_EXTENDED

ifeq ($(PLATFORM), windows)
	target = main.exe
	remove = if exist $(target) del $(target)
	LDLIBS = -lncursesw -lqrencode

else ifeq ($(PLATFORM), macos)
	target = main
	remove = rm -f
	HOMEBREW_PREFIX := $(shell brew --prefix)
	CXXFLAGS += -I$(HOMEBREW_PREFIX)/opt/ncurses/include -I$(HOMEBREW_PREFIX)/include
	LDFLAGS  += -L$(HOMEBREW_PREFIX)/opt/ncurses/lib -L$(HOMEBREW_PREFIX)/lib
	LDLIBS   = -lncursesw -lqrencode

else ifeq ($(PLATFORM), linux)
	target = main
	remove = rm -f
	LDLIBS = -lncursesw -lqrencode
endif

all: $(target)

$(target): $(scrs)
	g++ -o $@ $(CXXFLAGS) $(scrs) $(LDFLAGS) $(LDLIBS)

run: $(target)
	./$(target)

clean:
	$(remove) $(target)

PROG = $(patsubst %.cpp,%,$(wildcard *.cpp))
PHPPROG = $(wildcard *.php)
# OBS = $(wildcard ../obj/*.o)

include $(shell echo $${PREFIX-/usr})/share/smartmet/devel/makefile.inc

INCLUDES += -I../woml -I/usr/include/smartmet

LIBS += -L.. -Wl,--rpath,$(shell pwd)/.. -lsmartmet-woml \
	$(PREFIX_LDFLAGS) \
	-lsmartmet-macgyver \
	-lboost_system \
	-lxerces-c \
	-lxqilla

all: $(PROG)
clean:
	rm -f $(PROG) *~

test: $(PROG)
	@echo Running tests:
	@for prog in $(PROG); do \
	 ./$$prog; \
	done
	@echo
	@for prog in $(PHPPROG); do \
	 php -q $$prog; \
	done

$(PROG) : % : %.cpp ../libsmartmet-woml.so
	$(CXX) $(CFLAGS) -o $@ $@.cpp $(INCLUDES) $(LIBS)


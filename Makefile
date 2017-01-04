SUBNAME = woml
LIB = smartmet-$(SUBNAME)
SPEC = smartmet-library-$(SUBNAME)
INCDIR = smartmet/$(SUBNAME)


# Using 'scons' for building (make clean|release|debug|profile)
#
#
# To build serially (helps get the error messages right): make debug SCONS_FLAGS=""

SCONS_FLAGS=-j 4

# Installation directories

prosessor := $(shell uname -p)

ifeq ($(origin PREFIX), undefined)
  PREFIX = /usr
else
  PREFIX = $(PREFIX)
endif

ifeq ($(prosessor), x86_64)
  libdir = $(PREFIX)/lib64
else
  libdir = $(PREFIX)/lib
endif

includedir = $(PREFIX)/include
objdir = obj

ifeq ($(origin BINDIR), undefined)
  bindir = $(PREFIX)/bin
else
  bindir = $(BINDIR)
endif

# rpm variables

rpmsourcedir=/tmp/$(shell whoami)/rpmbuild

rpmexcludevcs := $(shell tar --help | grep -m 1 -o -- '--exclude-vcs')

# What to install

LIBFILE = lib$(LIB).a

# How to install

INSTALL_PROG = install -m 775
INSTALL_DATA = install -m 664

.PHONY: test rpm

#
# The rules
#
SCONS_FLAGS += objdir=$(objdir)

all release:
	scons $(SCONS_FLAGS) $(LIBFILE)

$(LIBFILE):
	scons $(SCONS_FLAGS) $@

debug:
	scons $(SCONS_FLAGS) debug=1 $(LIBFILE)

profile:
	scons $(SCONS_FLAGS) profile=1 $(LIBFILE)

clean:
	@#scons -c objdir=$(objdir)
	-rm -f $(LIBFILE) *~ source/*~ include/*~
	-rm -rf $(objdir)

format:
	clang-format -i -style=file include/*.h source/*.cpp test/*.cpp

install:
	@mkdir -p $(includedir)/$(INCDIR)
	@list=`cd include && ls -1 *.h`; \
	for hdr in $$list; do \
	  echo $(INSTALL_DATA) include/$$hdr $(includedir)/$(INCDIR)/$$hdr; \
	  $(INSTALL_DATA) include/$$hdr $(includedir)/$(INCDIR)/$$hdr; \
	done
	@mkdir -p $(libdir)
	$(INSTALL_DATA) $(LIBFILE) $(libdir)/$(LIBFILE)

test:
	cd test && make test

rpm: clean
	if [ -e $(SPEC).spec ]; \
	then \
	  mkdir -p $(rpmsourcedir) ; \
	  tar $(rpmexcludevcs) -C ../ -cf $(rpmsourcedir)/$(SPEC).tar $(SUBNAME) ; \
	  gzip -f $(rpmsourcedir)/$(SPEC).tar ; \
	  TAR_OPTIONS=--wildcards rpmbuild -ta $(rpmsourcedir)/$(SPEC).tar.gz ; \
	  rm -f $(rpmsourcedir)/$(SPEC).tar.gz ; \
	else \
	  echo $(rpmerr); \
	fi;

headertest:
	@echo "Checking self-sufficiency of each header:"
	@echo
	@for hdr in $(HDRS); do \
	echo $$hdr; \
	echo "#include \"$$hdr\"" > /tmp/$(LIB).cpp; \
	echo "int main() { return 0; }" >> /tmp/$(LIB).cpp; \
	$(CC) $(CFLAGS) $(INCLUDES) -o /dev/null /tmp/$(LIB).cpp $(LIBS); \
	done

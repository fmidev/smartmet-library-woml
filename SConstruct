#
# SConstruct for building WOML
#
# Usage:
#       scons [-j 4] [-Q] [debug=1|profile=1] [objdir=<path>] smartmet_woml.a|lib
#             [windows_boost_path=<path>]
#
# Notes:
#       The three variants (debug/release/profile) share the same output and 
#       object file names;
#       changing from one version to another will cause a full recompile.
#       This is intentional (instead of keeping, say, out/release/...)
#       for compatibility with existing test suite etc. and because normally
#       different machines are used only for debug/release/profile.

import os.path, os

Help(""" 
    Usage: scons [-j 4] [-Q] [debug=1|profile=1] [objdir=<path>] smartmet_woml.a|lib
    
    Or just use 'make release|debug|profile', which point right back to us.
""") 

Decider("MD5-timestamp") 

DEBUG=      int( ARGUMENTS.get("debug", 0) ) != 0
PROFILE=    int( ARGUMENTS.get("profile", 0) ) != 0
RELEASE=    (not DEBUG) and (not PROFILE)     # default

OBJDIR=     ARGUMENTS.get("objdir","obj")

env = Environment( )

env.Append(LIBS="smartmet_macgyver-mt")

env.ParseConfig( "(pkg-config --exists libxml++-2.6 && pkg-config libxml++-2.6 --cflags --libs)" )

env.Append( CPPPATH= [ "./include" ] )
env.Append( CPPDEFINES= ["UNIX"] )
env.Append( CXXFLAGS= [
        # MAINFLAGS from orig. Makefile
        "-fPIC",
        "-Wall", 
        "-Wno-unused-parameter",
        "-Wno-variadic-macros",
	    
	    # DIFFICULTFLAGS from orig. Makefile
	    #
	    # These are flags that would be good, but give hard to bypass errors
	    #
	    #"-Wunreachable-code", gives errors if enabled (NFmiSaveBase.h:88)
	    #"-Weffc++",           gives errors if enabled (NFmiVoidPtrList.h: operator++)
	    #"-pedantic",          Boost errors (on OS X, Boost 1.35)
    ] )


if DEBUG:
	env.Append( CXXFLAGS=[ "-O0", "-g", "-Werror",
    
	# EXTRAFLAGS from orig. Makefile (for 'debug' target)
        #
        "-ansi",
        "-Wcast-align",
        "-Wcast-qual",
        "-Wconversion",
        "-Winline",
        "-Wno-multichar",
        "-Wno-pmf-conversions",
        "-Woverloaded-virtual",
        "-Wpointer-arith",
        "-Wredundant-decls",
        "-Wwrite-strings"
    
            # Disabled because of Boost 1.35
            #"-Wold-style-cast",
            #"-Wshadow",
            # "-Wsign-promo",
        ] )

#
# Release settings
#
if RELEASE or PROFILE:
	env.Append( CPPDEFINES="NDEBUG",
        	    CXXFLAGS= ["-O2",
	            "-Wuninitialized",
        ] )


# Profile settings
#
if PROFILE:
	env.Append( CXXFLAGS="-g -pg" )

# Exceptions to the regular compilation rules (from orig. Makefile)

objs= []
env.Append( CPPDEFINES="FMI_MULTITHREAD" )
env.Append( CPPDEFINES= "_REENTRANT" )

if DEBUG:
        e_O0= env       # No change, anyways

        e_noerror= env.Clone()
        e_noerror["CXXFLAGS"].remove( "-Werror" )
        e_noerror["CXXFLAGS"].append( "-Wno-error" )
        
else:
        e_O0= env.Clone()
        e_O0["CXXFLAGS"].remove("-O2")
        e_O0["CXXFLAGS"].append("-O0")
        e_O0["CXXFLAGS"].remove("-Wuninitialized")    # not supported without '-O'

        e_noerror= env    # anyways no -Werror

for fn in Glob("source/*.cpp"): 
	s= os.path.basename( str(fn) )
	obj_s= OBJDIR+"/"+ s.replace(".cpp","")
	objs += env.Object( obj_s, fn )

 # Make just the static lib

env.Library( "smartmet_woml", objs )

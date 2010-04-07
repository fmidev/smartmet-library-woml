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

WINDOWS_BOOST_PATH= ARGUMENTS.get("windows_boost_path","")

env= Environment( )

LINUX=  env["PLATFORM"]=="posix"
OSX=    env["PLATFORM"]=="darwin"
WINDOWS= env["PLATFORM"]=="win32"

#
# SCons does not pass env.vars automatically through to executing commands.
# On Windows, we want it to get them all (Visual C++ 2008).
#
if WINDOWS:
    env.Replace( ENV= os.environ )

env.Append( CPPPATH= [ "./include" ] )

if WINDOWS:
    if env["CC"]=="cl":
        env.Append( CXXFLAGS= ["/EHsc"] )
else:
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

BOOST_POSTFIX=""
BOOST_PREFIX=""

if WINDOWS:
    # Installed from 'boost_1_35_0_setup.exe' from BoostPro Internet page.
    #
    env.Append( CPPPATH= [ WINDOWS_BOOST_PATH ] )
    env.Append( LIBPATH= [ WINDOWS_BOOST_PATH + "/lib" ] )
    if DEBUG:
        BOOST_POSTFIX= "-vc90-mt-gd-1_35"
    else:
        BOOST_POSTFIX= "-vc90-mt-1_35"
        BOOST_PREFIX= "lib"
elif LINUX:
    BOOST_POSTFIX= "-mt"

elif OSX:
    # Boost from Fink
    #
    env.Append( CPPPATH= [ "/sw/include" ] )
    env.Append( LIBPATH= [ "/sw/lib" ] )

#
# Debug settings
#
if DEBUG:
    if WINDOWS:
        if env["CC"]=="cl":
            env.AppendUnique( CPPDEFINES=["_DEBUG","DEBUG"] )
            # Debug multithreaded DLL runtime, no opt.
            env.AppendUnique( CCFLAGS=["/MDd", "/Od"] )
            # Each obj gets own .PDB so parallel building (-jN) works
            env.AppendUnique( CCFLAGS=["/Zi", "/Fd${TARGET}.pdb"] )
    else:
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
    if WINDOWS:
        if env["CC"]=="cl":
            # multithreaded DLL runtime, reasonable opt.
            env.AppendUnique( CCFLAGS=["/MD", "/Ox"] )
    else:
        env.Append( CPPDEFINES="NDEBUG",
                    CXXFLAGS= ["-O2",

            # RELEASEFLAGS from orig. Makefile (for 'release' and 'profile' targets)
            #
            "-Wuninitialized",
        ] )


#
# Profile settings
#
if PROFILE:
    if WINDOWS: 
        { }     # TBD
    else:
        env.Append( CXXFLAGS="-g -pg" )


# Exceptions to the regular compilation rules (from orig. Makefile)

objs= []
env.Append( CPPDEFINES="FMI_MULTITHREAD" )
if not WINDOWS:
    env.Append( CPPDEFINES= "_REENTRANT" )

if WINDOWS:
    for fn in Glob("source/*.cpp"): 
        s= os.path.basename( str(fn) )
        obj_s= OBJDIR+"/"+ s.replace(".cpp","")

        objs += env.Object( obj_s, fn )
else:
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

out_postfix= WINDOWS and (DEBUG and "_debug" or "_release") or ""

env.Library( "smartmet_woml"+out_postfix, objs )

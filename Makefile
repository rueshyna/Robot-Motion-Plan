#############################################################################
# Makefile for building: bin/pro
# Generated by qmake (2.01a) (Qt 4.6.2) on: Wed Dec 22 22:07:33 2010
# Project:  pro.pro
# Template: app
# Command: /usr/bin/qmake -unix QMAKE_CXXFLAGS_WARN_ON= DESTDIR=./bin OBJECTS_DIR=./lib HEADERS=./src/headers -o Makefile pro.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Isrc/headers -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = lib/

####### Files

SOURCES       = src/sources/BFS.cc \
		src/sources/Bitmap.cc \
		src/sources/BitmapItem.cc \
		src/sources/CSpace.cc \
		src/sources/Data.cc \
		src/sources/GraphicsItem.cc \
		src/sources/main.cc \
		src/sources/PainterWidget.cc \
		src/sources/Parser.cc \
		src/sources/PathItem.cc \
		src/sources/Window.cc moc_View.cpp
OBJECTS       = lib/BFS.o \
		lib/Bitmap.o \
		lib/BitmapItem.o \
		lib/CSpace.o \
		lib/Data.o \
		lib/GraphicsItem.o \
		lib/main.o \
		lib/PainterWidget.o \
		lib/Parser.o \
		lib/PathItem.o \
		lib/Window.o \
		lib/moc_View.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		pro.pro
QMAKE_TARGET  = pro
DESTDIR       = bin/
TARGET        = bin/pro

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) bin/ || $(MKDIR) bin/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: pro.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix QMAKE_CXXFLAGS_WARN_ON= DESTDIR=./bin OBJECTS_DIR=./lib HEADERS=./src/headers -o Makefile pro.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix QMAKE_CXXFLAGS_WARN_ON= DESTDIR=./bin OBJECTS_DIR=./lib HEADERS=./src/headers -o Makefile pro.pro

dist: 
	@$(CHK_DIR_EXISTS) lib/pro1.0.0 || $(MKDIR) lib/pro1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) lib/pro1.0.0/ && $(COPY_FILE) --parents src/headers src/headers/Algorithm.h src/headers/Data.h src/headers/MotionPlan.h src/headers/View.h lib/pro1.0.0/ && $(COPY_FILE) --parents src/sources/BFS.cc src/sources/Bitmap.cc src/sources/BitmapItem.cc src/sources/CSpace.cc src/sources/Data.cc src/sources/GraphicsItem.cc src/sources/main.cc src/sources/PainterWidget.cc src/sources/Parser.cc src/sources/PathItem.cc src/sources/Window.cc lib/pro1.0.0/ && (cd `dirname lib/pro1.0.0` && $(TAR) pro1.0.0.tar pro1.0.0 && $(COMPRESS) pro1.0.0.tar) && $(MOVE) `dirname lib/pro1.0.0`/pro1.0.0.tar.gz . && $(DEL_FILE) -r lib/pro1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_View.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_View.cpp
moc_View.cpp: src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h \
		src/headers/View.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) src/headers/View.h -o moc_View.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

lib/BFS.o: src/sources/BFS.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/BFS.o src/sources/BFS.cc

lib/Bitmap.o: src/sources/Bitmap.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/Bitmap.o src/sources/Bitmap.cc

lib/BitmapItem.o: src/sources/BitmapItem.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/BitmapItem.o src/sources/BitmapItem.cc

lib/CSpace.o: src/sources/CSpace.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/CSpace.o src/sources/CSpace.cc

lib/Data.o: src/sources/Data.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/Data.o src/sources/Data.cc

lib/GraphicsItem.o: src/sources/GraphicsItem.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/GraphicsItem.o src/sources/GraphicsItem.cc

lib/main.o: src/sources/main.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/main.o src/sources/main.cc

lib/PainterWidget.o: src/sources/PainterWidget.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/PainterWidget.o src/sources/PainterWidget.cc

lib/Parser.o: src/sources/Parser.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/Parser.o src/sources/Parser.cc

lib/PathItem.o: src/sources/PathItem.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/PathItem.o src/sources/PathItem.cc

lib/Window.o: src/sources/Window.cc src/headers/MotionPlan.h \
		src/headers/Algorithm.h \
		src/headers/Data.h \
		src/headers/View.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/Window.o src/sources/Window.cc

lib/moc_View.o: moc_View.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lib/moc_View.o moc_View.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:


# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:40 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := WLS
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

#CXX = g++
#CPPFLAGS += -O -Wall -fPIC -I$(ROOTSYS)/include -g
#LD = g++
#LDFLAGS -g
#SOFLAGS -Wl, -soname,libEvent.so -shared
#LIBS = $(ROOTLIBS) -lg++ -lm -ldl -rdynamic
#OOTLIBS      = -L$(ROOTSYS)/lib -lNew -lBase -lCint -lClib -lCont -lFunc -lGraf -lGraf3d -lHist -lHtml -lMatrix -lMeta -lMinuit -lNet -lPostscript -lProof -lTree -lUnix -lZip
#ROOTGLIBS     = -lGpad -lGui -lGX11 -lX3d
#EXTRALIBS += $(ROOTLIBS) $(ROOTGLIBS) -L/usr/X11R6/lib -lXpm -lX11 -lm -ldl

#EXTRALIBS += -L$(ROOTSYS)/lib

#.PHONY: all
#all: lib bin

#include $(G4INSTALL)/config/binmake.gmk


ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)
CPPFLAGS += $(ROOTCFLAGS)
EXTRALIBS += $(ROOTLIBS) $(ROOTGLIBS)
#CPPFLAGS += -O -Wall -fPIC -I$(ROOTSYS)/include -g
#OOTLIBS      = -L$(ROOTSYS)/lib -lNew -lBase -lCint -lClib -lCont -lFunc -lGraf -lGraf3d -lHist -lHtml -lMatrix -lMeta -lMinuit -lNet -lPostscript -lProof -lTree -lUnix -lZip
#ROOTGLIBS     = -lGpad -lGui -lGX11 -lX3d
#EXTRALIBS += $(ROOTLIBS) $(ROOTGLIBS) -L/usr/X11R6/lib -lXpm -lX11 -lm -ldl

#EXTRALIBS += -L$(ROOTSYS)/lib

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

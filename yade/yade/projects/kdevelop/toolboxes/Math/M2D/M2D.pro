# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./toolboxes/Math/M2D
# Target is a library:  

LIBS += -lConstants \
        -lSerialization \
        -rdynamic 
INCLUDEPATH = ../../../yade \
              ../../../toolboxes/Libraries/Serialization \
              ../../../toolboxes/Math/Constants 
MOC_DIR = $(YADECOMPILATIONPATH) 
UI_DIR = $(YADECOMPILATIONPATH) 
OBJECTS_DIR = $(YADECOMPILATIONPATH) 
QMAKE_LIBDIR = ../../../toolboxes/Math/Constants/$(YADEDYNLIBPATH) \
               ../../../toolboxes/Libraries/Serialization/$(YADEDYNLIBPATH) \
               $(YADEDYNLIBPATH) 
DESTDIR = $(YADEDYNLIBPATH) 
CONFIG += release \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += Vector2.hpp \
           Vector2.ipp 
SOURCES += Vector2.cpp 

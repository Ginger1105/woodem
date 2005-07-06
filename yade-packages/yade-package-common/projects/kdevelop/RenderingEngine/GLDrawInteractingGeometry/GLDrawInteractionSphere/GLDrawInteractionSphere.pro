# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./RenderingEngine/GLDrawInteractingGeometry/GLDrawInteractionSphere
# Target is a library:  

LIBS += -lInteractingSphere \
        -lyade-lib-opengl \
        -rdynamic 
INCLUDEPATH += ../../../DataClass/InteractingGeometry/InteractingSphere \
               ../../../RenderingEngine/OpenGLRenderingEngine 
QMAKE_LIBDIR = ../../../../../bin \
               /usr/local/lib/yade/yade-libs/ 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = ../../../../../bin 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
HEADERS += GLDrawInteractionSphere.hpp 
SOURCES += GLDrawInteractionSphere.cpp 

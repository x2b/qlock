HEADERS = src/auth.h            \
          src/AuthCreator.hpp   \
          src/AuthVerifier.hpp  \
          src/AuthWidget.hpp    \
          src/Key.hpp           \
          
SOURCES = src/auth.c            \ 
          src/AuthCreator.cpp   \
          src/AuthVerifier.cpp  \
          src/AuthWidget.cpp    \
          src/Key.cpp           \
          src/main.cpp          \

CONFIG(debug, debug|release) {
   QMAKE_CXXFLAGS   += -O0 -g3 -ggdb
} else {
   DEFINES          += NDEBUG QT_NO_DEBUG_OUTPUT
}

LIBS    += -lgcrypt
CONFIG  += debug_and_release

DESTDIR       = bin
OBJECTS_DIR   = bin/obj
MOC_DIR       = bin/moc
TARGET        = qlock

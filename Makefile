TARGET = psp-sys
OBJS = main.o
 
CFLAGS = 
CXXFLAGS = $(CFLAGS) -std=c++14 -fno-rtti
ASFLAGS = $(CFLAGS)
 
# PSP Stuff
BUILD_PRX = 0
PSP_FW_VERSION = 500
PSP_LARGE_MEMORY = 1
 
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = psp-sys
#PSP_EBOOT_ICON = ICON0.PNG 
LIBS= -lpsppower
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

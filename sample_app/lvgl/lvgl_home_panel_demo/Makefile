BIN = lvgl-home-panel-demo

CFLAGS += -I${SDKTARGETSYSROOT}/usr/include/lvgl  -I${SDKTARGETSYSROOT}/usr/include/lvgl/lv_drivers -DLV_CONF_INCLUDE_SIMPLE
CFLAGS += -I${SDKTARGETSYSROOT}/usr/include/glib-2.0 -I${SDKTARGETSYSROOT}/usr/lib64/glib-2.0/include
LDFLAGS += -llvgl -llv_drivers -lwayland-client -lpthread 

GLIB_CFLAGS :=${shell pkg-config --cflags glib-2.0}
GLIB_LIBS :=${shell pkg-config --libs glib-2.0}

GOBJ_GLIB_CFLAGS :=${shell pkg-config --cflags gobject-2.0}
GOBJ_GLIB_LIBS :=${shell pkg-config --libs gobject-2.0}

CFLAGS += ${GLIB_CFLAGS}
LDFLAGS += ${GLIB_LIBS}

CFLAGS += ${GOBJ_GLIB_CFLAGS}
LDFLAGS += ${GOBJ_GLIB_LIBS}

ifeq ($(MACHINE),smarc-rzg2l)
 CFLAGS += -I${SDKTARGETSYSROOT}/usr/include/gstreamer-1.0
 LDFLAGS += -lgstreamer-1.0
endif

ifeq ($(MACHINE),smarc-rzg2lc)
 CFLAGS += -I${SDKTARGETSYSROOT}/usr/include/gstreamer-1.0
 LDFLAGS += -lgstreamer-1.0
endif

prefix ?= /usr
bindir ?= $(prefix)/bin

SRC_DIR := ./src

MAIN := $(SRC_DIR)/main.c
SRCS := $(shell find $(SRC_DIR) -name '*.c' ! -name 'main.c')

MAINOBJ = $(MAIN:.c=.o)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

.PHONY: all clean

all: default

%.o: %.c
	@$(CC)  $(CFLAGS) -c $< -o $@

default: $(OBJS) $(MAINOBJ)
	$(CC) -o $(BIN) $(MAINOBJ) $(OBJS) $(LDFLAGS)

clean: 
	@echo "Cleaning ... "
	rm -f $(BIN) $(MAINOBJ) $(OBJS)

install:
	install -d $(bindir)
	install $(BIN) $(bindir)



BIN = lvgl_sample_video_playback

CFLAGS += -I${SDKTARGETSYSROOT}/usr/include/lvgl -DLV_CONF_INCLUDE_SIMPLE
CFLAGS += -I${SDKTARGETSYSROOT}/usr/include/gstreamer-1.0 -I${SDKTARGETSYSROOT}/usr/include/glib-2.0 -I${SDKTARGETSYSROOT}/usr/lib64/glib-2.0/include
LDFLAGS += -llvgl -lwayland-client -lgstreamer-1.0 -lglib-2.0 -lgobject-2.0 -lpthread -lxkbcommon -lwayland-cursor

GLIB_CFLAGS :=${shell pkg-config --cflags glib-2.0}
GLIB_LIBS :=${shell pkg-config --libs glib-2.0}
CFLAGS += ${GLIB_CFLAGS}
LDFLAGS += ${GLIB_LIBS}

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


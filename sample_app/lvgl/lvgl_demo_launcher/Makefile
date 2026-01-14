
BIN = demo-launcher

CFLAGS += -I${SDKTARGETSYSROOT}/usr/include/lvgl -DLV_CONF_INCLUDE_SIMPLE
LDFLAGS += -llvgl

ifeq ($(MACHINE),smarc-rzg2l)
 LDFLAGS += -lwayland-client -lxkbcommon -lwayland-cursor
endif

ifeq ($(MACHINE),smarc-rzg2lc)
 LDFLAGS += -lwayland-client -lxkbcommon -lwayland-cursor
endif

ifeq ($(MACHINE),smarc-rzg3e)
 LDFLAGS += -lwayland-client -lxkbcommon -lwayland-cursor
endif

GLIB_CFLAGS :=${shell pkg-config --cflags glib-2.0}
GLIB_LIBS :=${shell pkg-config --libs glib-2.0}

JSON_GLIB_CFLAGS :=${shell pkg-config --cflags json-glib-1.0}
JSON_GLIB_LIBS :=${shell pkg-config --libs json-glib-1.0}

GOBJ_GLIB_CFLAGS :=${shell pkg-config --cflags gobject-2.0}
GOBJ_GLIB_LIBS :=${shell pkg-config --libs gobject-2.0}

CFLAGS += ${GLIB_CFLAGS}
LDFLAGS += ${GLIB_LIBS}

CFLAGS += ${JSON_GLIB_CFLAGS}
LDFLAGS += ${JSON_GLIB_LIBS}

CFLAGS += ${GOBJ_GLIB_CFLAGS}
LDFLAGS += ${GOBJ_GLIB_LIBS}

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
	cp $(PWD)/config/lvgl_launcher_$(MACHINE).json $(PWD)/demo-launcher.json
clean: 
	@echo "Cleaning ... "
	rm -f $(BIN) $(MAINOBJ) $(OBJS)
	rm -f $(PWD)/demo-launcher.json
install:
	install -d $(bindir)
	install $(BIN) $(bindir)



BIN = lvgl_sample_img_disp

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


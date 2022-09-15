OBJDIR = ../lib
BUILDDIR = ../bin

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CSRC = $(call rwildcard,./,*.c)

OBJS = $(patsubst %.c, $(OBJDIR)/%_$(OUTPUT).o, $(CSRC))


CFLAGS = -Iinclude
LDFLAGS = -r

CFLAGS += $(USER_CFLAGS)
LDFLAGS += $(USER_LDFLAGS)

CC = gcc
LD = ld
AR = ar

$(OUTPUT): $(OBJS)
	@echo LD $^
	@$(LD) $(LDFLAGS) -o $(BUILDDIR)/$@.o $^
	@echo AR $(BUILDDIR)/$@.o
	@$(AR) rcs $(BUILDDIR)/$@ $(BUILDDIR)/$@.o
	@echo Succesfully build library $(OUTPUT)

$(OBJDIR)/%_$(OUTPUT).o: %.c
	@echo "CC $^ -> $@"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: build
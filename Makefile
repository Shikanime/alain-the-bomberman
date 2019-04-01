#
# Fluid
# Version: 1.5.7
#
# Use of this source code is governed by an MIT-style license that can be
# found in the LICENSE file at LICENSE
#

#
# CONFIGURATIONS
#

OUTNAME := bomberman

ASSETDIR := assets
ROOTDIR := .
DEPDIR := .cache
OBJDIR := .cache
OUTDIR := build
SRCDIR := src
HDRDIR := src

#
# DO NOT EDIT FORWARD
#

# Compilation settings

CC := gcc
TYPE := c

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
			-Wwrite-strings -Wmissing-declarations -Wredundant-decls \
			-Winline -Wno-long-long -Wuninitialized -Wconversion -Wfatal-errors \
			-fsanitize=address

CFLAGS ?= -std=c11 $(WARNINGS)

# Options

ifeq ($(VERBOSE), 1)
    SILENCER :=
else
    SILENCER := @
endif

# Compilation command

.PHONY: all
all: init exec

.PHONY: exec
exec: $(OUTNAME)
	$(SILENCER)cp -r $(ROOTDIR)/$(ASSETDIR) $(ROOTDIR)/$(OUTDIR)

# Automated compilator

# Compilator files

SRCS := $(shell find $(ROOTDIR)/$(SRCDIR) -name "*.$(TYPE)" -type f | cut -sd / -f 3- | tr '\n' ' ')
OBJS := $(patsubst %, $(OBJDIR)/%, $(SRCS:$(TYPE)=o))
DEPS :=$(patsubst %.$(TYPE), %.d, $(SRCS))

# Compilation output configurations

CFLAGS += -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

$(OUTNAME): $(OBJS)
	$(SILENCER)$(CC) $(CFLAGS) -o $(OUTDIR)/$(OUTNAME) $^ -lSDL2 `sdl2-config --cflags --libs` -lSDL2_image  -lSDL2_ttf

$(OBJDIR)/%.o: $(SRCDIR)/%.$(TYPE) $(DEPDIR)/%.d
	$(SILENCER)mkdir -p $(shell dirname $@)
	$(SILENCER)$(CC) $(CFLAGS) -c -o $@ $<
	$(POSTCOMPILE)

# Helpers command

.PHONY: init
init:
	$(SILENCER)mkdir -p $(ROOTDIR)/$(SRCDIR)
	$(SILENCER)mkdir -p $(ROOTDIR)/$(OBJDIR)
	$(SILENCER)mkdir -p $(ROOTDIR)/$(HDRDIR)
	$(SILENCER)mkdir -p $(ROOTDIR)/$(OUTDIR)

.PHONY: clean
clean:
	$(SILENCER)$(RM) -r $(ROOTDIR)/$(OBJDIR)
	$(SILENCER)mkdir -p $(ROOTDIR)/$(OBJDIR)

.PHONY: fclean
fclean: clean
	$(SILENCER)$(RM) -r $(ROOTDIR)/$(OUTDIR)
	$(SILENCER)mkdir -p $(ROOTDIR)/$(OUTDIR)

.PHONY: re
re: fclean all

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))

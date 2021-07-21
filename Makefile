CC :=gcc
INCLUDE :=include
CFLAGS :=-c -I$(INCLUDE)
TARGET :=rtmodx64
VERSION :=1.0
SRC :=$(filter-out test%, $(wildcard *.c */*.c))
OBJS :=$(patsubst %.c,%.o,$(SRC))

INSTALLDIR := /bin
.PHONY: build build-objects clean very-clean install uninstall

define init-uninstall
echo Uninstalling $(TARGET); \
sudo rm $(INSTALLDIR)/$(TARGET); \
echo $(TARGET) uninstalled successfully
endef


build: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

build-objects: $(OBJS)

$(TARGET): $(SRC)
	$(MAKE) build-objects
	$(CC) $(OBJS) -o $@

change-version:
	sed -i 's/^Version=.*/Version=$(VERSION)/' resources/version-msg.txt 

clean:
	rm -rf *.o *.rm

very-clean: clean
	rm -rf $(TARGET)

install: $(TARGET)
	@echo Installing $(TARGET)
	@sudo cp $(TARGET) $(INSTALLDIR)/$(TARGET) 
	@echo $(TARGET) installation complete..

uninstall:
	@cd $(INSTALLDIR) && if [ -f $(TARGET) ] ; then $(init-uninstall) ; else echo "$(TARGET) already uninstalled" ; fi

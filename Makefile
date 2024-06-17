#Esta implementacion permite usar el mismo archivo Makefile tanto
#En Windows como en sistemas basados en Unix como Linux y Mac OS X

ifdef OS  #Deteccion de Windows 
	CC := g++.exe
	FLAGS := -lwinmm icono.res
	RM := del /Q
	COPY := copy
	FixPath = $(subst /,\,$1)
	InstallPath := C:\Program Files\Klotski\
	UNAME := Windows
	EXT := .exe
else  	  #*NIX usando GNU make
	CC := g++
	FLAGS := -lncurses -s
	RM := rm -f 
	COPY := cp
	FixPath = $1
	InstallPath := /usr/local/bin/
	UNAME = $(shell uname)
	EXT :=
endif

CFLAGS := -Ofast -w -std=c++17  #optimizacion maxima 
LaunchScript := launch_klotski.sh
Nombre := Klotski-$(UNAME)

all: $(Nombre) desktop

$(Nombre): main.cpp Klotski.cpp Tabla.cpp Bloque.cpp Nivel.cpp TiposDeDatos.h FuncionesAuxiliares.h
	$(CC) -o $(call FixPath,$(Nombre)) $< $(FLAGS) $(CFLAGS)

install: $(Nombre)
ifdef OS
	mkdir "$(InstallPath)"
endif
	$(COPY) $(call FixPath,$(Nombre)$(EXT)) "$(InstallPath)"

uninstall:
	$(RM) "$(InstallPath)$(Nombre)$(EXT)"
ifdef OS
	rmdir /s /q "$(InstallPath)"
endif


$(LaunchScript): $(Nombre)
ifeq ($(UNAME), Linux)
	@echo "#!/usr/bin/env sh" > $(LaunchScript)
	@echo "cd \"$(shell pwd)\"" >> $(LaunchScript)
	@echo "./$(Nombre)" >> $(LaunchScript)
	@chmod +x $(LaunchScript)
endif

desktop: $(Nombre) $(LaunchScript)
ifeq ($(UNAME), Linux)
	@echo "[Desktop Entry]" > Klotski.desktop
	@echo "Version=1.0" >> Klotski.desktop
	@echo "Name=Klotski" >> Klotski.desktop
	@echo "Comment=Solucionador de Klotski" >> Klotski.desktop
	@echo "Exec=$(shell pwd)/$(LaunchScript)" >> Klotski.desktop
	@echo "Icon=$(shell pwd)/icono.ico" >> Klotski.desktop
	@echo "Terminal=true" >> Klotski.desktop
	@echo "Type=Application" >> Klotski.desktop
	@echo "Categories=Game;" >> Klotski.desktop
	@chmod +x Klotski.desktop
endif

clean:
	$(RM) $(call FixPath,$(Nombre)$(EXT)) 
ifeq ($(UNAME), Linux)
	$(RM) $(LaunchScript)
	$(RM) Klotski.desktop
endif

.PHONY: all clean install uninstall
#Esta implementacion permite usar el mismo archivo Makefile tanto
#En Windows como en sistemas basados en Unix como Linux y Mac OS X

ifdef OS  #Deteccion de Windows 
	CC := g++.exe
	FLAGS := -lwinmm Klotski-icono.res
	FixPath = $(subst /,\,$1)
	InstallPath := C:\/Users\/$(USERNAME)\/Desktop\/
	UNAME := Windows
	EXT := .exe
else  	  #*NIX usando GNU make
	CC := g++
	FLAGS := -lncurses -s
	FixPath = $1
	InstallPath := /usr/local/bin/
	IconoPath   := /usr/share/icons/
	DesktopPath := /home/$(USER)/Desktop/
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
	cp $(call FixPath,$(Nombre)$(EXT)) "$(call FixPath,$(InstallPath))"
ifeq ($(UNAME), Linux)
	cp $(LaunchScript) $(InstallPath)
	cp Klotski-icono.ico $(IconoPath)
endif

uninstall:
	rm -f  "$(call FixPath,$(InstallPath))$(Nombre)$(EXT)"
ifeq ($(UNAME), Linux)
	rm -f $(InstallPath)$(LaunchScript)
	rm -f $(IconoPath)Klotski-icono.ico
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
	@echo "[Desktop Entry]" > $(Nombre).desktop
	@echo "Version=1.0" >> $(Nombre).desktop
	@echo "Name=$(Nombre)" >> $(Nombre).desktop
	@echo "Comment=Solucionador de Klotski" >> $(Nombre).desktop
	@echo "Exec=$(InstallPath)$(LaunchScript)" >> $(Nombre).desktop
	@echo "Icon=$(IconoPath)Klotski-icono.ico" >> $(Nombre).desktop
	@echo "Terminal=true" >> $(Nombre).desktop
	@echo "Type=Application" >> $(Nombre).desktop
	@echo "Categories=Game;" >> $(Nombre).desktop
	@chmod +x $(Nombre).desktop
	@mv $(Nombre).desktop $(DesktopPath)
endif

clean:
	rm -f  $(call FixPath,$(Nombre)$(EXT)) 
ifeq ($(UNAME), Linux)
	rm -f  $(InstallPath)$(LaunchScript)
	rm -f  $(InstallPath)$(LaunchScript)
	rm -f  $(DesktopPath)$(Nombre).desktop
endif

.PHONY: all clean install uninstall
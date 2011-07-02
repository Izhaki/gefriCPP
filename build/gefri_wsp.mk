.PHONY: clean All

All:
	@echo ----------Building project:[ gxDraw - Win32 Debug ]----------
	@cd "..\samples\gxDraw" && "mingw32-make.exe"  -j 1 -f "gxDraw.mk"
clean:
	@echo ----------Cleaning project:[ gxDraw - Win32 Debug ]----------
	@cd "..\samples\gxDraw" && "mingw32-make.exe"  -j 1 -f "gxDraw.mk" clean

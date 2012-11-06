.PHONY: clean All

All:
	@echo ----------Building project:[ gxDraw - Mac32 Debug ]----------
	@cd "/Volumes/Blackstore/Development/gefri/samples/gxDraw" && "$(MAKE)" -w -f "gxDraw.mk" PrePreBuild && "$(MAKE)" -w -f "gxDraw.mk"
clean:
	@echo ----------Cleaning project:[ gxDraw - Mac32 Debug ]----------
	@cd "/Volumes/Blackstore/Development/gefri/samples/gxDraw" && "$(MAKE)" -w -f "gxDraw.mk" clean

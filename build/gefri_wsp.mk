.PHONY: clean All

All:
	@echo ----------Building project:[ gxDraw - Linux32 Release ]----------
	@cd "../samples/gxDraw" && "$(MAKE)" -f "gxDraw.mk"
clean:
	@echo ----------Cleaning project:[ gxDraw - Linux32 Release ]----------
	@cd "../samples/gxDraw" && "$(MAKE)" -f "gxDraw.mk" clean

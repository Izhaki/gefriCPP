.PHONY: clean All

All:
	@echo ----------Building project:[ gefri - Mac32 Debug ]----------
	@cd "gefri" && "$(MAKE)" -w -f "gefri.mk"
clean:
	@echo ----------Cleaning project:[ gefri - Mac32 Debug ]----------
	@cd "gefri" && "$(MAKE)" -w -f "gefri.mk" clean

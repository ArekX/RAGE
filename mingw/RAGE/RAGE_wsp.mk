.PHONY: clean All

All:
	@echo "----------Building project:[ RAGE - Debug ]----------"
	@$(MAKE) -f  "RAGE.mk"
clean:
	@echo "----------Cleaning project:[ RAGE - Debug ]----------"
	@$(MAKE) -f  "RAGE.mk" clean

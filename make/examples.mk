EXAMPLES_DIR = $(KINAI_PATH)/examples

EXAMPLES = $(filter-out examples/assets,$(wildcard examples/*))

define __make_example_rule =
.PHONY: examples/$(1)
examples/$(1):
	@echo "$(COLOR_GREY)Compiling $(1)...$(COLOR_DEFAULT)"
	$(SILENT)$(CXX) $(CXXFLAGS) -o $(1)$(EXE) $(INCLUDE) $(wildcard $(EXAMPLES_DIR)/$(1)/*.cpp) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(1)$(EXE)) $(COLOR_DEFAULT)"

.PHONY: examples/$(1)/
examples/$(1)/:
	@echo "$(COLOR_GREY)Compiling $(1)...$(COLOR_DEFAULT)"
	$(SILENT)$(CXX) $(CXXFLAGS) -o $(1)$(EXE) $(INCLUDE) $(wildcard $(EXAMPLES_DIR)/$(1)/*.cpp) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(1)$(EXE)) $(COLOR_DEFAULT)"

.PHONY: $(1)
$(1):
	@echo "$(COLOR_GREY)Compiling $(1)...$(COLOR_DEFAULT)"
	$(SILENT)$(CXX) $(CXXFLAGS) -o $(1)$(EXE) $(INCLUDE) $(wildcard $(EXAMPLES_DIR)/$(1)/*.cpp) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(1)$(EXE)) $(COLOR_DEFAULT)"

endef

.PHONY: examples
examples: $(foreach example,$(EXAMPLES),$(notdir $(example)))

$(eval $(foreach example,$(EXAMPLES),$(call __make_example_rule,$(notdir $(example)))))

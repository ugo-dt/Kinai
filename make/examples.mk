EXAMPLES_DIR = $(KINAI_PATH)/examples

EXAMPLES = $(wildcard examples/*)

define __make_example_rule = 
$(1):
	@echo "$(COLOR_GREY)Compiling $(1)...$(COLOR_DEFAULT)"
	$(SILENT)$(CXX) $(CXXFLAGS) -o $(1)$(EXE) $(INCLUDE) $(wildcard $(EXAMPLES_DIR)/$(1)/*.cpp) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(1)$(EXE)) $(COLOR_DEFAULT)"

endef

all_examples: $(foreach example,$(EXAMPLES),$(notdir $(example)))

$(eval $(foreach example,$(EXAMPLES),$(call __make_example_rule,$(notdir $(example)))))

KINAI_PATH = ..
backend = Headless
target = web
verbose = 1
include $(KINAI_PATH)/Makefile

EXAMPLES_DIR = $(KINAI_PATH)/examples
EXAMPLES = $(filter-out $(EXAMPLES_DIR)/assets,$(wildcard $(EXAMPLES_DIR)/*))

INCLUDE += -I $(KINAI_PATH)/examples/assets

define __make_example_rule =
.PHONY: $(EXAMPLES_DIR)/$(1)
$(EXAMPLES_DIR)/$(EXAMPLES_DIR)/$(1):
	@echo "$(COLOR_GREY)Compiling $(1)...$(COLOR_DEFAULT)"
	$(SILENT)$(CXX) $(CXXFLAGS) -o $(1)$(EXE) $(INCLUDE) $(wildcard $(EXAMPLES_DIR)/$(1)/*.cpp) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(1)$(EXE)) $(COLOR_DEFAULT)"

.PHONY: $(EXAMPLES_DIR)/$(1)/
$(EXAMPLES_DIR)/$(1)/:
	@echo "$(COLOR_GREY)Compiling $(1)...$(COLOR_DEFAULT)"
	$(SILENT)$(CXX) $(CXXFLAGS) -o $(1)$(EXE) $(INCLUDE) $(wildcard $(EXAMPLES_DIR)/$(1)/*.cpp) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(1)$(EXE)) $(COLOR_DEFAULT)"

.PHONY: $(1)
$(1):
	@echo "$(COLOR_GREY)Compiling $(1)...$(COLOR_DEFAULT)"
	$(SILENT)$(CXX) $(CXXFLAGS) -o $(1)$(EXE) $(INCLUDE) $(wildcard $(EXAMPLES_DIR)/$(1)/*.cpp) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(1)$(EXE)) $(COLOR_DEFAULT)"

.PHONY: $(1)/
$(1)/:
	@echo "$(COLOR_GREY)Compiling $(1)...$(COLOR_DEFAULT)"
	$(SILENT)$(CXX) $(CXXFLAGS) -o $(1)$(EXE) $(INCLUDE) $(wildcard $(EXAMPLES_DIR)/$(1)/*.cpp) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built $(notdir $(1)$(EXE)) $(COLOR_DEFAULT)"

endef

.PHONY: examples
examples: $(foreach example,$(EXAMPLES),$(notdir $(example)))
	for ex in $(foreach example,$(EXAMPLES),$(notdir $(example))) ; do \
		$(MAKE) example 1=$$ex ; \
	done

$(eval $(foreach example,$(EXAMPLES),$(call __make_example_rule,$(notdir $(example)))))

.PHONY: $(foreach example,$(EXAMPLES),$(notdir $(example)))
example:
	$(SILENT)mkdir -p $(EXAMPLES_DIR)/bin
	@echo "$(COLOR_GREY)Compiling $(1)...$(COLOR_DEFAULT)"
	$(SILENT)$(CXX) $(CXXFLAGS) -o bin/$(1)$(EXE) $(INCLUDE) $(wildcard $(EXAMPLES_DIR)/$(1)/*.cpp) $(KINAI) $(LDFLAGS)
	@echo "$(COLOR_GREEN)Successfully built bin/$(notdir $(1)$(EXE)) $(COLOR_DEFAULT)"

hello_kinai:
	$(SILENT)$(MAKE) example 1=hello_kinai

kinai_cube:
	$(SILENT)$(MAKE) example 1=kinai_cube

kinai_events:
	$(SILENT)$(MAKE) example 1=kinai_events

kinai_2d:
	$(SILENT)$(MAKE) example 1=kinai_2d

kinai_sokol:
	$(SILENT)$(MAKE) example 1=kinai_sokol

kinai_sokol_gp:
	$(SILENT)$(MAKE) example 1=kinai_sokol_gp

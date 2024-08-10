CXX := clang++
CPPFLAGS := -std=c++20 -I.

ifeq ($(DEBUG),1)
	CPPFLAGS += -g -Wall
else
	CPPFLAGS += -O
endif

IGNORE_DIRECTORIES = .vscode .git build
ALL_DIERCTORIES = $(wildcard */)

MODULES = $(filter-out $(IGNORE_DIRECTORIES),$(ALL_DIERCTORIES))
CPPFILES = $(foreach MODULE,$(MODULES),$(wildcard $(MODULE)*.cpp))
OBJECTS = $(CPPFILES:.cpp=.o)

clean:
	@rm -rf build/obj
	@rm build/$(TARGET)

stage:
	@$(foreach MODULE,$(MODULES),mkdir -p build/obj/$(MODULE);)

%.o: %.cpp
	@echo =\> Compiling $<...
	@$(CXX) -c $< -o build/obj/$@ $(CPPFLAGS)

target: stage $(OBJECTS)
	@echo =\> Linking $(TARGET)...
	@$(CXX) $(addprefix build/obj/,$(OBJECTS)) -o build/$(TARGET) $(CPPFLAGS)

run:
	@echo =\> Running $(TARGET)...
	@./build/$(TARGET) $(RUN_COMMAND)

do: target run
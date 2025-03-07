COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

CXXFLAGS = $(shell cat compile_flags.txt)
LDFLAGS = $(shell cat link_flags.txt)

objects = fmt/src/format.o $(patsubst src/%.cc,src/%.o,$(shell find src -name "*.cc" ! -path "src/bin/*"))
binaries = $(basename $(wildcard src/bin/*.cc))

.PHONY: all
all: $(binaries)

src/bin/%: src/bin/%.o $(objects)
	$(LINK.cc) $^ -o $@ $(LDLIBS) 

src/%.o: src/%.cc
	$(COMPILE.cc) -MMD -MP -MT $@ -MF $(@:.o=.d) -o $@ $<

fmt/src/%.o: fmt/src/%.cc
	$(COMPILE.cc) -o $@ $<

.PHONY: clean
clean:
	@find src fmt/src -type f  \( -name "*.o" -o -name "*.d" -o ! -name "*.*" \) -exec echo rm -f {} +
	@find src/bin -type f ! -name "*.*" -delete
	@find src fmt/src \( -name "*.o" -o -name "*.d" \) -delete

.PHONY: format
format:
	@find src \( -name "*.cc" -o -name "*.hh" \) -exec echo clang-format -i {} +
	@find src \( -name "*.cc" -o -name "*.hh" \) -exec clang-format -i {} +

include $(shell find src -name "*.d")

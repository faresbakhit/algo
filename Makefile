COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

CXXFLAGS = @compile_flags.txt
LDFLAGS = @link_flags.txt

objects = $(patsubst %.cc,%.o,$(wildcard src/*.cc)) fmt/src/format.o
binaries = $(basename $(wildcard src/bin/*.cc))

.PHONY: all
all: $(binaries)

src/bin/%: src/bin/%.o $(objects)
	$(LINK.cc) $^ $(LDLIBS) -o $@

src/bin/%.o: src/bin/%.cc
	$(COMPILE.cc) -MMD -MP -MT $@ -MF src/bin/$*.d -o $@ $<

src/%.o: src/%.cc
	$(COMPILE.cc) -MMD -MP -MT $@ -MF src/$*.d -o $@ $<

fmt/src/%.o: fmt/src/%.cc
	$(COMPILE.cc) -o $@ $<

.PHONY: clean
clean:
	rm -f src/*.d src/*.o src/bin/*.d src/bin/*.o fmt/src/*.o $(binaries)

include $(wildcard src/*.d)
include $(wildcard src/bin/*.d)

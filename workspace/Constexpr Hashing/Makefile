.PHONY = all clean

RUNTIME_EXECUTABLE     = runtime.exe
COMPILETIME_EXECUTABLE = compile_time.exe

CXX      = g++
CXXFLAGS = -Os -std=c++17 -pedantic-errors

ODMP      = objdump
#ODMPSECTION = -j .rodata
#ODMPSECTION = -j .rdata
ODMPSECTION = -j .data
ODMPFLAGS = -s $(ODMPSECTION)

STRS = strings
GREP = grep

PASS = MySuperSecurePassword
HASH = 06196032580217052bad1df90ddd482deeb3387c851fee7af706a314aaf60f6d

all: objdump search_pass search_hash;

clean:
	@rm -f compile_time
	@rm -f runtime



objdump: compile_time runtime
	@echo "Dumping data sections of '$(COMPILETIME_EXECUTABLE)'"
	@echo "=============================================================================="
	@$(ODMP) $(ODMPFLAGS) $(COMPILETIME_EXECUTABLE)
	@echo "=============================================================================="
	@echo
	@echo "Dumping data sections of '$(RUNTIME_EXECUTABLE)'"
	@echo "=============================================================================="
	@$(ODMP) $(ODMPFLAGS) $(RUNTIME_EXECUTABLE)
	@echo "=============================================================================="
	@echo

search_pass: compile_time runtime
	@echo "Searching for password in '$(COMPILETIME_EXECUTABLE)'"
	@echo "=============================================================================="
	@$(STRS) $(COMPILETIME_EXECUTABLE) | $(GREP) $(PASS) || echo "Password not found"
	@echo "=============================================================================="
	@echo
	@echo "Searching for password in '$(RUNTIME_EXECUTABLE)'"
	@echo "=============================================================================="
	@$(STRS) $(RUNTIME_EXECUTABLE) | $(GREP) $(PASS) || echo "Password not found"
	@echo "=============================================================================="
	@echo

search_hash: compile_time runtime
	@echo "Searching for hash in '$(COMPILETIME_EXECUTABLE)'"
	@echo "=============================================================================="
	@echo -n "searching for hash in 'compile_time'... "
	@$(STRS) $(COMPILETIME_EXECUTABLE) | $(GREP) $(HASH) || echo "Hash not found"
	@echo "=============================================================================="
	@echo
	@echo "Searching for hash in '$(RUNTIME_EXECUTABLE)'"
	@echo "=============================================================================="
	@$(STRS) $(RUNTIME_EXECUTABLE) | $(GREP) $(HASH) || echo "Hash not found"
	@echo "=============================================================================="
	@echo

%: %.cpp
	@echo CXX $^
	@$(CXX) $^ $(CXXFLAGS) $(OUTPUT_OPTION)

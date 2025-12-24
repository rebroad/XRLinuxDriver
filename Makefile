.PHONY: all build clean install help
.DEFAULT_GOAL := help

BUILD_DIR := build
BIN_DIR := bin

# Detect if build directory exists and has CMake cache
CMAKE_CACHE := $(BUILD_DIR)/CMakeCache.txt

help: ## Show this help message
	@echo "Available targets:"
	@echo "  make build    - Build the project (creates build/ directory)"
	@echo "  make install  - Install the built driver (requires build to be done first)"
	@echo "  make clean    - Remove build directory"
	@echo "  make help     - Show this help message"

build: $(CMAKE_CACHE) ## Build the project
	cd $(BUILD_DIR) && cmake --build . --parallel $(shell nproc)
	@echo "Build complete. Binary is in $(BUILD_DIR)/xrDriver"

$(CMAKE_CACHE):
	@echo "Configuring CMake..."
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

install: build ## Install the driver
	@if [ ! -f $(BUILD_DIR)/xrDriver ]; then \
		echo "Error: Binary not found. Run 'make build' first."; \
		exit 1; \
	fi
	@echo "Copying binary to $(BIN_DIR)/..."
	cp $(BUILD_DIR)/xrDriver $(BIN_DIR)/xrDriver
	@echo "Running install script..."
	./$(BIN_DIR)/user/install

clean: ## Remove build directory
	rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory"


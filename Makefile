.PHONY: build conan clean

BUILD_TYPE ?= Debug

conan:
	@mkdir -p build && cd build && conan install ../ -s build_type=$(BUILD_TYPE) -s compiler.libcxx=libstdc++11 --build=missing

build: conan
	@cd build && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCODE_COVERAGE=ON -j 4 ..

clean:
	@rm -rf build

test: build
	@cd build && make tests CMAKE_BUILD_TYPE=$(BUILD_TYPE) test CTEST_OUTPUT_ON_FAILURE=TRUE

coverage: clean test
	@lcov --capture --directory . --output-file coverage.info
	@lcov --remove coverage.info '*/usr/*' '*/_deps/*' --output-file coverage.info > /dev/null
	@lcov --list coverage.info

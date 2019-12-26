.PHONY: build conan clean

BUILD_TYPE ?= Debug
COMPILER ?= libc++
CODECOV ?= OFF

conan:
	@mkdir -p build && cd build && conan install ../ -s build_type=$(BUILD_TYPE) -s compiler.libcxx=$(COMPILER) --build=missing

build: conan
	@cd build && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCODE_COVERAGE=$(CODECOV) -j 4 ..

clean:
	@rm -rf build

test: build
	@cd build && make tests libtests CMAKE_BUILD_TYPE=$(BUILD_TYPE) test CTEST_OUTPUT_ON_FAILURE=TRUE

coverage: test
	@cd build && lcov --capture --directory . --output-file codecov.info
	@cd build && lcov --remove codecov.info '*/usr/*' '*/.conan/*' '*/test/*' --output-file codecov.info > /dev/null
	@cd build && lcov --list codecov.info

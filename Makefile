.PHONY: build conan clean docker_test

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

docker_test:
	@docker build -t dfiler_test -f test_data/Dockerfile .
	@docker run --rm -e CODECOV=ON -e COMPILER=libstdc++11 -v /tmp/.conan/:/home/conan/ dfiler_test /bin/bash -c "make coverage"

coverage: test
	@cd build && make codecov CMAKE_BUILD_TYPE=$(BUILD_TYPE)

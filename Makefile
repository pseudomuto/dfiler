.PHONY: build cmake clean docker_test conan

BUILD_TYPE ?= Debug
CODECOV ?= OFF
IWYU ?= ON

conan:
	@conan remote add cxxopts https://api.bintray.com/conan/lordobsidian01/LordObsidian01 -f

cmake: conan
	@echo $(IWYU)
	@mkdir -p build && cd build && cmake -DIWYU=$(IWYU) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCODE_COVERAGE=$(CODECOV) -j 4 ..

build:
	@cd build && make dfiler

run: build
	@build/bin/dfiler $(ARGS)

clean:
	@rm -rf build

test:
	@cd build && make libtests CMAKE_BUILD_TYPE=$(BUILD_TYPE) test CTEST_OUTPUT_ON_FAILURE=TRUE

docker_test:
	@docker build -t dfiler_test -f test_data/Dockerfile .
	@docker run --rm -v /tmp/.conan/:/home/conan/.conan/ dfiler_test

coverage: test
	@cd build && make codecov CMAKE_BUILD_TYPE=$(BUILD_TYPE)

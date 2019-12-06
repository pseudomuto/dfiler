.PHONY: build clean

build:
	@mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Debug -j 4 ..

clean:
	@rm -rf build

test: build
	@cd build && make tests test CTEST_OUTPUT_ON_FAILURE=TRUE

coverage: clean
	@mkdir -p build
	@cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DCODE_COVERAGE=ON -j 4 ..
	@cd build && make tests test CTEST_OUTPUT_ON_FAILURE=TRUE
	@lcov --capture --directory . --output-file coverage.info
	@lcov --remove coverage.info '*/usr/*' '*/_deps/*' --output-file coverage.info > /dev/null
	@lcov --list coverage.info
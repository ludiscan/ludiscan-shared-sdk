build:
	rm -rf build
	mkdir build
	cd build && cmake ..
	cd build && make
	mkdir -p dist
	cp build/libSDK.* dist
	cp include/**/*.h dist
	rm -rf build

setup-linux:
	sudo apt-get update
	sudo apt-get install libcurl4-openssl-dev

setup-mac:
	brew install curl

setup-windows:
	git clone https://github.com/microsoft/vcpkg.git
	cd vcpkg
	./bootstrap-vcpkg.bat
	./vcpkg integrate install
	./vcpkg install curl

generate-cpp-client:
	openapi-generator-cli generate -i http://localhost:3000/api-json -g cpp-restsdk -o ./build/cpp-client
	mkdir -p ./src/CppRestOpenAPIClient
	cp -r ./build/cpp-client/src/* ./src/CppRestOpenAPIClient
	mkdir -p ./include/CppRestOpenAPIClient
	cp -r ./build/cpp-client/include/* ./include
	cp ./build/cpp-client/Config.cmake.in ./


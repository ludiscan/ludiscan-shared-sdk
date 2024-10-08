build:
	mkdir -p build
	cd build && cmake ..
	cd build && make

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
	openapi-generator-cli generate -i http://localhost:3000/api-json -g cpp-restsdk -o ./dist/cpp-client
	mkdir -p ./src/CppRestOpenAPIClient
	cp -r ./dist/cpp-client/src/* ./src/CppRestOpenAPIClient
	mkdir -p ./include/CppRestOpenAPIClient
	cp -r ./dist/cpp-client/include/* ./include
	cp ./dist/cpp-client/Config.cmake.in ./


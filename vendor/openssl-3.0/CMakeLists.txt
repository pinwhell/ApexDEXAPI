add_library(openssl INTERFACE)

set(ARCH x86)

if(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
	set(ARCH x86)
else()
	set(ARCH x64)
endif()

target_include_directories(openssl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/${ARCH}/include)
target_link_libraries(openssl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/${ARCH}/lib/libcrypto.lib ${CMAKE_CURRENT_SOURCE_DIR}/${ARCH}/lib/libssl.lib)
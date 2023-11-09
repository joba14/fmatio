
macro(get_subdirectories_list RESULT CURRENT_DIRECTORY)
	file(GLOB TESTS RELATIVE ${CURRENT_DIRECTORY} ${CURRENT_DIRECTORY}/*)
	set(DIRECTORIES_LIST "")

	foreach(TEST ${TESTS})
		if(IS_DIRECTORY ${CURRENT_DIRECTORY}/${TEST})
			list(APPEND DIRECTORIES_LIST ${TEST})
		endif()
	endforeach()

	set(${RESULT} ${DIRECTORIES_LIST})
endmacro()

get_subdirectories_list(SUBDIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

foreach(SUBDIRECTORY ${SUBDIRECTORIES})
	add_subdirectory(${SUBDIRECTORY})
endforeach()

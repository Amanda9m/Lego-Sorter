
include(CheckIncludeFiles)
include(CheckSymbolExists)

check_include_files("unistd.h;signal.h" HAVE_HEADERS)

# Check for all required functions
check_symbol_exists(usleep  "stdio.h;stdlib.h;string.h;unistd.h;signal.h" HAVE_USLEEP)
check_symbol_exists(popen   "stdio.h;stdlib.h;string.h;unistd.h;signal.h" HAVE_POPEN)
check_symbol_exists(pclose  "stdio.h;stdlib.h;string.h;unistd.h;signal.h" HAVE_PCLOSE)
check_symbol_exists(kill    "stdio.h;stdlib.h;string.h;unistd.h;signal.h" HAVE_KILL)
check_symbol_exists(mkdtemp "stdio.h;stdlib.h;string.h;unistd.h;signal.h" HAVE_MKDTEMP)

if (HAVE_HEADERS
	AND HAVE_USLEEP
	AND HAVE_POPEN
	AND HAVE_PCLOSE
	AND HAVE_KILL
	AND HAVE_MKDTEMP)
	
	add_library(camera STATIC camera.c)

	target_include_directories(camera PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)
endif()

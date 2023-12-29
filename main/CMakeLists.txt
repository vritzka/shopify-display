file(GLOB_RECURSE SRC_UI ${CMAKE_SOURCE_DIR} "ui/*.c" "ui/images/*.c")

idf_component_register(SRCS "main.c"
"gui.c"
"general.c"
"api_request_task.c"
${SRC_UI}
                    
INCLUDE_DIRS "." "ui")

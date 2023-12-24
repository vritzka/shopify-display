SET(SOURCES screens/ui_Screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c)

add_library(ui ${SOURCES})


file(GLOB_RECURSE SRC_UI ${CMAKE_SOURCE_DIR} "ui/*.c" "ui/images/*.c")

idf_component_register(SRCS
"main.c"
"lvgl_demo.c"
${SRC_UI}

INCLUDE_DIRS "." "ui")




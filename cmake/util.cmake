# 添加一个函数来计算文件的相对路径
function(define_file_macro_for_sources target)
    get_target_property(srcs ${target} SOURCES)
    foreach(src ${srcs})
        get_filename_component(src_abs ${src} ABSOLUTE)
        file(RELATIVE_PATH src_rel "${CMAKE_SOURCE_DIR}" "${src_abs}")
        set_property(
                SOURCE ${src}
                PROPERTY COMPILE_DEFINITIONS __FILE__="${src_rel}"
        )
    endforeach()
endfunction()
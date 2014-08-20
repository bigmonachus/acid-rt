function(ph_link_ovr target)
    set_target_properties(${target} PROPERTIES COMPILE_DEFINITIONS "PH_OVR=1")
    target_link_libraries(${target} ${nuwen_runtime} ovr)
    if (UNIX)
        set_property(TARGET ${target} PROPERTY LINK_FLAGS "-lXrandr -ludev")
    endif()
endfunction()
add_library(null0_api src/main.c src/sfx_gen.c)

if (NULL0_HOST_TYPE_RAYLIB)
  target_link_libraries(null0_api raylib pntr pntr_app physfs-static)
endif()

if (NULL0_HOST_TYPE_SDL)
  target_link_libraries(null0_api ${SDL2_LIBRARIES} pntr pntr_app physfs-static)
endif()

if (NULL0_HOST_TYPE_WEB)
  target_link_libraries(null0_api pntr pntr_app physfs-static)
endif()
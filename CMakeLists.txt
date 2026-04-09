cmake_minimum_required(VERSION 3.20)

project(wall
    VERSION 0.1.0
    DESCRIPTION "Public real-time wall powered by Vix.cpp"
    LANGUAGES CXX
)

option(WALL_BUILD_TESTS "Build wall tests" OFF)
option(WALL_BUILD_EXAMPLES "Build wall examples" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(vix QUIET CONFIG)
if (NOT vix_FOUND)
    find_package(Vix CONFIG REQUIRED)
endif()

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.vix/vix_deps.cmake")
    include("${CMAKE_CURRENT_SOURCE_DIR}/.vix/vix_deps.cmake")
endif()

function(wall_link_optional_targets tgt)
    foreach(dep IN LISTS ARGN)
        if (TARGET ${dep})
            target_link_libraries(${tgt} PRIVATE ${dep})
        endif()
    endforeach()
endfunction()

add_library(wall_core
    src/util/Clock.cpp
    src/util/Ids.cpp
    src/util/Strings.cpp
    src/util/Env.cpp

    src/domain/Message.cpp
    src/domain/Reaction.cpp
    src/domain/Presence.cpp
    src/domain/Stats.cpp

    src/config/WallConfig.cpp

    src/storage/Sqlite.cpp
    src/storage/Schema.cpp
    src/storage/MessageRepository.cpp
    src/storage/StatsRepository.cpp

    src/validation/PostMessageInput.cpp
    src/validation/ReactInput.cpp
    src/validation/ValidationJson.cpp

    src/json/MessageJson.cpp
    src/json/StatsJson.cpp
    src/json/EventJson.cpp

    src/services/MessageService.cpp
    src/services/ReactionService.cpp
    src/services/StatsService.cpp
    src/services/ModerationService.cpp
    src/services/WallService.cpp

    src/websocket/WallEvents.cpp
    src/websocket/PresenceHub.cpp
    src/websocket/BroadcastService.cpp
    src/websocket/WallWebSocket.cpp

    src/http/PublicRoutes.cpp
    src/http/ApiRoutes.cpp
    src/http/HealthRoutes.cpp
    src/http/RouteRegistrar.cpp
    src/http/HttpServer.cpp

    src/app/ServerContext.cpp
    src/app/Bootstrap.cpp
    src/app/App.cpp

    src/middleware/CorsMiddleware.cpp
    src/middleware/RateLimitMiddleware.cpp
    src/middleware/RequestIdMiddleware.cpp
    src/middleware/SecurityHeadersMiddleware.cpp
)

add_library(wall::core ALIAS wall_core)

target_include_directories(wall_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(wall_core
    PUBLIC
        vix::vix
)

add_executable(wall
    src/main.cpp
)

target_link_libraries(wall
    PRIVATE
        wall::core
)

if (MSVC)
    target_compile_options(wall_core PRIVATE /W4 /permissive-)
    target_compile_options(wall PRIVATE /W4 /permissive-)
else()
    target_compile_options(wall_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(wall PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (WALL_BUILD_TESTS)
    include(CTest)
    enable_testing()

    add_executable(wall_validation_tests
        tests/unit/ValidationTests.cpp
    )
    target_link_libraries(wall_validation_tests PRIVATE wall::core)
    if (MSVC)
        target_compile_options(wall_validation_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(wall_validation_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME wall_validation_tests COMMAND wall_validation_tests)

    add_executable(wall_message_repository_tests
        tests/unit/MessageRepositoryTests.cpp
    )
    target_link_libraries(wall_message_repository_tests PRIVATE wall::core)
    if (MSVC)
        target_compile_options(wall_message_repository_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(wall_message_repository_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME wall_message_repository_tests COMMAND wall_message_repository_tests)

    add_executable(wall_message_service_tests
        tests/unit/MessageServiceTests.cpp
    )
    target_link_libraries(wall_message_service_tests PRIVATE wall::core)
    if (MSVC)
        target_compile_options(wall_message_service_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(wall_message_service_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME wall_message_service_tests COMMAND wall_message_service_tests)

    add_executable(wall_reaction_service_tests
        tests/unit/ReactionServiceTests.cpp
    )
    target_link_libraries(wall_reaction_service_tests PRIVATE wall::core)
    if (MSVC)
        target_compile_options(wall_reaction_service_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(wall_reaction_service_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME wall_reaction_service_tests COMMAND wall_reaction_service_tests)

    add_executable(wall_stats_service_tests
        tests/unit/StatsServiceTests.cpp
    )
    target_link_libraries(wall_stats_service_tests PRIVATE wall::core)
    if (MSVC)
        target_compile_options(wall_stats_service_tests PRIVATE /W4 /permissive-)
    else()
        target_compile_options(wall_stats_service_tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
    add_test(NAME wall_stats_service_tests COMMAND wall_stats_service_tests)
endif()

if (WALL_BUILD_EXAMPLES)
    add_executable(wall_http_smoke
        examples/http_smoke.cpp
    )
    target_link_libraries(wall_http_smoke PRIVATE wall::core)

    add_executable(wall_websocket_smoke
        examples/websocket_smoke.cpp
    )
    target_link_libraries(wall_websocket_smoke PRIVATE wall::core)

    add_executable(wall_post_demo
        examples/post_demo.cpp
    )
    target_link_libraries(wall_post_demo PRIVATE wall::core)

    if (MSVC)
        target_compile_options(wall_http_smoke PRIVATE /W4 /permissive-)
        target_compile_options(wall_websocket_smoke PRIVATE /W4 /permissive-)
        target_compile_options(wall_post_demo PRIVATE /W4 /permissive-)
    else()
        target_compile_options(wall_http_smoke PRIVATE -Wall -Wextra -Wpedantic)
        target_compile_options(wall_websocket_smoke PRIVATE -Wall -Wextra -Wpedantic)
        target_compile_options(wall_post_demo PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

add_custom_target(run
    COMMAND $<TARGET_FILE:wall>
    DEPENDS wall
    USES_TERMINAL
)

include(GNUInstallDirs)

install(TARGETS wall wall_core
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY static/
    DESTINATION ${CMAKE_INSTALL_DATADIR}/wall/static
)

install(FILES README.md
    DESTINATION ${CMAKE_INSTALL_DATADIR}/wall
)

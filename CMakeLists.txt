cmake_minimum_required(VERSION 3.20)

project(wall
    VERSION 0.1.0
    DESCRIPTION "Public real-time wall powered by Vix.cpp"
    LANGUAGES CXX
)

# =========================
# Options
# =========================
option(WALL_BUILD_TESTS "Build wall tests" OFF)
option(WALL_BUILD_EXAMPLES "Build wall examples" OFF)

# =========================
# C++ standard
# =========================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# Output directories
# =========================
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# =========================
# Dependencies
# =========================
find_package(vix CONFIG REQUIRED)

# =========================
# Wall library
# =========================
add_library(wall_core
    src/wall/util/Clock.cpp
    src/wall/util/Ids.cpp
    src/wall/util/Strings.cpp
    src/wall/util/Env.cpp

    src/wall/domain/Message.cpp
    src/wall/domain/Reaction.cpp
    src/wall/domain/Presence.cpp
    src/wall/domain/Stats.cpp

    src/wall/config/WallConfig.cpp

    src/wall/storage/Sqlite.cpp
    src/wall/storage/Schema.cpp
    src/wall/storage/MessageRepository.cpp
    src/wall/storage/StatsRepository.cpp

    src/wall/validation/PostMessageInput.cpp
    src/wall/validation/ReactInput.cpp
    src/wall/validation/ValidationJson.cpp

    src/wall/json/MessageJson.cpp
    src/wall/json/StatsJson.cpp
    src/wall/json/EventJson.cpp

    src/wall/services/MessageService.cpp
    src/wall/services/ReactionService.cpp
    src/wall/services/StatsService.cpp
    src/wall/services/ModerationService.cpp
    src/wall/services/WallService.cpp

    src/wall/websocket/WallEvents.cpp
    src/wall/websocket/PresenceHub.cpp
    src/wall/websocket/BroadcastService.cpp
    src/wall/websocket/WallWebSocket.cpp

    src/wall/http/PublicRoutes.cpp
    src/wall/http/ApiRoutes.cpp
    src/wall/http/HealthRoutes.cpp
    src/wall/http/RouteRegistrar.cpp
    src/wall/http/HttpServer.cpp

    src/wall/app/ServerContext.cpp
    src/wall/app/Bootstrap.cpp
    src/wall/app/App.cpp
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

# =========================
# Main executable
# =========================
add_executable(wall
    src/wall/main.cpp
)

target_link_libraries(wall
    PRIVATE
        wall::core
)

# =========================
# Warnings
# =========================
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(wall_core PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

if(MSVC)
    target_compile_options(wall_core PRIVATE
        /W4
    )
endif()

# =========================
# Tests
# =========================
if(WALL_BUILD_TESTS)
    enable_testing()

    add_executable(wall_validation_tests
        tests/unit/ValidationTests.cpp
    )

    target_link_libraries(wall_validation_tests
        PRIVATE
            wall::core
    )

    add_test(NAME wall_validation_tests COMMAND wall_validation_tests)

    add_executable(wall_message_repository_tests
        tests/unit/MessageRepositoryTests.cpp
    )

    target_link_libraries(wall_message_repository_tests
        PRIVATE
            wall::core
    )

    add_test(NAME wall_message_repository_tests COMMAND wall_message_repository_tests)

    add_executable(wall_message_service_tests
        tests/unit/MessageServiceTests.cpp
    )

    target_link_libraries(wall_message_service_tests
        PRIVATE
            wall::core
    )

    add_test(NAME wall_message_service_tests COMMAND wall_message_service_tests)

    add_executable(wall_reaction_service_tests
        tests/unit/ReactionServiceTests.cpp
    )

    target_link_libraries(wall_reaction_service_tests
        PRIVATE
            wall::core
    )

    add_test(NAME wall_reaction_service_tests COMMAND wall_reaction_service_tests)

    add_executable(wall_stats_service_tests
        tests/unit/StatsServiceTests.cpp
    )

    target_link_libraries(wall_stats_service_tests
        PRIVATE
            wall::core
    )

    add_test(NAME wall_stats_service_tests COMMAND wall_stats_service_tests)
endif()

# =========================
# Examples
# =========================
if(WALL_BUILD_EXAMPLES)
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
endif()

# =========================
# Install
# =========================
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

install(FILES
    README.md
    DESTINATION ${CMAKE_INSTALL_DATADIR}/wall
)

include_guard(GLOBAL)

option(
    SDL_GAME_UPDATE_SUBMODULES
    "Initialize the Git submodules required by the project"
    ON
)

if(NOT SDL_GAME_UPDATE_SUBMODULES)
    return()
endif()

# An initialized submodule is already checked out at the commit recorded by
# the parent repository. Avoid invoking Git on every CMake configuration.
if(
    NOT EXISTS "${PROJECT_SOURCE_DIR}/external/SDL/CMakeLists.txt"
    AND EXISTS "${PROJECT_SOURCE_DIR}/.git"
)
    find_package(Git QUIET)

    if(NOT Git_FOUND)
        message(FATAL_ERROR
            "Git is required to initialize external/SDL. "
            "Install Git or configure with -DSDL_GAME_UPDATE_SUBMODULES=OFF."
        )
    endif()

    execute_process(
        COMMAND "${GIT_EXECUTABLE}" submodule update --init --recursive -- external/SDL
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        RESULT_VARIABLE SDL_SUBMODULE_RESULT
        OUTPUT_VARIABLE SDL_SUBMODULE_OUTPUT
        ERROR_VARIABLE SDL_SUBMODULE_ERROR
    )

    if(NOT SDL_SUBMODULE_RESULT EQUAL 0)
        string(STRIP "${SDL_SUBMODULE_ERROR}" SDL_SUBMODULE_ERROR)
        message(FATAL_ERROR
            "Could not initialize external/SDL (exit code ${SDL_SUBMODULE_RESULT}).\n"
            "${SDL_SUBMODULE_ERROR}"
        )
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/SDL/CMakeLists.txt")
    message(FATAL_ERROR
        "external/SDL is missing. Clone the repository with submodules or run "
        "git submodule update --init --recursive."
    )
endif()

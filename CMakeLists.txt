cmake_minimum_required(VERSION 3.28)
project(FootballChampionshipFMI)

set(CMAKE_CXX_STANDARD 20)

# =========================
# Catch2
# =========================
include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.4
)

FetchContent_MakeAvailable(Catch2)

enable_testing()

# =========================
# UTILS VALIDATORS
# =========================
add_library(utils_validator
        src/utils/validator/CommandLineValidator.cpp
        src/utils/validator/StringValidator.cpp
)

target_include_directories(utils_validator PUBLIC
        src/utils/validator
)

# =========================
# MODEL CHAMPIONSHIP
# =========================
add_library(model_championship
        src/model/championship/accountingManager/AccountingManager.cpp
        src/model/championship/history/ChampionshipHistory.cpp
        src/model/championship/validator/ChampionshipValidator.cpp
        src/model/championship/Championship.cpp
)

target_include_directories(model_championship PUBLIC
        src/model/championship
)

# =========================
# MODEL MATCH
# =========================
add_library(model_match
        src/model/match/lineup/Lineup.cpp
        src/model/match/validator/MatchValidator.cpp
        src/model/match/Match.cpp
)

target_include_directories(model_match PUBLIC
        src/model/match
)

# =========================
# MODEL PLAYER
# =========================
add_library(model_player
        src/model/player/validator/PlayerValidator.cpp
        src/model/player/Player.cpp
)

target_include_directories(model_player PUBLIC
        src/model/player
)

target_link_libraries(model_player PUBLIC utils_validator)

# =========================
# MODEL TEAM
# =========================
add_library(model_team
        src/model/team/factory/TeamFactory.cpp
        src/model/team/manager/TeamManager.cpp
        src/model/team/validator/TeamValidator.cpp
        src/model/team/AttackingTeam.cpp
        src/model/team/BalancedTeam.cpp
        src/model/team/DefensiveTeam.cpp
        src/model/team/Team.cpp
)

target_include_directories(model_team PUBLIC
        src/model/team
)

target_link_libraries(model_team PUBLIC utils_validator)

# =========================
# SIMULATION CORE
# =========================
add_library(simulation
        src/simulation/MatchResultApplier.cpp
)

target_include_directories(simulation PUBLIC
        src/simulation
)

target_link_libraries(simulation PUBLIC
        model_championship
        model_match
        model_team
)

# =========================
# SIMULATION VALIDATOR
# =========================
add_library(simulation_validator
        src/simulation/validator/FootballGameSimulatorValidator.cpp
)

target_include_directories(simulation_validator PUBLIC
        src/simulation/validator
)

target_link_libraries(simulation_validator PUBLIC
        model_championship
        model_match
        model_team
)

# =========================
# SIMULATION ENGINE
# =========================
add_library(simulation_engine
        src/simulation/engine/FootballGameEngine.cpp
        src/simulation/engine/PlayerEngine.cpp
        src/simulation/engine/StatisticsEngine.cpp
        src/simulation/engine/SystemCommandsEngine.cpp
)

target_include_directories(simulation_engine PUBLIC
        src/simulation/engine
)

target_link_libraries(simulation_engine PUBLIC
        model_championship
        model_match
        model_player
        model_team
        utils_validator
        simulation_validator
        simulation
)

# =========================
# UTILS
# =========================
add_library(utils
        src/utils/CommandLineInterpreter.cpp
)

target_include_directories(utils PUBLIC
        src/utils
)

target_link_libraries(utils PUBLIC
        simulation_engine
        model_championship
        model_match
        model_player
        model_team
)

# =========================
# EXECUTABLE
# =========================
add_executable(FootballChampionshipFMI src/main.cpp)

target_link_libraries(FootballChampionshipFMI PRIVATE
        utils
)

# =========================
# TESTS
# =========================
add_executable(engine_tests)

target_sources(engine_tests PRIVATE
        test/simulation/engine/FootballGameEngineTest.cpp
        test/simulation/engine/PlayerEngineTest.cpp
)

target_link_libraries(engine_tests PRIVATE
        Catch2::Catch2WithMain
        simulation_engine
        model_player
        model_match
        model_team
        model_championship
)

include(Catch)
include(CTest)

catch_discover_tests(engine_tests)
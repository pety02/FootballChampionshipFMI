cmake_minimum_required(VERSION 3.28)
project(FootballChampionshipFMI)

set(CMAKE_CXX_STANDARD 20)

# Library model_championship
add_library(model_championship
        src/model/championship/accountingManager/AccountingManager.cpp
        src/model/championship/history/ChampionshipHistory.cpp
        src/model/championship/validator/ChampionshipValidator.cpp
        src/model/championship/Championship.cpp
)

target_include_directories(model_championship PUBLIC
        src/model/championship
        src/model/championship/accountingManager
        src/model/championship/history
        src/model/championship/validator
)

# Library model_match
add_library(model_match
        src/model/match/lineup/Lineup.cpp
        src/model/match/validator/MatchValidator.cpp
        src/model/match/Match.cpp
)

target_include_directories(model_match PUBLIC
        src/model/match
        src/model/match/lineup
        src/model/match/validator
)

# Library model_player
add_library(model_player
        src/model/player/validator/PlayerValidator.cpp
        src/model/player/Player.cpp
)

target_include_directories(model_player PUBLIC
        src/model/player
        src/model/player/validator
)

# Library model_team
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
        src/model/team/factory
        src/model/team/manager
        src/model/team/validator
)

# Library simulation
add_library(simulation
        src/simulation/validator/FootballGameSimulatorValidator.cpp
        src/simulation/FootballGameSimulator.cpp
        src/simulation/MatchResultApplier.cpp
        src/simulation/MatchResultApplier.h
)

target_include_directories(simulation PUBLIC
        src/simulation
        src/simulation/validator
)

# Library utils
add_library(utils
        src/utils/Map.cpp
        src/utils/StringValidator.cpp
)

target_include_directories(utils PUBLIC
        src/utils
)

# Add executable main.cpp
add_executable(FootballChampionshipFMI src/main.cpp
        src/simulation/MatchResultApplier.h)

# Link the libraries
target_link_libraries(FootballChampionshipFMI PRIVATE
        model_championship
        model_match
        model_player
        model_team
        simulation
        utils
)
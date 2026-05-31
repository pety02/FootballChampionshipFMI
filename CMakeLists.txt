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
        src/model/championship/accountingManager/AccountingManager.h
        src/model/championship/history/ChampionshipHistory.h
        src/model/championship/validator/ChampionshipValidator.h
        src/model/championship/Championship.h
)

# Library model_match
add_library(model_match
        src/model/match/lineup/Lineup.cpp
        src/model/match/validator/MatchValidator.cpp
        src/model/match/Match.cpp
)

target_include_directories(model_match PUBLIC
        src/model/match/lineup/Lineup.h
        src/model/match/validator/MatchValidator.h
        src/model/match/Match.h
)

# Library model_player
add_library(model_player
        src/model/player/validator/PlayerValidator.cpp
        src/model/player/Player.cpp
)

target_include_directories(model_player PUBLIC
        src/model/player/validator/PlayerValidator.h
        src/model/player/Player.h
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
        src/model/team/factory/TeamFactory.h
        src/model/team/manager/TeamManager.h
        src/model/team/validator/TeamValidator.h
        src/model/team/AttackingTeam.h
        src/model/team/BalancedTeam.h
        src/model/team/DefensiveTeam.h
        src/model/team/Team.h
)

# Library simulation
add_library(simulation
        src/simulation/validator/FootballGameSimulatorValidator.cpp
        src/simulation/FootballGameSimulator.cpp
        src/simulation/MatchResultApplier.cpp
        src/simulation/MatchResultApplier.h
)

target_include_directories(simulation PUBLIC
        src/simulation/validator/FootballGameSimulatorValidator.h
        src/simulation/FootballGameSimulator.h
        src/simulation/MatchResultApplier.h
)

# Library utils
add_library(utils
        src/utils/Map.cpp
        src/utils/StringValidator.cpp
)

target_include_directories(utils PUBLIC
        src/utils/Map.h
        src/utils/StringValidator.h
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
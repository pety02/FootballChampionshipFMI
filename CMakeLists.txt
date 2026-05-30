cmake_minimum_required(VERSION 3.28)
project(FootballChampionshipFMI)

set(CMAKE_CXX_STANDARD 20)

add_executable(FootballChampionshipFMI main.cpp
        PlayerValidator.cpp
        StringValidator.cpp
        MatchValidator.cpp
        ChampionshipValidator.cpp
        Player.cpp
        Team.cpp
        TeamFactory.cpp
        TeamManager.cpp
        TeamValidator.cpp
        AttackingTeam.h
        AttackingTeam.cpp
        DefensiveTeam.h
        DefensiveTeam.cpp
        BalancedTeam.h
        BalancedTeam.cpp
        Championship.h
        ChampionshipHistory.h
        ChampionshipHistory.cpp
        Championship.cpp
        Lineup.cpp
        Match.cpp
        FootballGameSimulator.h
        FootballGameSimulator.cpp
        Map.h
        AccountingManager.h
        AccountingManager.cpp
        MatchResultApplier.h
        FootballGameSimulatorValidator.h
        FootballGameSimulatorValidator.cpp
)

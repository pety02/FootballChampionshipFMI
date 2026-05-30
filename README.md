# FootballChampionshipFMI
**Final Project for Object Oriented Programming course**

## Project Overview:
> This project simulates a football championship across multiple seasons. Each championship follows a group stage format where every team plays against every other team twice—once at home and once away. For each match, realistic starting lineups are selected, and after every game, team and player statistics are updated. The simulation maintains a complete history of all championships, allowing for analysis of team and player performance over time.

### Miro Board design decisions:

<img width="1257" height="762" alt="Player" src="https://github.com/user-attachments/assets/dd660eb4-5d0b-42de-938f-6f3b19a59cd1" />
<img width="1035" height="740" alt="Team" src="https://github.com/user-attachments/assets/288a7883-4362-48bb-83ce-4bfea9537c92" />
<img width="2803" height="557" alt="Teams" src="https://github.com/user-attachments/assets/5d06659e-45a4-47b8-8a86-32269edfb228" />
<img width="535" height="352" alt="Match" src="https://github.com/user-attachments/assets/377a871e-8877-4d53-b13c-e1cb2d176ed4" />
<img width="492" height="182" alt="Lineup" src="https://github.com/user-attachments/assets/9aed68ae-8fde-4aa4-b89e-213e580bc236" />
<img width="561" height="317" alt="Championship" src="https://github.com/user-attachments/assets/bcf1e8de-5cfd-4ab3-9eb8-81ea0432a3e8" />
<img width="475" height="182" alt="ChampionshipCollection" src="https://github.com/user-attachments/assets/8f20e8db-bb55-491f-8736-063a07e41f38" />

## Used Design Patterns:
- **Factory Pattern**: TeamFactory is used for creating different teams on the base of their types and each team knows how to manage adding and removing players in it on the base of different rules for the different type of teams.
- **Facade Pattern**: Each team's statistics and budget is controlled of a manager via the extra introduced TeamManager class while the Team controls its characteristics.
- **Separattion of Validating logic in separate classes**: Some validator classes with static validation methods were added to make checks on the values of the fields of the objects before they to be created.  

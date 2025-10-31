﻿#include <iostream>
#include <map>
#include "Pipe.h"
#include "CS.h"
#include "Logger.h"
#include "utils.h"
#include "file_op.h"
#include "operations.h"
#include "globals.h"

void showMenu(std::map<int, Pipe>&pipes, std::map<int, CompressStation>&stations, Logger & logger) {
    int menu_choose;

    while (true) {
        std::cout << "Select an action:\n"
            << "1. Add pipe\n"
            << "2. Add CS\n"
            << "3. View all objects\n"
            << "4. Search pipes\n"
            << "5. Search CS\n"
            << "6. Batch edit pipes\n"
            << "7. Save\n"
            << "8. Load\n"
            << "9. Edit pipe by ID (all fields)\n"
            << "10. Edit CS by ID (all fields)\n"
            << "0. Exit\n";

        if (!isValidInput(menu_choose, "Enter your choice: ")) {
            std::cout << "Invalid input! Please enter a number.\n\n";
            continue;
        }

        logger.logUserInput(std::to_string(menu_choose));

        switch (menu_choose) {
        case 1:
            addPipe(pipes, logger);
            break;

        case 2:
            addCompressStation(stations, logger);
            break;

        case 3:
            viewAllObjects(pipes, stations);
            break;

        case 4: {
            std::cout << "Search pipes by:\n"
                << "1. ID\n"
                << "2. Name\n"
                << "3. Repair status\n";

            int searchChoice;
            if (!isValidInput(searchChoice, "Enter your choice: ")) {
                std::cout << "Invalid choice!\n\n";
                break;
            }
            logger.logUserInput(std::to_string(searchChoice));

            std::vector<int> foundPipes;

            if (searchChoice == 1) {
                int searchId;
                if (!isValidInput(searchId, "Enter pipe ID to search: ")) {
                    std::cout << "Invalid ID!\n\n";
                    break;
                }
                logger.logUserInput(std::to_string(searchId));
                foundPipes = findPipesById(pipes, searchId);

            }
            else if (searchChoice == 2) {
                std::string name;
                if (!isValidInput(name, "Enter name to search: ")) {
                    std::cout << "Invalid name!\n\n";
                    break;
                }
                logger.logUserInput(name);
                foundPipes = findPipesByName(pipes, name);

            }
            else if (searchChoice == 3) {
                std::cout << "Search by status:\n"
                    << "1. Under renovation\n"
                    << "2. Working\n";

                int statusChoice;
                if (!isValidInput(statusChoice, "Enter your choice: ")) {
                    std::cout << "Invalid choice!\n\n";
                    break;
                }
                logger.logUserInput(std::to_string(statusChoice));

                foundPipes = findPipesByStatus(pipes, statusChoice == 1);

            }
            else {
                std::cout << "Invalid choice!\n\n";
                break;
            }

            if (foundPipes.empty()) {
                std::cout << "No pipes found.\n\n";
            }
            else {
                std::cout << "Found " << foundPipes.size() << " pipes:\n";
                for (int id : foundPipes) {
                    pipes[id].displayInfo();
                }
            }
            break;
        }

        case 5: {
            std::cout << "Search CS by:\n"
                << "1. ID\n"
                << "2. Name\n"
                << "3. Unused percentage\n";

            int searchChoice;
            if (!isValidInput(searchChoice, "Enter your choice: ")) {
                std::cout << "Invalid choice!\n\n";
                break;
            }
            logger.logUserInput(std::to_string(searchChoice));

            std::vector<int> foundStations;

            if (searchChoice == 1) {
                int searchId;
                if (!isValidInput(searchId, "Enter CS ID to search: ")) {
                    std::cout << "Invalid ID!\n\n";
                    break;
                }
                logger.logUserInput(std::to_string(searchId));
                foundStations = findStationsById(stations, searchId);

            }
            else if (searchChoice == 2) {
                std::string name;
                if (!isValidInput(name, "Enter name to search: ")) {
                    std::cout << "Invalid name!\n\n";
                    break;
                }
                logger.logUserInput(name);
                foundStations = findStationsByName(stations, name);

            }
            else if (searchChoice == 3) {
                double minPercent;
                if (!isValidInput(minPercent, "Enter minimum unused percentage: ")) {
                    std::cout << "Invalid percentage!\n\n";
                    break;
                }
                logger.logUserInput(std::to_string(minPercent));
                foundStations = findStationsByUnusedPercentage(stations, minPercent);

            }
            else {
                std::cout << "Invalid choice!\n\n";
                break;
            }

            if (foundStations.empty()) {
                std::cout << "No CS found.\n\n";
            }
            else {
                std::cout << "Found " << foundStations.size() << " CS:\n";
                for (int id : foundStations) {
                    stations[id].displayInfo();
                }
            }
            break;
        }

        case 6:
            batchEditPipes(pipes, logger);
            break;

        case 7: {
            std::string filename;
            if (!isValidInput(filename, "Enter filename to save: ")) {
                std::cout << "Invalid filename!\n\n";
                break;
            }
            logger.logUserInput(filename);

            std::cout << "Are you sure? The file will be permanently replaced.\n";
            std::cout << "Choice: Y/N (Yes/No)\n";

            char choice;
            std::cin >> choice;
            clearInputBuffer();
            logger.logUserInput(std::string(1, choice));

            if (tolower(choice) == 'y') {
                saveData(filename, pipes, stations, logger);
            }
            else {
                std::cout << "Save cancelled.\n\n";
            }
            break;
        }

        case 8: {
            std::string filename;
            if (!isValidInput(filename, "Enter filename to load: ")) {
                std::cout << "Invalid filename!\n\n";
                break;
            }
            logger.logUserInput(filename);

            std::cout << "Are you sure? The current data will be replaced.\n";
            std::cout << "Choice: Y/N (Yes/No)\n";

            char choice;
            std::cin >> choice;
            clearInputBuffer();
            logger.logUserInput(std::string(1, choice));

            if (tolower(choice) == 'y') {
                loadData(filename, pipes, stations, logger);
            }
            else {
                std::cout << "Load cancelled.\n\n";
            }
            break;
        }

        case 9:
            editPipe(pipes, logger);
            break;

        case 10:
            editCompressStation(stations, logger);
            break;

        case 0:
            std::cout << "Goodbye!\n";
            return;

        default:
            std::cout << "Invalid choice! Please enter a number between 0 and 12.\n\n";
            break;
        }
    }
}

int main() {
    std::map<int, Pipe> pipes;
    std::map<int, CompressStation> stations;
    Logger logger("user_commands_log.txt");

    std::cout << "Welcome to the application 'Gas and Oil Pipeline Transportation System'\n";

    showMenu(pipes, stations, logger);

    return 0;
}
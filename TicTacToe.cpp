#include <iostream>
#include <vector>
#include <string>
#include <map>

// magic square config
void mapInit(std::map<int, std::pair<int, std::string>> &gameOptions)
{
    gameOptions[1] = std::make_pair(8, "");
    gameOptions[2] = std::make_pair(1, "");
    gameOptions[3] = std::make_pair(6, "");
    gameOptions[4] = std::make_pair(3, "");
    gameOptions[5] = std::make_pair(5, "");
    gameOptions[6] = std::make_pair(7, "");
    gameOptions[7] = std::make_pair(4, "");
    gameOptions[8] = std::make_pair(9, "");
    gameOptions[9] = std::make_pair(2, "");
}

// numpad key order
void printField(std::map<int, std::pair<int, std::string>> gameOptions)
{
    int i = 7;
    for (auto const& [key, value] : gameOptions)
    {
        std::cout << ((i - 1) % 3 == 0 ? " " : " | ") << (gameOptions[i].second == "" ? " " : gameOptions[i].second);

        if (i % 3 == 0 && i != 3)
        {
            i = i - 5;
            std::cout << "\n-----------\n";
        }
        else 
        {
            i += 1;
        }
    }
    std::cout << "\n";
}

bool hasTripletsWithSum(std::vector<int> set, int n, int sum, int count)
{
    if (sum == 0 && count == 3)
        return true;
    if (n == 0)
        return false;

    // Add nothing if the current value is greater than the sum
    if (set[n - 1] > sum)
        return hasTripletsWithSum(set, n - 1, sum, count);

    // Option 1: Add value
    bool include = hasTripletsWithSum(set, n - 1, sum - set[n - 1], count + 1);

    // Option 2: Do not add value
    bool exclude = hasTripletsWithSum(set, n - 1, sum, count);

    return include || exclude;
}

bool hasWon(std::map<std::string, std::vector<int>> occupiedFields, std::string player, int sum)
{
    std::map<std::string, std::vector<int>>::const_iterator pos = occupiedFields.find(player);

    if (pos == occupiedFields.end())
    {
        return false;
    }
    else
    {
        return hasTripletsWithSum(pos->second, pos->second.size(), sum, 0);
    }
}

int main()
{
    std::map<int, std::pair<int, std::string>> gameOptions;
    int playerField;
    std::string player = "X";
    std::map<std::string, std::vector<int>> occupiedFields;
    bool changePlayer = false;

    mapInit(gameOptions);

    printField(gameOptions);

    while (!hasWon(occupiedFields, player, 15) && !(occupiedFields["X"].size() + occupiedFields["O"].size() >= 9)) 
    {
        if (player == "X" && changePlayer)
        {
            player = "O";
        }
        else if (changePlayer)
        {
            player = "X";
        }

        std::cout << "Player " << player << ": Select your field (1-9): ";

        if (!(std::cin >> playerField) || playerField < 0 || playerField > 9 || gameOptions[playerField].second == "X" || gameOptions[playerField].second == "O")
        {
            std::cout << "Choose another field!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            changePlayer = false;
            continue;
        }

        changePlayer = true;
        gameOptions[playerField].second = player;
        occupiedFields[player].push_back(gameOptions[playerField].first);
    
        printField(gameOptions);
    }


    if (occupiedFields["X"].size() + occupiedFields["O"].size() >= 9 && !hasWon(occupiedFields, player, 15))
    {
        std::cout << "Tie!";
    }
    else
    {
        std::cout << player << " has won!";
    }
}
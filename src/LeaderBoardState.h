#pragma once
#include "State.h"

// Define a struct to hold the score data
struct ScoreEntry {
    std::string name;
    int score;

    // Define the < operator for sorting
    bool operator<(const ScoreEntry& other) const {
        return score > other.score; // Sort in descending order
    }
};

class LeaderBoardState :
    public State
{
public:
    LeaderBoardState(Scyjz14Engine* engine) : State(engine) {
        loadScores();
    }
    ~LeaderBoardState();

    void initialiseStateObject() override;

    void virtSetupBackgroundBuffer() override;

    void virtDrawStringsUnderneath() override;

    void virtMouseUp(int iButton, int iX, int iY) override;

    void loadScores();

private:
    std::vector<ScoreEntry> scores;
};
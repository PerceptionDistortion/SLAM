#pragma once

class FilterVisualMatches{
public:

//directly done on the 2 frames' descriptors
bool LoweRatioTest();

//mutual keypoint from both sides
bool crossFilterCheck();

private:
};
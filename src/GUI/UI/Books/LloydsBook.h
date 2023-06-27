#pragma once
#include "GUI/UI/UIBooks.h"

struct GUIWindow_LloydsBook : public GUIWindow_Book {
    GUIWindow_LloydsBook(int casterId, int spellLevel);
    virtual ~GUIWindow_LloydsBook() {}

    virtual void Update();

    void flipButtonClicked(bool isRecalling);
    void hintBeaconSlot(int beaconId);
    void installOrRecallBeacon(int beaconId);
 private:
    int _maxBeacons;
    bool _recallingBeacon;
    int _casterId;
    int _spellLevel;
};

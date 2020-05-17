#ifndef CLOCKWORK_WAVE_APP_H
#define CLOCKWORK_WAVE_APP_H

#include <Application.h>

class RegularWindow;
class TimeKeeper;
class BMenuBar;

class ClockworkWaveApp : public BApplication {
public:
	ClockworkWaveApp();

private:
	void ReadyToRun() override;
	void Quit() override;

	void MakeClockWin();
	void MakeWaveWin();
	BMenuBar* MakeMenuBar(bool forClock);

	void MessageReceived(BMessage* message) override;
	void AboutRequested() override;
	void CheckWindow(BMessage* message);
	void ShowClock();
	void ShowWave();

	void ShowWindow(BWindow* window);

private:
	RegularWindow* fClockWin;
	RegularWindow* fWaveWin;
	TimeKeeper* fTimeKeeper;
};


#endif //  CLOCKWORK_WAVE_APP_H

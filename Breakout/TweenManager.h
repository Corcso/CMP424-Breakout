#pragma once
#include <vector>
#include <functional>

class TweenManager
{
public:
	struct Tween {
		Tween(float start, float end, float speed, float t, std::function<void(float)> applicationFunction, std::function<void()> callbackFunction) 
			: start(start), end(end), speed(speed), t(t), applicationFunction(applicationFunction), callbackFunction(callbackFunction), finished(false) {};
		float start;
		float end;
		float t;
		float speed;
		std::function<void(float)> applicationFunction;
		std::function<void()> callbackFunction;
		bool finished;
	};

	TweenManager();

	void update(float dt);

	void addTween(float start, float end, float speed, std::function<void(float)> applicationFunction);
	void addTweenWithCallback(float start, float end, float speed, std::function<void(float)> applicationFunction, std::function<void()> callbackFunction);
private:
	std::vector<Tween> activeTweens;
};


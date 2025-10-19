#include "TweenManager.h"

TweenManager::TweenManager()
{
}

void TweenManager::update(float dt)
{
	for (auto& tween : activeTweens) {
		if (tween.finished) continue;

		tween.t += dt * tween.speed;
		float value = (tween.t * (tween.end - tween.start)) + tween.start;
		tween.applicationFunction(value);

		if (tween.t >= 1.0f) {
			tween.finished = true;
			tween.callbackFunction();
		}
	}
	for (auto it = activeTweens.begin(); it != activeTweens.end();) {
		if (it->finished) {
			it = activeTweens.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void TweenManager::addTween(float start, float end, float speed, std::function<void(float)> applicationFunction)
{
	activeTweens.emplace_back(start, end, speed, 0.0f, applicationFunction, []() {});
}

void TweenManager::addTweenWithCallback(float start, float end, float speed, std::function<void(float)> applicationFunction, std::function<void()> callbackFunction)
{
	activeTweens.emplace_back(start, end, speed, 0.0f, applicationFunction, callbackFunction);
}

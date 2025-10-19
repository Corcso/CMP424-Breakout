#include "TweenManager.h"

TweenManager::TweenManager()
{
}

void TweenManager::update(float dt)
{
	// Loop over an enact on all tweens
	for (auto& tween : activeTweens) {
		if (tween.finished) continue;

		tween.t += dt * tween.speed;
		float tInt = tween.t; // Interpolated by easing function value of t
		tInt = (tInt <= 0) ? 0 : (tInt >= 1) ? 1 : tInt; // Clamp tInt

		float p1, p2 = 0; // Ambigious paramaters used inside easing functions

		// Easing functions from (Sitnek & Solonev, 2025) easing.net
		switch (tween.easeFunc)
		{
		case EasingFunction::LINEAR_IN_OUT:
			// Do nothing, its linear by default
			break;
		case EasingFunction::SINE_IN_OUT:
			tInt = -(cos(3.141592f * tInt) - 1.0f) / 2.0f;
			break;
		case EasingFunction::ELASTIC_OUT:
			p1 = (2.0f * 3.141592) / 3.0f;

			tInt = (tInt <= 0) ? 0 : (tInt >= 1) ? 1 : pow(2.0f, -10.0f * tInt) * sin((tInt * 10.0f - 0.75) * p1) + 1.0f;
			break;
		case EasingFunction::BOUNCE_OUT:
			p1 = 7.5625f;
			p2 = 2.75f;

			if (tInt < 1.0f / p2) {
				tInt = p1 * tInt * tInt;
			}
			else if (tInt < 2.0f / p2) {
				tInt = p1 * (tInt -= 1.5f / p2) * tInt + 0.75f;
			}
			else if (tInt < 2.5f / p2) {
				tInt = p1 * (tInt -= 2.25f / p2) * tInt + 0.9375f;
			}
			else {
				tInt = p1 * (tInt -= 2.625f / p2) * tInt + 0.984375f;
			}
			break;
		}

		float value = (tInt * (tween.end - tween.start)) + tween.start;

		tween.applicationFunction(value);

		if (tween.t >= 1.0f) {
			tween.finished = true;
			tween.callbackFunction();
		}
	}
	// Delete completed tweens
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

void TweenManager::addTween(float start, float end, float speed, EasingFunction easeFunc, std::function<void(float)> applicationFunction)
{
	activeTweens.emplace_back(start, end, speed, easeFunc, applicationFunction, []() {});
}

void TweenManager::addTweenWithCallback(float start, float end, float speed, EasingFunction easeFunc, std::function<void(float)> applicationFunction, std::function<void()> callbackFunction)
{
	activeTweens.emplace_back(start, end, speed, easeFunc, applicationFunction, callbackFunction);
}

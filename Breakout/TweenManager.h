#pragma once
#include <vector>
#include <functional>

class TweenManager
{
public:
	enum class EasingFunction {
		LINEAR_IN_OUT,
		SINE_IN_OUT,
		ELASTIC_OUT,
		BOUNCE_OUT
	};

	TweenManager();

	/// <summary>
	/// Update and execute all tweens active by the service. Also cleans up completed tweens.
	/// </summary>
	/// <param name="dt">Delta time</param>
	void update(float dt);

	/// <summary>
	/// Create a new tween, with no callback function.
	/// </summary>
	/// <param name="start">Starting interpolation value</param>
	/// <param name="end">End interpolation value</param>
	/// <param name="speed">Speed of interpolation, (1 = 1 second, 0.5f = 2 seconds)</param>
	/// <param name="applicationFunction">Function used to apply the value</param>
	void addTween(float start, float end, float speed, EasingFunction easeFunc, std::function<void(float)> applicationFunction);

	/// <summary>
	/// Create a new tween, with a callback function to call when the tween has finished.
	/// </summary>
	/// <param name="start">Starting interpolation value</param>
	/// <param name="end">End interpolation value</param>
	/// <param name="speed">Speed of interpolation, (1 = 1 second, 0.5f = 2 seconds)</param>
	/// <param name="applicationFunction">Function used to apply the value</param>
	/// <param name="callbackFunction">Callback function called on tween end</param>
	void addTweenWithCallback(float start, float end, float speed, EasingFunction easeFunc, std::function<void(float)> applicationFunction, std::function<void()> callbackFunction);
private:
	struct Tween {
		Tween(float start, float end, float speed, EasingFunction easeFunc, std::function<void(float)> applicationFunction, std::function<void()> callbackFunction)
			: start(start), end(end), speed(speed), easeFunc(easeFunc), t(0), applicationFunction(applicationFunction), callbackFunction(callbackFunction), finished(false) {
		};
		float start;
		float end;
		float t;
		float speed;
		EasingFunction easeFunc;
		std::function<void(float)> applicationFunction;
		std::function<void()> callbackFunction;
		bool finished;
	};

	std::vector<Tween> activeTweens;
};


# Breakout

W Kavanagh & N Merchant. Summer 2024 

## controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

* Fix the compiler issues in the code

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* GameLoop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball [where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist

### Removed unnecessary circular reference preventing compilation - 2 minutes  
Removed the circular reference which prevented the program compiling

### Codebase Familiarisation - 17 minutes  
Familiarised myself with the codebase

### Thanos Snap Powerup - 26 minutes  
Added a Thanos snap powerup which removes half the bricks

### Memory leak removal - 3 minutes  
Removed the unnecessary integer allocation in the fireball powerup

### Twixification - 18 minutes  
Added a twixification feature which, after 5 consecutive brick hits, turns all the bricks into twixes

### Parameterised Powerup per frame chance - 3 minutes  
Completed the todo on the powerup chance parameter

### Allowed Fair Frame Independent powerup chance - 5 minutes  
Switched powerup chance to be time rather than frame dependant
This allows for fairer playing as previously higher frame rate players had a higher chance of powerups

### Screen shake & Tween Service = 40 minutes  
Created a TweenManager class which can handle easy tweening.  
You can create a tween within the manager, apply a start and end value as well as a speed and add a application function.  
The application function is a lambda function which has 1 parameter, value, and allows the developer to apply this value how they please, this means private attributes can be tweened if they have a setter.  

Additionally added a screenshake making use of the tween manager.

### Paddle & Ball Tweens, Adding easing to tween service & fixing paddle set width = 40 minutes  
Added additional tweens on the paddle and ball.  
Added easing functions to the tween service (Sitnik and Solovev, 2025) as well as a callback function. 
The callback function will happen once the tween is complete.
Also fixed the set width function on the paddle as it did not calculate the position properly.

### SFX Additions - 14 minutes  
Added SFX to the ball hitting the paddle, bricks and wall. Also added a life loose SFX. (DrPetter, Fredricksen and McCormick, 2011)

### Music and party win mode - 21 minutes  
Added win music (MacLeod, 2012) and functions which respawn all bricks, and turn them into rainbow twixes using the TweenManager.
Additionally you can now press "I" to win instantly, for debugging purposes.

### Fix bug with paddle size and interpolation - 11 minutes  
Fixed a bug where the paddle tween would ignore the size set by the powerup.

# References
DrPetter, Fredricksen E. and McCormick C. (2011) *jsfxr.* Available at: https://sfxr.me/ (Accessed on: 19 October 2025)

MacLeod K. (2012) *Who Likes to Party* Available at: https://incompetech.com/music/royalty-free/mp3-royaltyfree/Who%20Likes%20to%20Party.mp3 (Downloaded: 19 October 2025)

Sitnik A. and Solovev I. (2025) *Easing Functions Cheat Sheet.* Available at: https://easings.net/ (Accessed on: 19 October 2025)
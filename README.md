# philosophers <img src="https://user-images.githubusercontent.com/45235527/96753610-698e7080-13d0-11eb-9461-d3351c9208d7.png" alt="Project note" width="50" height="37">

<div align="center">
<img src="https://i.kym-cdn.com/photos/images/original/002/559/624/c87.gif" alt="Totally normal Will Smith eating spaghetti like a normal human being" width="240" height="240">
<p><em>Here is an AI generated gif of Will Smith eating spaghetti so you can feel the same way I felt while doing this project. You're welcome!</em></p>
</div>

## WARNING WARNING WARNING
This README is not done yet so do not bother reading it hahaha or do but whatever ok bye

## Table of contents
* [Project overview](#project-overview)
* [Instructions](#instructions)
* [Bonus](#bonus)
* [What I learned](#what-i-learned)
* [What I would improve](#what-i-would-improve)

## Project overview
>Why did the five philosophers choose a round table for their dinner?
> 
>Because they wanted to have a "well-rounded" discussion on whether it's possible to eat their meals without getting into a "forking" deadlock! 

`...`

This project is 42's twist on 1965 Edsger Dijkstra's Dining Philosophers problem, a classic synchronization problem in computer science that illustrates the challenges of resource allocation and deadlock avoidance in multi-threaded systems.

The problem is defined as follows: There are five philosophers sitting around a circular table, and each philosopher alternates between thinking and eating. There is a bowl of rice placed between each pair of adjacent philsopher and their neighbooring bowl. Therefore, there are five bowls and five chopsticks in total. The behavior of each philosopher is represented by a concurrent process or thread. To eat, a philosopher needs to pick up the two chopsticks adjacent to them. However, a chopstick can only be held by one philosopher at a time. This creates potential conflict if all philosophers decide to eat simultaneously and try to pick up their left chopstick at the same time. The challenge is to design a solution that ensures the followinf conditions are satisfied:

1- Mutual Exclusion: Only one philosopher can hold a chopstick at a time.
2- Deadlock-free: The system should not enter a state where all philosophers are waiting for a chopstick indefinitely.
3- Starvation-free: Every philosopher should get a chance to eat eventually.

In our case, the bowl of rice and chopsticks are replaced by Eminem's favorite meal, his mom's spaghetti, and forks, but the concept stays the same.

## Instructions
### Compilation
The compilation for this project is quite simple. All you need to do is use the <code>make</code> command in the cloned repository, then execture the program like this: <./philo> followed by the arguments, complying with the requirements as shown below.

Example:
```
./philo 2 800 200 200 5
```
#### Arguments requirements
| Arg. number | Description|
|--|--|
| `1` | Number of philosophers |
| `2` | Time to die |
| `3` | Time to eat |
| `4` | Time to sleep |
| `5` | Number of meals |
* The time_to_die countdown starts as soon as the philo has started his meal. If he has not eaten *time_to_die* ms after the beginning of his last meal, well you guessed it, he dies.
* You should never test with more than 200 philosophers! (Do not worry though, I have made sure you don't 😉)
* You should always test with times higher than 60 ms. 

## What I would improve
* The structure of the code to make it faster (checking how much time has passed and seeing what action should be printed in consequence of that). Instead of using my destiny checker hack.
* Protecting my mallocs.

### Destiny checker
Do not take my code as an example! I hacked my way into succeeding this project and I wish I would have had more time to find out ways to make my code more efficient beforehand.

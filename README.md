# Comp2113GP

Group:28

Game Name:《Entrepreneurship simulator: From Zero To Infinity》

Members:

HongZhenghui(3035825784)

ShenZheye(3035770903)

Introduction

   You are a young man who want to build a career through your own hands. You want to start a business and set up a company by yourself. As the manager and operator of the company, you need to make all kinds of decisions carefully, know how to grasp opportunities  to develop the company into a world-class multinational company.


Rules of the game:

Pre setting:

The basic rules of this game are similar to the combination of 《life reopening simulator》 and 《Reigns》. At the beginning of the game,You can choose up to three talents. Talent has a bonus to the game. No talent in the first game. Talent will be gained at the end of a round of the game.

Game mainstream:

In the game, various events occur in the form of text dialogue every turn(One turn is equal to you running the company for 30 days). Usually, players need to choose "reject" or "execute" to decide how to deal with this event. The game will continue indefinitely until a condition that will end the round is triggered. The purpose of players' play is to play a round of games as long as possible to develop their small start-up companies into large multinational companies and eventually go public (for example, listed in Hong Kong stocks or US stocks).


In game numerical value:

In a round of game, There are three important indexes, integrity, influence, monthly profit, and one ultimate index: total assets of the company.


Integrity: whether your company is honest and whether there are exaggerated advertisements. Float, initial 5, floating range is positive 10 to 0, and a round of game will ends if Integrity falls to 0.

Influence: whether or not your company have popularity, and your influence in the industry.Float, initial 5, floating range is positive 10 to 0, and a round of game will ends if Integrity falls to 0.

Monthly profit is the money the company earns every month, which may be positive or negative.

Company's total assets is the most important value. There will be an initial asset at the beginning of the game. If the company's total assets become negative, the company will go bankrupt, and this round of the game will end immediately.


These values are the core of the game, and you need to maintain the balance of these values. For example, choosing to exaggerate your products can improve your Monthly profit, but it will reduce your integrity; Developing new products will reduce monthly profits, but may increase your company's total assets in the future, etc.


Reincarnation of multi round games：

This game encourages players to play in multiple rounds, In other words, you can't win without playing multiple rounds. In a round of game, if the total assets are negative, it will be game over and force the end of the round of game, but you will get a new Talent, such as "communication master (increase your initial value of Influence)". These new talents can be used in your next round of game, making you more likely to win the game.

features:
1.Randomly select the events encountered by players in the main process of the game, and the probability of different events will change according to the preseeting  and players' play.

2.use array to store integrity, connections, monthly profit and the company's total assets, and use stack to store the events that to be triggered.

3.We will dynamically allocate memory for events and the four main numerical value.

4 use file input output to build a save/load system and  players can get information and type in the comments in the interactive system.

5.main file, result file, event file,company file, presetting file.....




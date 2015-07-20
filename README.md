# HunLing
A Small RGP Game
想了解更多？欢迎关注贴吧 http://tieba.baidu.com/字母工作室

游戏名字：灵环
英文名：Soul Ring
游戏类型：2D角色扮演
开发语言：C++
开发工具：Qt5.4 QtCreater
关于剧情：完全没有想法，希望大家出谋划策！
关于人物：有力量，敏捷，体力三个主属性。同时有魂力，灵力，两种魔法值。人物可以携带灵环和灵骨（装备），稍后做详细的介绍。

关于灵环：灵环是游戏的核心，灵环好比宠物小精灵里的精灵，人物每10级可以佩戴多一个灵环，战斗时，灵环可以转换为魂灵帮你作战。每个灵环有一个被动技能，转换成的魂灵拥有该被动技能。
关于魂灵：魂灵也就是世界里的怪物，你所携带的灵环战斗时会转为魂灵，魂灵的能力比天然的厉害得多。每个魂灵有一个攻击技能和一个被动技能，携带的魂灵使用技能时消耗的是人物的魂力或灵力，人物的力量和敏捷和体力决定你所携带的魂灵的攻击力和防御力和生命，天然的就是天然的，除非是NPC，每个魂灵的参数都不一样，都要精心设计。

关于NPC：设计时NPC就是继承人物的，也就是说NPC的主属性也会影响他所携带的魂灵，游戏中，人物更多是与NPC对决。NPC可以提供任务，和帮助玩家理解剧情。

关于主属性：力量和敏捷共同决定所携带的魂灵的攻击力和防御力和生命力，魂力用于发动技能，灵力用于发动更强大的技能，
人物每升一级会自动增加力量敏捷，魂力和灵力每升一级都会自动加一点点。携带灵环和灵骨都对主属性有所要求。敏捷决定速度，力量决定体力！

关于技能：技能分为攻击技能和被动技能，每个魂灵分别有一个，被动技能的作用分为作用于人物和作用于魂灵，被动技能有时比攻击技能更重要。被动技能的作用范围是全体魂灵。攻击技能要消耗魂力或灵力，有的有回个限制。

关于攻克：魂灵有元素抗性和元素加成，分别为，火，冰，电，毒。采用暗黑风格....这些都可以通过技能或灵骨增加。

关于灵骨：灵骨相当于装备，提供六个栏位，每块灵骨都有一个攻击技能和一个被动技能，与它所属的魂灵有关！

关于道具：道具系统极为丰富，前期技能不够用，可以用道具代替，杀死魂灵可以掉落灵环或灵骨，这些都可以卖钱。钱可以买道具。

关于任务：任务是游戏的核心，我个人比较看中一个游戏的背景和文化，所以任务系统会比较庞大。

关于对战：当与魂灵或NPC对战时，速度越高越先出招，最高可以9V9。采用回合制！

关于地图：地图设计了25*25，不够用会再增加，每个地图都有一个坐标。方便大家认路，不是每个地方都可以去，必须要完成所要求的任务。

关于界面：因为技术原因第一个版本只能是传统的GUI界面，偏向文字多，不过我采用了游戏和界面分离的理念，以便日后开发游戏框架，界面在后续版本必会有所改善！

以上是暂时设定的内容，一切都可以改动，有好的建议可以提出！有问题的也可以问，设计理念神马的都可以问，主要就是想大家一起讨论，做一款大家都喜欢的游戏。
#include"Introduce.h"

Scene * IntroductionScene::createScene()
{
	auto scene = Scene::create();
	auto layer = IntroductionScene::create();
	scene->addChild(layer);
	return scene;
}

bool IntroductionScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//page1
	string gameIntroduction1 = "\
	\n一、游戏开始方法介绍\n\
	\n1.运行RedAlert.exe\n\
	\n2.服务端：\
	\n  开始游戏->选择地图->创建游戏->\n设置端口号(默认为8008)->开启服务器\n\
	\n3.客户端：\
	\n  开始游戏->选择地图(需选择与服务端相同的地图)->\n加入游戏->填入正确的IP地址与端口号->加入游戏\n\
	\n4.服务端：\
	\n  界面下方会显示当前加入游戏的人数，点击开始游戏即可进入游戏\n";
	page1 = LabelTTF::create(MyUtility::gbk_2_utf8(gameIntroduction1), "华文行楷", 15);
	page1->setHorizontalAlignment(TextHAlignment::CENTER);
	page1->setPosition(Vec2(origin.x + visibleSize.width / 2, 
		origin.y + visibleSize.height - page1->getContentSize().height / 2));
	page1->setVisible(true);
	addChild(page1);

	//page2
	string gameIntroduction2 = "\
	\n二、游戏内容介绍\n\
	\n1.地图：\
	\n  本游戏支持两张不同的地图，可供玩家自由选择\n\
	\n  地图移动:将鼠标移到界面边缘，地图即可自动移动。\
	\n  可使用快捷键P关闭自动移动功能 也可使用WSAD来代替鼠标进行地图移动\n\
	\n2.玩家：\
	\n  本游戏最多支持四个玩家在同一局域网下联机对战\n\
	\n3.金钱(Money)：\
	\n  初始值为7000 可以用于生产建筑与兵种\n\
	\n  金钱会随时间增长，但增长幅度较慢\n\
	\n  游戏初期较好的攒钱方法是生产矿兵(前提是要有矿场)，\
	\n	矿兵会自动采矿，采矿成功后会取得较大的利润\n";
	page2 = LabelTTF::create(MyUtility::gbk_2_utf8(gameIntroduction2), "华文行楷", 15);
	page2->setHorizontalAlignment(TextHAlignment::CENTER);
	page2->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - page2->getContentSize().height / 2));
	page2->setVisible(false);
	addChild(page2);

	//page3
	string gameIntroduction3 = "\
	\n4.能量(Power)：\
	\n  初始值为4000\n\
	\n  可以用来提高目前游戏中已生产的所有己方兵种的能力，\
	\n  提高一次需要消耗3000能量\n\
	\n  能量会随时间增长，但增长幅度极慢\n\
	\n  在己方有电厂的情况下，能量随时间的增长速度会大幅提升\n";
	page3 = LabelTTF::create(MyUtility::gbk_2_utf8(gameIntroduction3), "华文行楷", 15);
	page3->setHorizontalAlignment(TextHAlignment::CENTER);
	page3->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - page3->getContentSize().height / 2));
	page3->setVisible(false);
	addChild(page3);

	//page4
	string gameIntroduction4 = "\
	\n5.建筑物：\
	\n  点击游戏界面右边的图标，就可以生产相应的建筑物，\
	\n  一个玩家最多同时拥有一种同类型的建筑物。\
	\n  本游戏支持五种不同的建筑物\n\
	\n  ①基地：拥有较高的血量，基地被摧毁后玩家即出局。\
	\n  游戏的目标就是摧毁所有其他敌人的基地\n\
	\n  ③矿场：用于生产矿兵\n\
	\n  ④战车工厂：用于生产叫强大的兵种：坦克\n\
	\n  ⑤兵营：用于生产警察和战士两种兵种\n\
	\n  ⑥电厂：发电。当玩家拥有电厂时，电力的增加速度会大幅加快\n";
	page4 = LabelTTF::create(MyUtility::gbk_2_utf8(gameIntroduction4), "华文行楷", 15);
	page4->setHorizontalAlignment(TextHAlignment::CENTER);
	page4->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - page4->getContentSize().height / 2));
	page4->setVisible(false);
	addChild(page4);

	//page5
	string gameIntroduction5 = "\
	\n6.兵种：\
	\n  当用于相应的建筑物时，点击游戏界面右边的图标，\
	\n  就可以生产相应的士兵。本游戏支持四种兵种\n\
	\n  ①矿兵：由矿场生产。由系统自动操控，玩家不能控制。\n\
	\n  矿兵生产出之后会沿地图上标志出来的路径自动前往矿场，\
	\n  采矿自动返回矿场兵消失，同时金钱会得到一定增长。\
	\n  但矿兵能力较弱，因此玩家往往需要保护矿兵使其能顺利返回\n\
	\n  ②警察：由兵营生产。能力较低，价格便宜\n\
	\n  ③战士：由兵营生产。攻击力强，行动速度慢，价格适中\n\
	\n  ④坦克：由战车工厂生产。能力较强，行动速度快，价格较高\n\
	\n  兵种移动：使用鼠标框选要移动的兵种，\
	\n  处于框选状态的兵种就可以移动到鼠标点击的位置\
	\n  请勿点击有的障碍物地方，否则兵种不会移动\n";
	page5 = LabelTTF::create(MyUtility::gbk_2_utf8(gameIntroduction5), "华文行楷", 15);
	page5->setHorizontalAlignment(TextHAlignment::CENTER);
	page5->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - page5->getContentSize().height / 2));
	page5->setVisible(false);
	addChild(page5);

	//page6
	string gameIntroduction6 = "\
	\n7.兵种升级：\
	\n  当能量大于等于3000时，就可以点击游戏界面右边的图标进行兵种升级。\
	\n  点击后场上的所有己方士兵能力都将获得一定的提高\n\
	\n  请在合理的时机使用兵种升级，这样才能使其功效发挥到最大\n";
	page6 = LabelTTF::create(MyUtility::gbk_2_utf8(gameIntroduction6), "华文行楷", 15);
	page6->setHorizontalAlignment(TextHAlignment::CENTER);
	page6->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - page6->getContentSize().height / 2));
	page6->setVisible(false);
	addChild(page6);

	//page7
	string gameIntroduction7 = "\
	\n三、游戏快捷键\n\
	\n  本游戏支持鼠标键盘交互操作，设计了如下快捷键以方便用户使用\n\
	\n  SPACE：将界面跳转至己方基地\n\
	\n  W：界面上移 S：界面下移 A：界面左移 D：界面右移\n\
	\n  CTRL：游戏默认开启鼠标选框功能\
	\n  按CTRL开始关闭此功能，再按一次又可将其开启\n\
	\n  P：游戏默认开启地图自动移动功能\
	\n  按P关闭地图自动移动功能 再按一次又可将其开启\n";
	page7 = LabelTTF::create(MyUtility::gbk_2_utf8(gameIntroduction7), "华文行楷", 15);
	page7->setHorizontalAlignment(TextHAlignment::CENTER);
	page7->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - page7->getContentSize().height / 2));
	page7->setVisible(false);
	addChild(page7);

	//page8
	string gameIntroduction8 = "\
	\n四、注意事项\n\
	\n  联网游戏时，玩家需要选择同一张地图，\
	\n  否则虽然可以进入游戏，但将会在不同的地图上进行战斗\n\
	\n  基地被催毁后会收到胜负信息，但是并不会退出游戏界面\
	\n  金币和能量仍然在增加，但无法进行生产等任何操作，但可观战\
	\n  如果收到胜负信息后游戏并未结束，请不要关闭游戏\
	\n  关闭游戏会造成其他玩家游戏中断\n\
	\n  由于本游戏需要联网进行，\
	\n  一旦某一用户在游戏进行时中途退出或失去连接，\
	\n  将会导致数据中断，所有玩家的程序都将异常。\
	\n  因此请不要在游戏中途开关游戏，或将游戏最小化\n\
	\n  请不要让士兵在短时间内多次移动，\
	\n  若在一秒内发送数十次移动指令，将会导致数据拥挤，游戏崩溃\n";
	page8 = LabelTTF::create(MyUtility::gbk_2_utf8(gameIntroduction8), "华文行楷", 15);
	page8->setHorizontalAlignment(TextHAlignment::CENTER);
	page8->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - page8->getContentSize().height / 2));
	page8->setVisible(false);
	addChild(page8);

	auto nextlabel = LabelTTF::create(MyUtility::gbk_2_utf8("下一页"), "华文行楷", 15);
	nextPageMenu = MenuItemLabel::create(nextlabel, CC_CALLBACK_1(IntroductionScene::nextPage, this));
	float next_x = nextPageMenu->getContentSize().width;
	float next_y = nextPageMenu->getContentSize().height;
	nextPageMenu->setPosition(Vec2(origin.x + visibleSize.width / 2 + next_x, origin.y + next_y));

	auto lastlabel = LabelTTF::create(MyUtility::gbk_2_utf8("上一页"), "华文行楷", 15);
	lastPageMenu = MenuItemLabel::create(lastlabel, CC_CALLBACK_1(IntroductionScene::lastPage, this));
	float last_x = nextPageMenu->getContentSize().width;
	float last_y = nextPageMenu->getContentSize().height;
	lastPageMenu->setPosition(Vec2(origin.x + visibleSize.width /2 - last_x, origin.y + last_y));
	lastPageMenu->setVisible(false);

	auto backlabel = LabelTTF::create(MyUtility::gbk_2_utf8("返回"), "华文行楷", 15);
	backMenu = MenuItemLabel::create(backlabel, CC_CALLBACK_1(IntroductionScene::backToMenuScene, this));
	float back_x = backMenu->getContentSize().width;
	float back_y = backMenu->getContentSize().height;
	backMenu->setPosition(Vec2(origin.x + visibleSize.width - back_x, origin.y + back_y));

	auto menu = Menu::create(nextPageMenu, lastPageMenu, backMenu, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu);

	return true;
}

void IntroductionScene::backToMenuScene(Ref *pSender)
{
	auto sc = MenuScene::createScene();
	auto reScene = TransitionFadeTR::create(0.5f, sc);
	Director::getInstance()->pushScene(reScene);
}

void IntroductionScene::nextPage(Ref *pSender)
{
	pageNumber++;
	if (pageNumber == 2)
	{
		page1->setVisible(false);
		page2->setVisible(true);
	}
	if (pageNumber == 3)
	{
		page2->setVisible(false);
		page3->setVisible(true);
	}
	if (pageNumber == 4)
	{
		page3->setVisible(false);
		page4->setVisible(true);
	}
	if (pageNumber == 5)
	{
		page4->setVisible(false);
		page5->setVisible(true);
	}
	if (pageNumber == 6)
	{
		page5->setVisible(false);
		page6->setVisible(true);
	}
	if (pageNumber == 7)
	{
		page6->setVisible(false);
		page7->setVisible(true);
	}
	if (pageNumber == 8)
	{
		page7->setVisible(false);
		page8->setVisible(true);
		nextPageMenu->setVisible(false);
	}
	lastPageMenu->setVisible(true);
}

void IntroductionScene::lastPage(Ref *pSender)
{
	pageNumber--;
	if (pageNumber == 1)
	{
		page1->setVisible(true);
		page2->setVisible(false);
		lastPageMenu->setVisible(false);
	}
	if (pageNumber == 2)
	{
		page2->setVisible(true);
		page3->setVisible(false);
	}
	if (pageNumber == 3)
	{
		page3->setVisible(true);
		page4->setVisible(false);
	}
	if (pageNumber == 4)
	{
		page4->setVisible(true);
		page5->setVisible(false);
	}
	if (pageNumber == 5)
	{
		page5->setVisible(true);
		page6->setVisible(false);
	}
	if (pageNumber == 6)
	{
		page6->setVisible(true);
		page7->setVisible(false);
	}
	if (pageNumber == 7)
	{
		page7->setVisible(true);
		page8->setVisible(false);
	}
	nextPageMenu->setVisible(true);
}
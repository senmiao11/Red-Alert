#include"PopupLayer.h"
PopupLayer::~PopupLayer()
{
	CC_SAFE_RELEASE(m_pMenu);
	CC_SAFE_RELEASE(m_sfBackGround);
	CC_SAFE_RELEASE(m_s9BackGround);
	CC_SAFE_RELEASE(m_ltContentText);
	CC_SAFE_RELEASE(m_ltTitle);
}
bool PopupLayer::init()
{
	//若初始化失败，返回false
	if (!Layer::init())
	{
		return false;
	}
	//初始化默认值
	m_pMenu = NULL;
	m_callback = NULL;
	m_sfBackGround = NULL;
	m_s9BackGround = NULL;
	m_ltContentText = NULL;
	m_ltTitle = NULL;
	this->setContentSize(Size::ZERO);
	//初始化需要的Menu,随后根据参数向Menu中添加MenuItem选项
	Menu* menu = Menu::create();
	menu->setPosition(Point::ZERO);
	setMenuButton(menu);
	//添加触摸响应
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch * t,Event *e)
	{
		log("touch");
		return true;
	};
	listener->setSwallowTouches(true);
	//屏蔽下层事件相应，达到模态效果 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}


PopupLayer* PopupLayer::create(const char* backgroundImage)
{
	PopupLayer* m1 = PopupLayer::create();
	m1->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	return m1;
}

void PopupLayer::setTitle(const char * title, int fontsize)
{
	LabelTTF *ltfTitle = LabelTTF::create(MyUtility::gbk_2_utf8(title), "华文行楷", fontsize);
	setLabelTitle(ltfTitle);
}

void PopupLayer::setPopType(POP_TYPE type)
{
	pop_type = type;
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
	LabelTTF *ltf = LabelTTF::create(MyUtility::gbk_2_utf8(text), "华文行楷", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

bool PopupLayer::addButton(const char*normalImage, const char*selectedImage, const char*title, int tag)
{
	Size winSize = Director::getInstance()->getWinSize();
	//创建MenuItem按钮，并设置按钮tag，位置以及回调方法为buttonCallback
	auto  menuImage = MenuItemImage::create(normalImage, selectedImage, CC_CALLBACK_1(PopupLayer::buttonCallBack, this));
	menuImage->setScale(0.6);
	menuImage->setTag(tag);
	menuImage->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	//给MenuItem添加文字，设置颜色，位置
	Size imenu = menuImage->getContentSize();
	LabelTTF *ttf = LabelTTF::create(MyUtility::gbk_2_utf8(title), "华文行楷", 25);
	ttf->setColor(ccc3(0, 0, 0));
	//设置文字在MenuItem中的位置
	ttf->setPosition(ccp(imenu.width / 2, imenu.height / 2));
	menuImage->addChild(ttf);
	getMenuButton()->addChild(menuImage,3);
	return true;
}

void PopupLayer::setCallbackFunc(CCObject* target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}

void PopupLayer::buttonCallBack(CCObject *pSender)
{
	Node * node = dynamic_cast<Node*>(pSender);
	log("[buttonCallBack]touch tag:%d", node->getTag());
	if (m_callback && m_callbackListener)
	{
		log("[buttonCallBack]touch tag:%d",node->getTag());
		//会调用setCallbackFunc方法传入的MenuScene对象的quitButtonCallback方法
		(m_callbackListener->*m_callback)(node);
	}
	this->removeFromParentAndCleanup(true);
}

void PopupLayer::onEnter()
{
	Layer::onEnter();
	Size winSize = Director::getInstance()->getWinSize();
	//根据对话框大小设置九宫格背景图片
	Scale9Sprite *background = getSprite9BackGround();
	background->setContentSize(getContentSize());
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(background, 0, 0);
	_contentSize = getContentSize();
	//添加按钮，并设置其位置
	this->addChild(getMenuButton());
	float btnWidth = _contentSize.width / (getMenuButton()->getChildrenCount() + 1);
	//从Menu项中取得子菜单项
	Vector<Node*>vecArray = getMenuButton()->getChildren();
	int j = 0;
	for (auto it = vecArray.begin(); it != vecArray.end(); it++)
	{
		Node *node = dynamic_cast<Node*>(*it);
		node->setPosition(Point(winSize.width / 2 - _contentSize.width / 2 + btnWidth * (j + 1), winSize.height / 2 -_contentSize.height / 3));
		j++;
	}
	if (getLabelTitle())
	{
		//显示对话框标题
		getLabelTitle()->setPosition(ccpAdd(ccp(winSize.width/2,winSize.height/2), ccp(0, _contentSize.height / 2 - 20)));
		getLabelTitle()->setColor(ccc3(255, 255, 255));
		this->addChild(getLabelTitle());
	}
	//根据对话框类型，设置对话框内容
	switch (pop_type)
	{
	case QUIT:
		if (getLabelContentText())
		{
			LabelTTF* ltf = getLabelContentText();
			ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));
			ltf->setDimensions(CCSizeMake(_contentSize.width - m_contentPadding * 2, _contentSize.height - m_contentPaddingTop));
			ltf->setColor(ccc3(255, 255, 255));
			this->addChild(ltf);
		}
	}
	//对话框弹出效果，由大变小，再由小变大
	Action *popupactions = Sequence::create(ScaleTo::create(0.0, 0.0), ScaleTo::create(0.15, 1.05), ScaleTo::create(0.08, 0.95), ScaleTo::create(0.08, 1.0),NULL);
	this->runAction(popupactions);
}

void PopupLayer::onExit()
{
	Layer::onExit();
}





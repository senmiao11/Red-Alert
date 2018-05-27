//对话框

#ifndef __PopupLayer_H__
#define __PopupLayer_H__
#include"cocos2d.h"
#include<iostream>
#include"ConstUtil.h"
#include "extensions/cocos-ext.h"  
#include"MyUtility.h"
USING_NS_CC_EXT;
USING_NS_CC;

enum POP_TYPE
{
	QUIT,                  //退出游戏
};

class PopupLayer:public Layer
{
public:
	bool init();
	~PopupLayer();
	CREATE_FUNC(PopupLayer);
	//设置对话框类型
	void setPopType(POP_TYPE type);                   
	//根据背景图片创建对象
	static PopupLayer *create(const char* backgroundImage);    
	//设置对话框标题
	void setTitle(const char* title, int fontsize );                
	//设置对话框文本内容
	void setContentText(const char*title, int fontsize,int padding,int paddingTop);           
	//添加对话框按键
	bool addButton(const char*normalImage, const char*selectedImage, const char*title, int tag=0);   
	//把调用对象和其他处理方法设置为按键回调
	void setCallbackFunc(CCObject* target, SEL_CallFuncN callfun);                  
	//进入对话框时调用
	virtual void onEnter();                                                     
	//退出对话框时调用
	virtual void onExit();      
	//按钮点击时调用此方法，然后调用到传入的回调方法
	void buttonCallBack(CCObject * pSender);

private:
	POP_TYPE pop_type;                                                               //对话框类型变量
	int m_contentPadding;                                                            //文字内容两边的空白区距离
	int m_contentPaddingTop;
	CCObject * m_callbackListener;                                                   //回调监听
	SEL_CallFuncN m_callback;                                                        //回调
	CC_SYNTHESIZE_RETAIN(Menu*, m_pMenu, MenuButton);                                //定义retain属性的变量
	CC_SYNTHESIZE_RETAIN(Sprite*, m_sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m_s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m_ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m_ltContentText, LabelContentText);
};                	      
#endif // !__PopupLayer_H__


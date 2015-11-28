//--------------------------------------------------------------------
#include "../Include/FKCW_Story_CommandSet.h"
#include "../Include/FKCW_Story_Layer.h"
//--------------------------------------------------------------------
CCArray gStoryCommandSet;
//--------------------------------------------------------------------
// �ṩ���༭��
#if FKCW_STORY_DESIGNER_TOOL
vector<string> gUsedSpriteFrameNames;
vector<string> gUsedImageNames;
vector<string> gUsedArmatureNames;
#endif
//--------------------------------------------------------------------
void winsize(float w, float h) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::WIN_SIZE);
	c->m_param.winsize.w = w;
	c->m_param.winsize.h = h;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void policy(ResolutionPolicy p) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::POLICY);
	c->m_param.policy.p = p;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void msg(string name, string s, float wait) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::MSG);
	c->m_param.msg.name = FKCW_Base_Utils::Copy(name.c_str());
	c->m_param.msg.s = FKCW_Base_Utils::Copy(s.c_str());
	c->m_param.msg.wait = wait;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void msgsize(float size) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::MSG_SIZE);
	c->m_param.msgsize.size = size;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void msgcolor(unsigned int c) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::MSG_COLOR);
	cmd->m_param.msgcolor.c = c;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void msgpos(float x, float y) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::MSG_POS);
	c->m_param.msgpos.x = x;
	c->m_param.msgpos.y = y;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void msganchor(float x, float y) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::MSG_ANCHOR);
	c->m_param.msganchor.x = x;
	c->m_param.msganchor.y = y;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void msgwidth(float w) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::MSG_WIDTH);
	c->m_param.msgwidth.w = w;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void msgalign(CCTextAlignment a) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::MSG_ALIGN);
	c->m_param.msgalign.a = a;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void msgfont(string fontName) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::MSG_FONT);
	c->m_param.msgfont.fontName = FKCW_Base_Utils::Copy(fontName.c_str());
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void namepos(float x, float y) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::NAME_POS);
	c->m_param.namepos.x = x;
	c->m_param.namepos.y = y;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void namecolor(unsigned int c) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::NAME_COLOR);
	cmd->m_param.namecolor.c = c;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void namesize(float size) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::NAME_SIZE);
	c->m_param.namesize.size = size;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void nameanchor(float x, float y) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::NAME_ANCHOR);
	c->m_param.nameanchor.x = x;
	c->m_param.nameanchor.y = y;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void namefont(string fontName) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::NAME_FONT);
	c->m_param.namefont.fontName = FKCW_Base_Utils::Copy(fontName.c_str());
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void labelcolor(unsigned int c) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::LABEL_COLOR);
	cmd->m_param.labelcolor.c = c;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void labelsize(float size) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::LABEL_SIZE);
	c->m_param.labelsize.size = size;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void labelfont(string fontName) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::LABEL_FONT);
	c->m_param.labelfont.fontName = FKCW_Base_Utils::Copy(fontName.c_str());
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void labelanchor(float x, float y) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::LABEL_ANCHOR);
	c->m_param.labelanchor.x = x;
	c->m_param.labelanchor.y = y;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void labelwidth(float w) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::LABEL_WIDTH);
	c->m_param.labelwidth.w = w;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void labelalign(CCTextAlignment a) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::LABEL_ALIGN);
	c->m_param.labelalign.a = a;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void move(string name, float x, float y, float time) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::MOVE);
	c->m_param.move.name = FKCW_Base_Utils::Copy(name.c_str());
	c->m_param.move.x = x;
	c->m_param.move.y = y;
	c->m_param.move.time = time;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void wait(float time) {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::WAIT);
	c->m_param.wait.time = time;
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void waitarm() {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::WAIT_ARM);
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void waitclick() {
	FKCW_Story_Command* c = FKCW_Story_Command::create(FKCW_Story_Command::WAIT_CLICK);
	gStoryCommandSet.addObject(c);
}
//--------------------------------------------------------------------
void fadein(string name, float time) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::FADE_IN);
	cmd->m_param.fadein.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.fadein.time = time;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void fadeout(string name, float time) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::FADE_OUT);
	cmd->m_param.fadeout.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.fadeout.time = time;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void flash(string name, unsigned int color, float times, float time) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::FLASH);
	cmd->m_param.flash.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.flash.c = color;
	cmd->m_param.flash.times = times;
	cmd->m_param.flash.time = time;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void blink(string name, float times, float time) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::BLINK);
	cmd->m_param.blink.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.blink.times = times;
	cmd->m_param.blink.time = time;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void shake(string name, float amplitude, float time) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::SHAKE);
	cmd->m_param.shake.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.shake.amplitude = amplitude;
	cmd->m_param.shake.time = time;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void scaleto(string name, float to, float time) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::SCALE_TO);
	cmd->m_param.scaleto.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.scaleto.to = to;
	cmd->m_param.scaleto.time = time;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void img(string name, string frameName, float x, float y) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::IMG);
	cmd->m_param.img.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.img.frameName = FKCW_Base_Utils::Copy(frameName.c_str());
	cmd->m_param.img.x = x;
	cmd->m_param.img.y = y;
	gStoryCommandSet.addObject(cmd);

#ifdef FKCW_STORY_DESIGNER_TOOL
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
	if(frame) {
		gUsedSpriteFrameNames.push_back(frameName);
	} else {
		gUsedImageNames.push_back(frameName);
	}
#endif
}
//--------------------------------------------------------------------
void label(string name, string text, float x, float y) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::LABEL);
	cmd->m_param.label.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.label.text = FKCW_Base_Utils::Copy(text.c_str());
	cmd->m_param.label.x = x;
	cmd->m_param.label.y = y;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void arm(string name, string armName, float x, float y) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::ARM);
	cmd->m_param.arm.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.arm.armName = FKCW_Base_Utils::Copy(armName.c_str());
	cmd->m_param.arm.x = x;
	cmd->m_param.arm.y = y;
	gStoryCommandSet.addObject(cmd);

#ifdef FKCW_STORY_DESIGNER_TOOL
	gUsedArmatureNames.push_back(armName);
#endif
}
//--------------------------------------------------------------------
void armplay(string name, string animName) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::ARM_PLAY);
	cmd->m_param.armplay.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.armplay.animName = FKCW_Base_Utils::Copy(animName.c_str());
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void angle(string name, float degree) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::ANGLE);
	cmd->m_param.angle.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.angle.degree = degree;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void rotateby(string name, float delta, float time) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::ROTATE_BY);
	cmd->m_param.rotateby.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.rotateby.delta = delta;
	cmd->m_param.rotateby.time = time;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void bgpos(float x, float y) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::BG_POS);
	cmd->m_param.bgpos.x = x;
	cmd->m_param.bgpos.y = y;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void bg(string frameName) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::BG);
	cmd->m_param.bg.frameName = FKCW_Base_Utils::Copy(frameName.c_str());
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void bgcolor(unsigned int c) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::BG_COLOR);
	cmd->m_param.bgcolor.c = c;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void z(string name, int zOrder) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::Z);
	cmd->m_param.z.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.z.z = zOrder;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void bgm(string musicFile) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::BGM);
	cmd->m_param.bgm.musicFile = FKCW_Base_Utils::Copy(musicFile.c_str());
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void sound(string soundFile) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::SOUND);
	cmd->m_param.sound.soundFile = FKCW_Base_Utils::Copy(soundFile.c_str());
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void remove(string name) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::REMOVE);
	cmd->m_param.remove.name = FKCW_Base_Utils::Copy(name.c_str());
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void show(string name) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::SHOW);
	cmd->m_param.show.name = FKCW_Base_Utils::Copy(name.c_str());
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void hide(string name) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::HIDE);
	cmd->m_param.hide.name = FKCW_Base_Utils::Copy(name.c_str());
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void flipx(string name) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::FLIP_X);
	cmd->m_param.flipx.name = FKCW_Base_Utils::Copy(name.c_str());
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void flipy(string name) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::FLIP_Y);
	cmd->m_param.flipy.name = FKCW_Base_Utils::Copy(name.c_str());
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void pos(string name, float x, float y) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::POS);
	cmd->m_param.pos.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.pos.x = x;
	cmd->m_param.pos.y = y;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void npos(string name, string refName, float relativeX, float relativeY) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::NODE_POS);
	cmd->m_param.npos.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.npos.refName = FKCW_Base_Utils::Copy(refName.c_str());
	cmd->m_param.npos.x = relativeX;
	cmd->m_param.npos.y = relativeY;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void spos(string name, float relativeX, float relativeY) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::SCREEN_POS);
	cmd->m_param.spos.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.spos.x = relativeX;
	cmd->m_param.spos.y = relativeY;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void anchor(string name, float x, float y) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::ANCHOR);
	cmd->m_param.anchor.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.anchor.x = x;
	cmd->m_param.anchor.y = y;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void color(string name, unsigned int c) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::COLOR);
	cmd->m_param.color.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.color.c = c;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
void scale(string name, float x, float y) {
	FKCW_Story_Command* cmd = FKCW_Story_Command::create(FKCW_Story_Command::SCALE);
	cmd->m_param.scale.name = FKCW_Base_Utils::Copy(name.c_str());
	cmd->m_param.scale.x = x;
	cmd->m_param.scale.y = y;
	gStoryCommandSet.addObject(cmd);
}
//--------------------------------------------------------------------
string p(string key) {
	return FKCW_Story_Layer::getParameter(key);
}
//--------------------------------------------------------------------
FKCW_Story_Command::FKCW_Story_Command() :
	m_type(UNKNOWN) 
{
}
//--------------------------------------------------------------------
FKCW_Story_Command::~FKCW_Story_Command() 
{
	switch(m_type) 
	{
	case MSG:
		free((void*)m_param.msg.name);
		free((void*)m_param.msg.s);
		break;
	case MSG_FONT:
		free((void*)m_param.msgfont.fontName);
		break;
	case NAME_FONT:
		free((void*)m_param.namefont.fontName);
		break;
	case LABEL_FONT:
		free((void*)m_param.labelfont.fontName);
		break;
	case IMG:
		free((void*)m_param.img.name);
		free((void*)m_param.img.frameName);
		break;
	case LABEL:
		free((void*)m_param.label.name);
		free((void*)m_param.label.text);
		break;
	case ARM:
		free((void*)m_param.arm.name);
		free((void*)m_param.arm.armName);
		break;
	case ARM_PLAY:
		free((void*)m_param.armplay.name);
		free((void*)m_param.armplay.animName);
		break;
	case ANGLE:
		free((void*)m_param.angle.name);
		break;
	case MOVE:
		free((void*)m_param.move.name);
		break;
	case FLASH:
		free((void*)m_param.flash.name);
		break;
	case BLINK:
		free((void*)m_param.blink.name);
		break;
	case SHAKE:
		free((void*)m_param.shake.name);
		break;
	case ROTATE_BY:
		free((void*)m_param.rotateby.name);
		break;
	case SCALE_TO:
		free((void*)m_param.scaleto.name);
		break;
	case FADE_IN:
		free((void*)m_param.fadein.name);
		break;
	case FADE_OUT:
		free((void*)m_param.fadeout.name);
		break;
	case BG:
		free((void*)m_param.bg.frameName);
		break;
	case BGM:
		free((void*)m_param.bgm.musicFile);
		break;
	case SOUND:
		free((void*)m_param.sound.soundFile);
		break;
	case Z:
		free((void*)m_param.z.name);
		break;
	case REMOVE:
		free((void*)m_param.remove.name);
		break;
	case SHOW:
		free((void*)m_param.show.name);
		break;
	case HIDE:
		free((void*)m_param.hide.name);
		break;
	case FLIP_X:
		free((void*)m_param.flipx.name);
		break;
	case FLIP_Y:
		free((void*)m_param.flipy.name);
		break;
	case POS:
		free((void*)m_param.pos.name);
		break;
	case NODE_POS:
		free((void*)m_param.npos.name);
		free((void*)m_param.npos.refName);
		break;
	case SCREEN_POS:
		free((void*)m_param.spos.name);
		break;
	case ANCHOR:
		free((void*)m_param.anchor.name);
		break;
	case COLOR:
		free((void*)m_param.color.name);
		break;
	case SCALE:
		free((void*)m_param.scale.name);
		break;
	default:
		break;
	}
}
//--------------------------------------------------------------------
FKCW_Story_Command* FKCW_Story_Command::create(Type type) 
{
	FKCW_Story_Command* c = new FKCW_Story_Command();
	if(c->initWithCommand(type)) 
	{
		c->autorelease();
		return c;
	}
	CC_SAFE_RELEASE(c);
	return NULL;
}
//--------------------------------------------------------------------
bool FKCW_Story_Command::initWithCommand(Type type) 
{
	m_type = type;
	memset(&m_param, 0, sizeof(m_param));

	return true;
}
//--------------------------------------------------------------------
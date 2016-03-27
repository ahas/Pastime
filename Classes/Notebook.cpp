#include "Notebook.h"
#include "Gates.h"
#include "Wall.h"
#include "Switch.h"
#include "Highlight.h"
#include "Player.h"
#include "Eraser.h"

#include "cocos2d\external\tinyxml2\tinyxml2.h"
#include <cmath>
#include <sstream>

#define MARGIN_Y 4

WallColor stringToWallColor(std::string str);

Notebook::Notebook()
{
	Node::init();
	_glowSwitch = cocos2d::Sprite::create("glow_switch.png");
	_glowSwitch->setVisible(false);
	this->addChild(_glowSwitch);

	_glowGate = cocos2d::Sprite::create("glow_gate.png");
	_glowGate->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	_glowGate->setVisible(false);
	this->addChild(_glowGate);

	this->scheduleUpdate();
}

Notebook::~Notebook()
{

}

void Notebook::update(float dt)
{
	bool glowASwitch = false;
	_usableSwitch = nullptr;
	_usableGate = nullptr;

	cocos2d::Rect playerBox = _player->getBoundingBox();
	for (Switch* sw : _switches)
	{
		if (playerBox.intersectsRect(sw->getBoundingBox()))
		{
			_usableSwitch = sw;
			_glowSwitch->setPosition(sw->getPosition());
			glowASwitch = true;
			break;
		}
	}

	bool glowAGate = false;
	for (Gate* gate : _gates)
	{
		if (playerBox.intersectsRect(gate->getBoundingBox()))
		{
			_usableGate = gate;
			_glowGate->setPosition(gate->getPosition());
			glowAGate = true;
			break;
		}
	}

	_glowSwitch->setVisible(glowASwitch);
	_glowGate->setVisible(glowAGate);
}

void Notebook::createLines(int num)
{
	int posY = 0;
	const int last = num - 1;

	cocos2d::Size maxSize;

	for (int i = 0; i < num; i++)
	{
		std::string filename = "";
		if (i == num - 1) filename = "line_top.png";
		else filename = "line_bottom.png";

		cocos2d::Sprite* line = cocos2d::Sprite::create(filename);
		line->setAnchorPoint(cocos2d::Vec2(0, 0));
		line->setPositionY(posY);
		line->setZOrder(100);

		_lineHeight = line->getContentSize().height;
		posY += _lineHeight;

		cocos2d::Size lineSize = line->getContentSize();
		maxSize.width = std::max(maxSize.width, lineSize.width);
		maxSize.height = posY;

		this->addChild(line);
	}

	setContentSize(maxSize);
}

void Notebook::loadPage(std::string filename)
{
	std::string xmlString = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
	tinyxml2::XMLDocument doc;
	doc.Parse(xmlString.c_str());

	tinyxml2::XMLElement* pageElement = doc.FirstChildElement("Page");
	createLines(pageElement->IntAttribute("lines"));

	Wall* lastWall = nullptr;

	for (tinyxml2::XMLElement* child = pageElement->FirstChildElement();
		child;
		child = child->NextSiblingElement())
	{
		std::string childName = child->Name();
		if (childName == "Stairs")
		{
			addGates(child, new Stairs(), new Stairs());
		}
		else if (childName == "Door")
		{
			addGates(child, new Door(), new Door());
		}
		else if (childName == "Wall")
		{
			addWall(child);
		}
		else if (childName == "Switch")
		{
			addSwitch(child);
		}
		else if (childName == "Highlight")
		{
			addHighlight(child);
		}
		else if (childName == "Eraser")
		{
			addEraser(child);
		}
		else if (childName == "Player")
		{
			addPlayer(child);
		}
	}
}

std::vector<int> Notebook::getLineValues(std::string lines)
{
	std::istringstream ss(lines);
	std::string valueString;
	std::vector<int> lineValues;

	while (std::getline(ss, valueString, ','))
		lineValues.push_back(std::stoi(valueString));

	return lineValues;
}

void Notebook::addGates(tinyxml2::XMLElement* element, Gate* gateA, Gate* gateB)
{
	std::vector<int> lineValues = getLineValues(element->Attribute("lines"));

	gateA->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	gateB->setAnchorPoint(cocos2d::Vec2(0.5, 0));

	gateA->linkGate(gateB);
	gateB->linkGate(gateA);

	gateA->setLine(lineValues[0]);
	gateB->setLine(lineValues[1]);
	gateA->setPositionY(_lineHeight * lineValues[0]);
	gateB->setPositionY(_lineHeight * lineValues[1]);

	int draw = element->IntAttribute("draw");

	gateA->setPositionX(draw);
	gateB->setPositionX(draw);

	this->addChild(gateA, 98);
	this->addChild(gateB, 98);
	_gates.push_back(gateA);
	_gates.push_back(gateB);
}

WallColor stringToWallColor(std::string str)
{
	WallColor wallColor;

	if (str == "Black")
		wallColor = WallColor::Black;
	else if (str == "Red")
		wallColor = WallColor::Red;
	else if (str == "Green")
		wallColor = WallColor::Green;
	else if (str == "Blue")
		wallColor = WallColor::Blue;

	return wallColor;
}

void Notebook::addWall(tinyxml2::XMLElement* element)
{
	const char* color = element->Attribute("color");
	std::string colorStr = color != 0 ? color : "Black";

	WallColor wallColor = stringToWallColor(colorStr);

	int draw = element->IntAttribute("draw");
	int line = element->IntAttribute("line");

	Wall* wall = new Wall(wallColor);
	wall->setLine(line);
	wall->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	wall->setPosition(draw, _lineHeight * line);
	this->addChild(wall, 98);
	_walls.push_back(wall);

	const char* key = element->Attribute("key");
	if (key != 0)
		_wallMap[key].push_back(wall);
}

void Notebook::addSwitch(tinyxml2::XMLElement* element)
{
	int draw = element->IntAttribute("draw");
	int line = element->IntAttribute("line");
	std::string key = element->Attribute("key");
	const char* color = element->Attribute("color");

	Switch* sswitch = new Switch(stringToWallColor(color));
	sswitch->setLinkedWalls(_wallMap[key]);
	sswitch->setLine(line);
	sswitch->setPosition(draw, line * _lineHeight + _lineHeight * 0.5);
	this->addChild(sswitch, 98);
	_switches.push_back(sswitch);
}

void Notebook::addHighlight(tinyxml2::XMLElement* element)
{
	int draw = element->IntAttribute("draw");
	int line = element->IntAttribute("line");
	int length = element->IntAttribute("length");

	Highlight* highlight = new Highlight();
	highlight->setLine(line);
	highlight->setAnchorPoint(cocos2d::Vec2(0, 0.5));
	highlight->setPosition(draw, line * _lineHeight + _lineHeight * 0.5);
	highlight->setContentSize(cocos2d::Size(length, highlight->getContentSize().height));
	this->addChild(highlight, 97);
}

void Notebook::addEraser(tinyxml2::XMLElement* element)
{
	int draw = element->IntAttribute("draw");
	int line = element->IntAttribute("line");

	Eraser* eraser = new Eraser();
	eraser->setLine(line);
	eraser->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	eraser->setPosition(draw, line * _lineHeight);
	this->addChild(eraser);
}

void Notebook::addPlayer(tinyxml2::XMLElement* element)
{
	int draw = element->IntAttribute("draw");
	int line = element->IntAttribute("line");

	Player* player = new Player();
	player->setLine(line);
	player->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	player->setPosition(draw, line * _lineHeight);
	this->addChild(player, 99);

	_player = player;
}
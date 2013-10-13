/*
Copyright (C) 2013 Chris Boyce <chris@gitanic.com>

See the LISCENSE.txt file at the top-level directory of 
this distribution and at http://opensource.org/licenses/MIT
*/

#include "C4Interface.h"

#include "LSystemPlugin.h"
#include "LSystemCreatorPage.h"
using namespace C4;

C4::Plugin *ConstructPlugin(void)
{
	return (new LSystemPlugin);
}

LSystemPlugin::LSystemPlugin() :
	c4MenuItem("LSystem",WidgetObserver<LSystemPlugin>(this, &LSystemPlugin::HandleC4MenuItem)){
	ThePluginMgr->AddToolMenuItem(&c4MenuItem); 
}
void LSystemPlugin::HandleC4MenuItem(Widget *menuItem, const WidgetEventData *eventData)
{
	
	Window * generator = new LSystemCreatorPage();
	TheInterfaceMgr->AddWidget(generator);

}
LSystemPlugin::~LSystemPlugin(){}

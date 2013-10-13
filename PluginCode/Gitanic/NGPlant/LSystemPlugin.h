/*
Copyright (C) 2013 Chris Boyce <chris@gitanic.com>

See the LISCENSE.txt file at the top-level directory of 
this distribution and at http://opensource.org/licenses/MIT
*/
#ifndef LSystemPlugin_h
#define LSystemPlugin_h

#include "C4Plugins.h"


extern "C"
{
	C4MODULEEXPORT C4::Plugin *ConstructPlugin(void);
}

namespace C4
{
	class LSystemPlugin : public Plugin
	{
	private:
		MenuItemWidget						c4MenuItem;
		void HandleC4MenuItem(Widget *menuItem, const WidgetEventData *eventData);

	public:
		LSystemPlugin();
		~LSystemPlugin();

		
		const char *GetPluginName(void) const {
			return "LSystem";
		}
	};
}
#endif
#ifndef RUMBA_PANEL_H
#define RUMBA_PANEL_H

#include "Panel.h"

class RumbaPanel : public Panel {
	public:
		RumbaPanel(int x, int y, char* img_path) : Panel(x, y, img_path) { }
		void setCenterPos(Vector<float> new_pos, int radius) { position = (Vector<int>)new_pos - radius; }
};

#endif

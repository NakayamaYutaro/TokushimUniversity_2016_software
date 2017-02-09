#ifndef EQUIPMENT_H

#include "Object.hpp"
#include "../utils/Vector.hpp"

#define EQUIPMENT_H

class Equipment : public Object{
	private:
		int life;
		Vector<int> position;
		int width;
		int height;
	public:
		Equipment(int team_id)
			: position( Vector<int>((team_id%2)*GAME_FIELD_WIDTH+(team_id%2)*(-EQUIPMENT_WIDTH), GAME_FIELD_HEIGHT/2 - EQUIPMENT_HEIGHT/2) ),
				width(EQUIPMENT_WIDTH),
				height(EQUIPMENT_HEIGHT)
				{ resetLife(); }
		void resetLife() { life = DEFAULT_LIFE; }
		Vector<int> getPosition() { return position; }
		int decreaseLife() { life--; return life; }
		int getLife() { return life; }
		void setLife(int new_life) { life = new_life; }
		int getWidth() { return width; }
		int getHeight() { return height; }
		Vector<int>* getAllApexes() {
			Vector<int>* list = new Vector<int>[4];
			list[0] = position;
			list[1] = position + Vector<int>(width, 0);
			list[2] = position + Vector<int>(width, height);
			list[3] = position + Vector<int>(0, height);
			return list;
		}
};

#endif

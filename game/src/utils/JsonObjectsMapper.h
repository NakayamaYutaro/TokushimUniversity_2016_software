#ifndef JSON_OBJECTS_MAPPER_H
#define JSON_OBJECTS_MAPPER_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "./picojson/picojson.h"
#include "./LinkedList.h"
#include "./Tuple.h"
#include "../models/Rumba.h"
#include "../models/RunawayRumba.h"
#include "../models/CustomizedRumba.h"
#include "../models/Equipment.h"

using namespace std;

namespace JsonObjectMapper {

			Tuple<char, picojson::object> parseJsonMsg(string json);

			// ---- methods for client --- //
			string getMsgHandshake();
			// ---- methods for client --- //

			// ---- methods for server --- //
			// get json msg : send each rumba and life of equipment
			string getMsgSendGameState(LinkedList<CustomizedRumba>* roombas, RunawayRumba* roomba, LinkedList<Equipment>* equipments);
			// set from json msg : send each rumba and life of equipment
			void setGameState(picojson::object game_state, LinkedList<CustomizedRumba>* c_roombas, RunawayRumba* r_roomba, LinkedList<Equipment>* equipments);
			// ---- methods for server --- //
}


string JsonObjectMapper::getMsgHandshake() {
		return "{\"cmd\":\"H\"}";
}

string JsonObjectMapper::getMsgSendGameState(LinkedList<CustomizedRumba>* roombas, RunawayRumba* roomba, LinkedList<Equipment>* equipments) {

	ostringstream msg;
	Vector<int> pos = Vector<int>(0,0);
	char tmp[256];
	int i;
	// set location of each roomba
	msg << "{\"cmd\":\"D\", \"roombas\":[ ";
	roombas->resetCurrent();
	for(i = 0; i < roombas->getSize(); i++) {
		pos = (Vector<int>)(roombas->get().getCenterPos());
		sprintf(tmp, "[%d, %d, %d], ", i, pos.getX(), pos.getY());
		msg << tmp;
	}
	pos = (Vector<int>)(roomba->getCenterPos());
	sprintf(tmp, "[%d, %d, %d] ], \"life\":[", i, pos.getX(), pos.getY());
	msg << tmp;
	// set life of each player
	equipments->resetCurrent();
	for(i = 0; i < equipments->getSize(); i++) {
		if(i < equipments->getSize()-1 ) msg << (equipments->get().getLife()) << ", ";
		else msg << equipments->get().getLife();
	}
	msg << "]}";
	return msg.str();
}

Tuple<char, picojson::object> JsonObjectMapper::parseJsonMsg(string json) {

	picojson::value jsonval;
	string err_msg = parse(jsonval, json);
	if(!err_msg.empty()) {
		cerr << err_msg << endl;
		exit(1);
	}

	picojson::object data = jsonval.get<picojson::object>();
	string cmd = data["cmd"].get<string>();
	return Tuple<char, picojson::object>( (cmd.c_str())[0], data );

}

void JsonObjectMapper::setGameState(picojson::object game_state, LinkedList<CustomizedRumba>* c_roombas, RunawayRumba* r_roomba, LinkedList<Equipment>* equipments) {
	picojson::array roomba_data = game_state["roombas"].get<picojson::array>();
	unsigned int i;
	c_roombas->resetCurrent();
	for(i = 0; i < roomba_data.size(); i++) {
		picojson::array params = roomba_data.at(i).get<picojson::array>();
		Rumba* rumba = (i != roomba_data.size()-1) ? (Rumba*)c_roombas->getPtr() : (Rumba*)r_roomba;
		rumba->setCenterPos( Vector<float>( (float)(params.at(1).get<double>()), (float)(params.at(2).get<double>()) ) );
	}
	picojson::array life_data = game_state["life"].get<picojson::array>();
	equipments->resetCurrent();
	for(i = 0; i < life_data.size(); i++) equipments->getPtr()->setLife( (int)(life_data.at(i).get<double>()) );
}

#endif

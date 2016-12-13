#ifndef JSON_OBJECTS_MAPPER_H
#define JSON_OBJECTS_MAPPER_H

#include <iostream>
/*
#include "../utils/picojson/picojson.h"
#include "RunawayRumba.h"
#include "CustomizedRumba.h"
#include "Equipment.h"
#include "../utils/LinkedList.h"
*/
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

/*
class JsonObjectMapper {

	public:
		string getMsgHandshake() {
			string msg;
			return "[\"H\", ]";
		}
		string getMsgSendRumbaPos(LinkedList<CustomizedRumba>* roombas) {
			return "";
		}
		string getMsgSendRumbaPos(RunawayRumba roomba) {
			return "";
		}
		string
	private:
		string convert2Json(RunawayRumba roomba) {
			return "";
		}
		string convert2Json(LinkedList<CustomizedRumba> roombas) {
			return "";
		}
		string convert2Json(LinkedList<Equipment> equipments) {
			return "";
		}
		static string getMyIPAddrss() {
			int fd;
			struct ifreq ifr;
			fd = socket(AF_INET, SOCK_STREAM. 0);
			ifr.ifr_addr.sa.family = AF_INET;
			strcpy(ifr.ifr_name, NETWORK_INTERFACE, IFNAMSIZ-1);
			ioctl(fd, SIOCGIFADDR, &ifr);
			close(fd);
			return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
		}
}
*/

#endif

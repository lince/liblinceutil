/*
 * LoggerXmlParser.cpp
 *
 *  Created on: Jul 20, 2011
 *      Author: caioviel
 */

//#define PARSER_DEBUG

#include "../../include/logger/LoggerXmlParser.h"
#include "../../include/logger/LoggerManager.h"

namespace cpputil {
namespace logger {

LoggerXmlParser::LoggerXmlParser(string xmlFileName) {
	this->xmlFileName = xmlFileName;

	blockedClasses = new set<string>();
	regionalOpt = LoggerManager::USA;
	loggerStyle = LoggerManager::DEFAULT;
	loggerLvl = Logger::INFO;

	protocol = LoggerNetworkStream::UDP;
	ipAddress = "127.0.0.1";
	portNumber = 5004;

	logfileName = "logfile.log";
	writemode = LoggerLogFile::OVERWRITE_FILE;

	colors = NULL;
}

LoggerXmlParser::~LoggerXmlParser() {
	delete blockedClasses;
	//delete colors;
}

LoggerNetworkStream::Protocol LoggerXmlParser::getProtocol() {
	return protocol;
}

LoggerLogFile::WriteMode LoggerXmlParser::getWritemode() {
	return writemode;
}

Logger::LoggerLvl LoggerXmlParser::getLoggerLvl() {
	return loggerLvl;
}

LoggerColor::Color* LoggerXmlParser::getColors() {
	return colors;
}

void LoggerXmlParser::resetDefault() {
	blockedClasses->clear();

	regionalOpt = LoggerManager::USA;
	loggerStyle = LoggerManager::DEFAULT;
	loggerLvl = Logger::INFO;

	protocol = LoggerNetworkStream::UDP;
	ipAddress = "127.0.0.1";
	portNumber = 5004;

	logfileName = "logfile.log";
	writemode = LoggerLogFile::OVERWRITE_FILE;

	if (colors != NULL) {
		delete colors;
		colors = NULL;
	}
}

set<string>* LoggerXmlParser::getBlockedClasses() {
	set<string>* copyList = new set<string>();
	set<string>::iterator it;
	it = blockedClasses->begin();
	while (it != blockedClasses->end() ) {
		copyList->insert(*it);
		it++;
	}
	return copyList;
}

string LoggerXmlParser::getFileName() {
	return logfileName;
}

string LoggerXmlParser::getIpAddress() {
	return ipAddress;
}

LoggerManager::LoggerStyle LoggerXmlParser::getLoggerStyle() {
	return loggerStyle;
}

unsigned short LoggerXmlParser::getPortNumber() {
	return portNumber;
}

LoggerManager::RegionalOpt LoggerXmlParser::getRegional() {
	return regionalOpt;
}

void LoggerXmlParser::parseDocument() {
	bool hadFoundClasses = false;
	bool hadFoundStyle = false;
	string aux;
	try {
		Document doc(xmlFileName);
		doc.LoadFile();

		Element* first = doc.FirstChildElement();
		first->GetValue(&aux);
#ifdef PARSER_DEBUG
		cout << "\tFirstElement=" << aux << endl;
#endif
		if (aux != "LoggerConfig") {
			throw LoggerException(
					"Error during parser xmlFile. Not found root element LoggerConfig.",
					"cpputil::Logger::LoggerXmlParser",
					"void parseDocument()");
		}

		if (first->HasAttribute("level")) {
			string value = first->GetAttribute("level");
			loggerLvl = Logger::stringToLoggerLvl(value);
#ifdef PARSER_DEBUG
			cout <<"\t\tlevel=" << value << endl;
			cout <<"\t\tlvl After been translated= " << Logger::loggerLvlToString(loggerLvl) << endl;
#endif
		}

		if (first->HasAttribute("region")) {
			string value = first->GetAttribute("region");
			regionalOpt = LoggerManager::stringToRegionalOpt(value);
#ifdef PARSER_DEBUG
			cout <<"\t\tregionalOpt= " << value << endl;
			cout <<"\t\tregionOpt After been translated= " << LoggerManager::regionalOptToString(regionalOpt) << endl;
#endif
		}

		ticpp::Iterator< ticpp::Node > child;
		child = child.begin(first);
		while (child != child.end()) {
			string name;

			if (child.Get()->Type() == TiXmlNode::COMMENT) {
				child++;
				continue;
				/* It's a comment... just ignore*/
			}
			child->GetValue(&name);
#ifdef PARSER_DEBUG
			cout <<"\n\tElement name=" << name << endl;
#endif
			if (name == "BlockedClasses" && !hadFoundClasses) {
				hadFoundClasses = true;
				Element* blockedClasses = child->ToElement();
				parseBlockedClasses(blockedClasses);

			} else if (name == "Style" && !hadFoundStyle) {
				hadFoundStyle = true;
				Element* style = child->ToElement();
				if (style->HasAttribute("name")) {
					string valeuAttName = style->GetAttribute("name");
#ifdef PARSER_DEBUG
					cout <<"\t\tStyle name=" << valeuAttName << endl;
#endif

					if (valeuAttName == "default") {
						parseDefault(style);
					} else if (valeuAttName == "networkstream") {
						parseNetworkStream(style);
					} else if (valeuAttName == "logfile") {
						this->parseLogFile(style);
					} else if (valeuAttName == "color") {
						parseColor(style);
					} else if (valeuAttName == "multilogger") {
						//TODO: Implementar o multilogger
					} else {
						throw LoggerException(
								"Error during parser xmlFile. A invalid style name specified.",
								"cpputil::Logger::LoggerXmlParser",
								"void parseDocument()");
					}
				} else {
					throw LoggerException(
							"Error during parser xmlFile. Name attbribute was no specified in Style.",
							"cpputil::Logger::LoggerXmlParser",
							"void parseDocument()");
				}
			} else {
				throw LoggerException(
						"Error during parser xmlFile. A invalid or duplicated element was found.",
						"cpputil::Logger::LoggerXmlParser",
						"void parseDocument()");
			}
			child++;
		}

	} catch (ticpp::Exception& ex) {
		cerr << ex.what() << endl;
		resetDefault();
	} catch (LoggerException& ex) {
		cerr << ex.what();
		resetDefault();
	}
}

void LoggerXmlParser::parseBlockedClasses(Element* blockedClasses) {
	ticpp::Iterator< ticpp::Node > child;
	child = child.begin(blockedClasses);
	while (child != child.end()) {
		string name;
		string value;

		if (child.Get()->Type() == TiXmlNode::COMMENT) {
			child++;
			continue;
			/* It's a comment... just ignore*/
		}

		child->GetValue(&name);
		if (name == "class") {
			child->ToElement()->GetText(&value);
#ifdef PARSER_DEBUG
			cout << "\t\t\tclassName= " << value << endl;
#endif
			this->blockedClasses->insert(value);
		} else {
			throw LoggerException(
					"Error during parser xmlFile. A invalid element was found in a BlockedClasses.",
					"cpputil::Logger::LoggerXmlParser",
					"void parseBlockedClasses(Element*)");
		}
		child++;
	}
}

void LoggerXmlParser::parseNetworkStream(Element* style) {
	this->loggerStyle = LoggerManager::NETWORKSTREAM;

	ticpp::Iterator< ticpp::Node > child;
	child = child.begin(style);
	while (child != child.end()) {
		Element* elem;
		string nameElem;
		string nameAtt;
		string valueStr;
		int valueInt;

		if (child.Get()->Type() == TiXmlNode::COMMENT) {
			child++;
			continue;
			/* It's a comment... just ignore*/
		}

		child->GetValue(&nameElem);
		if (nameElem != "styleParam") {
			throw LoggerException(
					"Error during parser xmlFile. A invalid element was found in a Style.",
					"cpputil::Logger::LoggerXmlParser",
					"void parseNetworkStream(Element*)");
		}

		elem = child->ToElement();
		nameAtt = elem->GetAttribute("name");
		if (nameAtt == "protocol") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\tprotocol= " << valueStr << endl;
#endif
			if (valueStr == "udp") {
				protocol = LoggerNetworkStream::UDP;
			} else if (valueStr == "tcp") {
				protocol = LoggerNetworkStream::TCP;
			} else {
				throw LoggerException(
						"Error during parser xmlFile. A invalid network protocol was specified.",
						"cpputil::Logger::LoggerXmlParser",
						"void parseNetworkStream(Element*)");
			}
		} else 	if (nameAtt == "ipAddress") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\tipAddress= " << valueStr << endl;
#endif
			ipAddress = valueStr;
		} else 	if (nameAtt == "portNumber") {
			elem->GetText(&valueInt);
#ifdef PARSER_DEBUG
			cout << "\t\t\tportNumber= " << valueInt << endl;
#endif
			portNumber = valueInt;
		} else {
			throw LoggerException(
					"Error during parser xmlFile. A invalid parameter for networkstream style was found.",
					"cpputil::Logger::LoggerXmlParser",
					"void parseNetworkStream(Element*)");
		}
		child++;
	}
}

void LoggerXmlParser::parseColor(Element* style) {
	this->loggerStyle = LoggerManager::COLOR;

	colors = LoggerColor::getDefaultColors();

	ticpp::Iterator< ticpp::Node > child;
	child = child.begin(style);
	while (child != child.end()) {
		Element* elem;
		string nameElem;
		string nameAtt;
		string valueStr;
		int valueInt;

		if (child.Get()->Type() == TiXmlNode::COMMENT) {
			child++;
			continue;
			/* It's a comment... just ignore*/
		}

		child->GetValue(&nameElem);
		if (nameElem != "styleParam") {
			throw LoggerException(
					"Error during parser xmlFile. A invalid element was found in a Style.",
					"cpputil::Logger::LoggerXmlParser",
					"void parseNetworkStream(Element*)");
		}

		elem = child->ToElement();
		nameAtt = elem->GetAttribute("name");
		if (nameAtt == "traceColor") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\ttraceColor= " << valueStr << endl;
#endif
			colors[(int) Logger::TRACE] = LoggerColor::stringToColor(valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\tcolor after translate= " << LoggerColor::colorToString(colors[(int) Logger::TRACE]) << endl;
#endif
		} else if (nameAtt == "debugColor") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\tdebugColor= " << valueStr << endl;
#endif
			colors[(int) Logger::DEBUG] = LoggerColor::stringToColor(valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\tdebug after translate= " << LoggerColor::colorToString(colors[(int) Logger::DEBUG]) << endl;
#endif
		} else 	if (nameAtt == "infoColor") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\tinfoColor= " << valueStr << endl;
#endif
			colors[(int) Logger::INFO] = LoggerColor::stringToColor(valueStr);
		} else 	if (nameAtt == "warningColor") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\twarningColor= " << valueStr << endl;
#endif
			colors[(int) Logger::WARNING] = LoggerColor::stringToColor(valueStr);
		} else 	if (nameAtt == "errorColor") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\terrorColor= " << valueStr << endl;
#endif
			colors[(int) Logger::ERROR] = LoggerColor::stringToColor(valueStr);
		} else 	if (nameAtt == "fatalColor") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\tfatalColor= " << valueStr << endl;
#endif
			colors[(int) Logger::FATAL] = LoggerColor::stringToColor(valueStr);
		} else {
			throw LoggerException(
					"Error during parser xmlFile. A invalid parameter for networkstream style was found.",
					"cpputil::Logger::LoggerXmlParser",
					"void parseNetworkStream(Element*)");
		}
		child++;
	}

}

void LoggerXmlParser::parseLogFile(Element* style) {
	this->loggerStyle = LoggerManager::LOGFILE;

	ticpp::Iterator< ticpp::Node > child;
	child = child.begin(style);
	while (child != child.end()) {
		Element* elem;
		string nameElem;
		string nameAtt;
		string valueStr;

		if (child.Get()->Type() == TiXmlNode::COMMENT) {
			child++;
			continue;
			/* It's a comment... just ignore*/
		}

		child->GetValue(&nameElem);
		if (nameElem != "styleParam") {
			throw LoggerException(
					"Error during parser xmlFile. A invalid element was found in a Style.",
					"cpputil::Logger::LoggerXmlParser",
					"void parseLogFile(Element*)");
		}

		elem = child->ToElement();
		nameAtt = elem->GetAttribute("name");
		if (nameAtt == "writemode") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\twritemode= " << valueStr << endl;
#endif
			if (valueStr == "overwrite") {
				writemode = LoggerLogFile::OVERWRITE_FILE;
			} else if (valueStr == "append") {
				writemode = LoggerLogFile::APPEND_FILE;
			} else {
				throw LoggerException(
						"Error during parser xmlFile. A invalid writemode was specified.",
						"cpputil::Logger::LoggerXmlParser",
						"void parseLogFile(Element*)");
			}
		} else 	if (nameAtt == "filename") {
			elem->GetText(&valueStr);
#ifdef PARSER_DEBUG
			cout << "\t\t\tfilename= " << valueStr << endl;
#endif
			logfileName = valueStr;
		} else {
			throw LoggerException(
					"Error during parser xmlFile. A invalid parameter for logfile style was found.",
					"cpputil::Logger::LoggerXmlParser",
					"void parseLogFile(Element*)");
		}
		child++;
	}

}

void LoggerXmlParser::parseDefault(Element* style){
	this->loggerStyle = LoggerManager::DEFAULT;
}

} /* namespace logger */
} /* namespace cpputil */

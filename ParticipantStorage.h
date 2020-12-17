#pragma once

#include <vector>
#include <string>
#include "Participant.h"

using namespace std;

class ParticipantStorage
{
private:
	vector<Participant>* records;

	vector<Participant>* readRecordsFile();
	void writeRecordFile();
	void writeToEndRecordFile(Participant record);
	
public:
	ParticipantStorage();

	void addRecord(string name, int year, string country, string instrument, int place);
	void addRecord(Participant* record);
	void editRecord(int i, Participant* editedRecord);
	void deleteRecord(int i);

	vector<Participant>* findRecordByName(string name);
	vector<Participant>* findRecordByYear(int year);
	vector<Participant>* findRecordByPlace(int place);

	void sortRecordsByName();
	void sortRecordsByYear();
	void sortRecordsByPlace();

	void clearAll();

	vector<Participant>* getRecords();
};

bool PlaceComparator(Participant participant_a, Participant participant_b);
bool YearDescComparator(Participant participant_a, Participant participant_b);
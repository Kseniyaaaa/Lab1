#include "ParticipantStorage.h"
#include "Participant.h"
#include "validation.h"
#include "ConsoleApp.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const string FILE_OF_RECORDS = "data.txt";

ParticipantStorage::ParticipantStorage()
{
    this->records = this->readRecordsFile();
}


vector<Participant>* ParticipantStorage::readRecordsFile()
{
	vector<Participant>* records = new vector<Participant>();

	ifstream fin(FILE_OF_RECORDS, ios::in);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			Participant* record = new Participant;
			getline(fin, record->name);
			getline(fin, record->country);
			fin >> record->year;
			fin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			getline(fin, record->instrument);
			fin >> record->place;
			fin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			records->push_back(*record);
		}
	}
	fin.close();
	return records;
}


void ParticipantStorage::writeRecordFile()
{
	ofstream fout(FILE_OF_RECORDS, ios::out);
	for (int i = 0; i < records->size(); i++)
	{
		fout << records->at(i).name << endl;
		fout << records->at(i).country << endl;
		fout << records->at(i).year << endl;
		fout << records->at(i).instrument << endl;
		fout << records->at(i).place;
		if (i < records->size() - 1)
		{
			fout << endl;
		}
	}
	fout.close();
}


void ParticipantStorage::writeToEndRecordFile(Participant record)
{
	ofstream fadd(FILE_OF_RECORDS, ios::app);
	fadd << endl
		<< record.name << " "
		<< record.country << " "
		<< record.year << " "
		<< record.instrument << " "
		<< record.place;
	fadd.close();
}


void ParticipantStorage::addRecord(string name, int year, string country, string instrument, int place)
{
	Participant* record = new Participant;
	record->name = name;
	record->country = country;
	record->year = year;
	record->instrument = instrument;
	record->place = place;

	this->records->push_back(*record);
	writeToEndRecordFile(*record);
}


void ParticipantStorage::addRecord(Participant* record)
{
	this->records->push_back(*record);
	writeToEndRecordFile(*record);
}


void ParticipantStorage::editRecord(int i, Participant* editedRecord)
{
	this->deleteRecord(i);
	this->addRecord(editedRecord);
	writeRecordFile();
}


void ParticipantStorage::deleteRecord(int i)
{
	vector<Participant>* records = getRecords();

	if (i >= 0 && i < records->size())
	{
		records->erase(records->begin() + i);
		writeRecordFile();
		return;
	}

	throw "Такого участника нет.";
}


Participant* ParticipantStorage::findRecordByName(string name)
{
	for (int i = 0; i < records->size(); i++)
	{
		if (records->at(i).name.find(name) != string::npos)
		{ 
			return &records->at(i);
		}
	}

	return NULL;
}


Participant* ParticipantStorage::findRecordByYear(int year)
{
	for (int i = 0; i < records->size(); i++)
	{
		if (year == records->at(i).year)
		{
			return &records->at(i);
		}
	}

	return NULL;
}


Participant* ParticipantStorage::findRecordByPlace(int place)
{
	for (int i = 0; i < records->size(); i++)
	{
		if (place == records->at(i).place)
		{
			return &records->at(i);
		}
	}

	return NULL;
}


bool NameComparator(Participant participant_a, Participant participant_b)
{
	return participant_a.name < participant_b.name;
}


void ParticipantStorage::sortRecordsByName()
{
	sort(records->begin(), records->end(), NameComparator);
}


bool YearComparator(Participant participant_a, Participant participant_b)
{
    return participant_a.name < participant_b.name;
}


void ParticipantStorage::sortRecordsByYear()
{
	sort(records->begin(), records->end(), YearDescComparator);
}


bool PlaceComparator(Participant participant_a, Participant participant_b)
{
	return participant_a.name > participant_b.name;
}


void ParticipantStorage::sortRecordsByPlace()
{
	sort(records->begin(), records->end(), PlaceComparator);
}


bool YearDescComparator(Participant participant_a, Participant participant_b)
{
	return participant_a.year > participant_b.year;
}


void ParticipantStorage::clearAll()
{
	records->clear();
	writeRecordFile();
}


vector<Participant>* ParticipantStorage::getRecords()
{
	return this->records;
}
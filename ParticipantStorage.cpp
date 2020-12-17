#include "ParticipantStorage.h"
#include "Participant.h"
#include "validation.h"
#include "ConsoleApp.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const string FILE_OF_RECORDS = "records.txt";

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
	fadd << record.name << " "
		<< record.country << " "
		<< record.year << " "
		<< record.instrument << " "
		<< record.place;
	fadd << endl;
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
	if (i >= 0 && i < records->size())
	{
		records->erase(records->begin() + i);
		writeRecordFile();
		return;
	}

	throw "Такого участника нет.";
}


vector<Participant>* ParticipantStorage::findRecordByName(string name)
{
	vector<Participant>* r_vector = new vector<Participant>;

	for (int i = 0; i < records->size(); i++)
	{
		if (records->at(i).name.find(name) != string::npos)
		{ 
			r_vector->push_back(records->at(i));
		}
	}

	if (r_vector->size() == 0) {
		return NULL;
	}

	return r_vector;
}


vector<Participant>* ParticipantStorage::findRecordByYear(int year)
{
	vector<Participant>* r_vector = new vector<Participant>;

	for (int i = 0; i < records->size(); i++)
	{
		if (year == records->at(i).year)
		{
			r_vector->push_back(records->at(i));
		}
	}

	if (r_vector->size() == 0) {
		return NULL;
	}

	return r_vector;
}


vector<Participant>* ParticipantStorage::findRecordByPlace(int place)
{
	vector<Participant>* r_vector = new vector<Participant>();

	for (int i = 0; i < records->size(); i++)
	{
		if (place == records->at(i).place)
		{ 
			r_vector->push_back(records->at(i));
		}
	}

	if (r_vector->size() == 0) {
		return NULL;
	}

	return r_vector;
}


void ParticipantStorage::sortRecordsByName()
{
	for (int i = 0; i < records->size() - 1; i++)
	{
		for (int j = i + 1; j < records->size(); j++)
		{
			if (records->at(i).name > records->at(j).name)
			{
				swap(records->at(i), records->at(j));
			}
		}
	}
}


void ParticipantStorage::sortRecordsByYear()
{
	for (int i = 0; i < records->size() - 1; i++)
	{
		for (int j = i + 1; j < records->size(); j++)
		{
			if (records->at(i).year > records->at(j).year)
			{
				swap(records->at(i), records->at(j));
			}
		}
	}
}


bool PlaceComparator(Participant participant_a, Participant participant_b)
{
	return participant_a.place < participant_b.place;
}


void ParticipantStorage::sortRecordsByPlace()
{
	for (int i = 0; i < records->size() - 1; i++)
	{
		for (int j = i + 1; j < records->size(); j++)
		{
			if (records->at(i).place > records->at(j).place)
			{
				swap(records->at(i), records->at(j));
			}
		}
	}
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
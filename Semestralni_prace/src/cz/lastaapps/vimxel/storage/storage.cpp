#include "storage.hpp"

#include <filesystem>
#include <ios>
#include <sstream>

#include "../log.hpp"
#include "../table/coordinate.hpp"
#include "../table/table.hpp"

namespace cz::lastaapps::vimxel::storage {

void Storage::saveData(shared_ptr<table::Table> table, const string& path) {
	auto size = table->tableSize();
	ofstream file;
	openFileForWrite(path, file);
	for (size_t y = 0; y < size.y(); y++) {
		bool isFirst = true;
		for (size_t x = 0; x < size.x(); x++) {
			if (isFirst)
				isFirst = false;
			else
				file << DELIMITER;
			const table::Cell& cell = table->getCell(table::Coordinates(x, y));
			file << escapeText(cell.getContent());
		}
		file << LINE_DELIMITER;
	}
	// drop latests \n
	file.close();
	auto filePath = filesystem::path(path);
	size_t fileSize = file_size(filePath);
	if (fileSize != 0)
		resize_file(filePath, fileSize - 1);
}

void Storage::exportData(shared_ptr<table::Table> table, const string& path) {
	auto size = table->tableSize();
	ofstream file;
	openFileForWrite(path, file);
	for (size_t y = 0; y < size.y(); y++) {
		bool isFirst = true;
		for (size_t x = 0; x < size.x(); x++) {
			if (isFirst)
				isFirst = false;
			else
				file << DELIMITER;
			const table::Cell& cell = table->getCell(table::Coordinates(x, y));
			file << escapeText(cell.getValue());
		}
		file << LINE_DELIMITER;
	}
	// drop latests \n
	file.close();
	auto filePath = filesystem::path(path);
	size_t fileSize = file_size(filePath);
	if (fileSize != 0)
		resize_file(filePath, fileSize - 1);
}

void Storage::loadData(const string& path, shared_ptr<table::Table>& table) {
	ifstream file;
	openFileForRead(path, file);
	for (size_t y = 0; file; y++) {
		for (size_t x = 0; file; x++) {
			bool lineEnd;
			string cellContent = move(importText(file, lineEnd));
			table->updateCell(table::Coordinates(x, y), cellContent);
			if (lineEnd) break;
		}
	}
	table -> clearChanged();
}

string Storage::escapeText(const string& str) {
	bool containsDelim = false;
	for (const char c : str)
		if (c == DELIMITER || c == LINE_DELIMITER || c == ENCAPSULATOR) {
			containsDelim = true;
			break;
		}
	if (!containsDelim) return str;
	stringstream stream;
	stream << ENCAPSULATOR;
	for (const char c : str)
		if (c == ENCAPSULATOR)
			stream << ENCAPSULATOR << ENCAPSULATOR;
		else
			stream << c;
	stream << ENCAPSULATOR;
	return stream.str();
}

string Storage::importText(const string& str) {
	bool tmp;
	auto stream = istringstream(str);
	return importText(stream, tmp);
}
string Storage::importText(istream& stream, bool& lineEnd) {
	stringstream out;
	char c;
	stream >> noskipws;
	stream >> c;
	if (!stream) return "";
	bool isEncapsulated = c == ENCAPSULATOR;
	if (!isEncapsulated) {
		stream.unget();
		while (stream >> c) {
			if (c == DELIMITER || c == LINE_DELIMITER) {
				lineEnd = c == LINE_DELIMITER;
				break;
			} else {
				out << c;
			}
		}
	} else {
		bool inEscape = false;
		while (stream >> c) {
			if (c == DELIMITER || c == LINE_DELIMITER) {
				if (!inEscape) {
					out << c;
				} else {
					lineEnd = c == LINE_DELIMITER;
					break;
				}
			} else if (c == ENCAPSULATOR) {
				if (inEscape)
					out << c;
				inEscape = !inEscape;
			} else {
				if (!inEscape)
					out << c;
				else
					throw SingleEncapsulator();
			}
		}
		if (stream.eof() && !inEscape) throw InvalidEncapsulation();
	}
	if (stream.eof()) lineEnd = true;
	return out.str();
}

void Storage::openFileForWrite(const string& str, ofstream& stream) {
	stream = ofstream(str, ios::out | ios::trunc);
}
void Storage::openFileForRead(const string& str, ifstream& stream) {
	stream = ifstream(str, ios::in);
}
}  // namespace cz::lastaapps::vimxel::storage

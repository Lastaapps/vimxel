#include "storage.hpp"

#include <ios>
#include <sstream>

#include "../table/cell.hpp"
#include "../table/coordinate.hpp"
#include "../table/table.hpp"

namespace cz::lastaapps::vimxel::storage {

void Storage::saveData(shared_ptr<table::Table> table, const string& path) {
	auto size = table->tableSize();
	fstream file;
	openFile(path, file);
	for (size_t x = 0; x < size.x(); x++) {
		bool isFirst = true;
		for (size_t y = 0; y < size.y(); y++) {
			if (isFirst)
				isFirst = false;
			else
				file << ';';
			const table::Cell& cell = table->getCell(table::Coordinates(x, y));
			file << escapeText(cell.getContent());
		}
		file << '\n';
	}
}

void Storage::exportData(shared_ptr<table::Table> table, const string& path) {
	// TODO update after expression evaulation is done
	saveData(table, path);
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
	auto stream = istringstream(str);
	return importText(stream);
}
string Storage::importText(istream& stream) {
	stringstream out;
	char c;
	stream >> noskipws;
	stream >> c;
	if (!stream) return "";
	bool isEncapsulated = c == ENCAPSULATOR;
	if (!isEncapsulated) {
		stream.unget();
		while (stream >> c) {
			if (c == DELIMITER || c == LINE_DELIMITER)
				break;
			else
				out << c;
		}
	} else {
		bool inEscape = false;
		while (stream >> c) {
			if (c == DELIMITER || c == LINE_DELIMITER) {
				if (!inEscape)
					out << c;
				else break;
			} else if (c == ENCAPSULATOR) {
				if (inEscape)
					out << c;
				inEscape = !inEscape;
			} else {
				if (!inEscape)
					out << c;
				else throw SingleEncapsulator();
			}
		}
		if (stream.eof() && !inEscape) throw InvalidEncapsulation();
	}
	return out.str();
}

void Storage::openFile(const string& str, fstream& stream) {
	stream = fstream(str, ios::in | ios::out | ios::trunc);
}
}  // namespace cz::lastaapps::vimxel::storage

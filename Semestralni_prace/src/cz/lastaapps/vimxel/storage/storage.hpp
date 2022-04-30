#ifndef H_STORAGE
#define H_STORAGE
#include <memory>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "../table/table.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::storage {

class Storage final {
    Storage() = delete;

   public:
	static void saveData(shared_ptr<table::Table> table, const string & path);
    static void exportData(shared_ptr<table::Table> table, const string & path);
    static void loadData(const string & path, shared_ptr<table::Table>& table);

   private:
	static constexpr char DELIMITER = ';';
	static constexpr char LINE_DELIMITER = '\n';
	static constexpr char ENCAPSULATOR = '"';
	static void openFileForWrite(const string & str, ofstream & stream);
	static void openFileForRead(const string & str, ifstream & stream);
    static string escapeText(const string & str);
	static string importText(const string& str);
    static string importText(istream & stream, bool & lineEnd);

	friend class StorageTester;
    };

struct InvalidEncapsulation final : invalid_argument {
    InvalidEncapsulation() : invalid_argument("Invalid encapsulation while reading a file") {}
};
struct SingleEncapsulator final : invalid_argument {
    SingleEncapsulator() : invalid_argument("Single encapsulator found while reading a file") {}
};

}
#endif
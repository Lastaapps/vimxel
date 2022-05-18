#ifndef H_STORAGE
#define H_STORAGE
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "../table/table.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;
namespace fs = std::filesystem;

namespace cz::lastaapps::vimxel::storage {

/**
 * @brief Manages all the IO operations
 */
class Storage final {
	Storage() = delete;

   public:
	/**
	 * @brief Saves data in way they can be loaded next time, cell contents are saved
	 *
	 * @param table data to save
	 * @param path file to save data in
	 * @throw exception when writing file fails
	 */
	static void saveData(shared_ptr<table::Table> table, const fs::path& path);
	/**
	 * @brief Exports data in CSV format, these data shouldn't be loaded next time
	 *
	 * @param table data to export
	 * @param path file to export data in
	 * @throw exception when writing file fails
	 */
	static void exportData(shared_ptr<table::Table> table, const fs::path& path);
	/**
	 * @brief Loads data from file, they should be saved before by saveData() function
	 *
	 * @param table data storage to save cells into, is always cleared even if loading fails
	 * @param path file to read data from
	 * @throw exception when reading fails because of IO or because of malformed data
	 */
	static void loadData(shared_ptr<table::Table>& table, const fs::path& path);

   private:
	// used with CVS escaping
	static constexpr char DELIMITER = ';';
	static constexpr char LINE_DELIMITER = '\n';
	static constexpr char ENCAPSULATOR = '"';

	/**
	 * @brief Creates output stream
	 *
	 * @param path file to file open
	 * @param stream place to assign stream to
	 */
	static void openFileForWrite(const fs::path& path, ofstream& stream);
	/**
	 * @brief Creates input file stream
	 *
	 * @param path file to open
	 * @param stream place to assign stream to
	 */
	static void openFileForRead(const fs::path& path, ifstream& stream);

	/**
	 * @brief Escapes text if needed to prevent problems with delimiter in text
	 *
	 * @param str text to escape
	 * @return excaped text
	 */
	static string escapeText(const string& str);
	/**
	 * This is just a wrapper for importText(istream&, lineEnd)
	 */
	static string importText(const string& str);
	/**
	 * @brief Does inverse operation for escapeText(), converts stream into normal expected data, just 1 cell per call
	 *
	 * @param stream stream to read data from
	 * @param lineEnd is set to true if line end was hit, if ; was hit, false is set
	 * @return unescaped content of a cell
	 */
	static string importText(istream& stream, bool& lineEnd);

	// ha ha, my hidden tests
	friend class StorageTester;
};

/**
 * @brief File is wrongly encapsulated
 */
struct InvalidEncapsulation final : invalid_argument {
	InvalidEncapsulation() : invalid_argument("Invalid encapsulation while reading a file") {}
};
/**
 * @brief File is wrongly encapsulated, there is missing closing element
 */
struct SingleEncapsulator final : invalid_argument {
	SingleEncapsulator() : invalid_argument("Single encapsulator found while reading a file") {}
};

}  // namespace cz::lastaapps::vimxel::storage
#endif
#ifndef H_PARSER
#define H_PARSER
#include <ncurses.h>

#include <memory>
#include <string>
#include <list>

#include "vimContract.hpp"
#include "parserResult.hpp"
#include "../display/state.hpp"
#include "../table/table.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
class Parser final {
	shared_ptr<display::State> mDisplayState;
	shared_ptr<display::StateCallback> mDisplayStateCallback;
	shared_ptr<table::Table> mTable;
	list<shared_ptr<VimContract>> mContracts;

	const vector<string> mArgs;
	table::Coordinates mPos;

	struct VimStateCallback final : public display::StateCallback {
		Parser* mParent;
		VimStateCallback(Parser* parent) : mParent(parent){};
		void onUpdatePos(const table::Coordinates& pos) override;
		void onUpdateViewPort(const table::Coordinates&) override {}
	};

   public:
	Parser(
	    shared_ptr<display::State> state,
	    shared_ptr<table::Table> table,
	    const vector<string> args);
	ParserResult handleKeyBoard();

	shared_ptr<VimContract> createContract();

   private:
	void setPos(const table::Coordinates& coord);
	void notifyContracts(const VimInfo& info);
};
}  // namespace cz::lastaapps::vimxel::vim

#endif
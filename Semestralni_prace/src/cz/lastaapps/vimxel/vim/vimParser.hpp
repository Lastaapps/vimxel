#ifndef H_PARSER
#define H_PARSER
#include <ncurses.h>

#include <memory>
#include <string>
#include <list>

#include "normalParser.hpp"
#include "insertParser.hpp"
#include "commandParser.hpp"
#include "errorParser.hpp"
#include "vimContract.hpp"
#include "parserResult.hpp"
#include "vimState.hpp"
#include "../display/state.hpp"
#include "../table/table.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
class VimParser final {
	VimState mState;
	Mode mMode = Mode::NORMAL;

	shared_ptr<display::StateCallback> mDisplayStateCallback;
	list<shared_ptr<VimContract>> mContracts;

	NormalParser normalParser = NormalParser(&mState);
	InsertParser insertParser = InsertParser(&mState);
	CommandParser commandParser = CommandParser(&mState);
	ErrorParser errorParser = ErrorParser(&mState);

	struct VimStateCallback final : public display::StateCallback {
		VimParser* mParent;
		VimStateCallback(VimParser* parent) : mParent(parent){};
		void onUpdatePos(const table::Coordinates& pos) override;
		void onUpdateViewPort(const table::Coordinates& viewPort) override;
	};

   public:
	VimParser(
	    shared_ptr<display::State> state,
	    shared_ptr<table::Table> table,
	    const string& filename);
	ParserResult handleKeyBoard();

	shared_ptr<VimContract> createContract();

   private:
	AbsParser& getParser();
	void setPos(const table::Coordinates& coord);
	void setViewPort(const table::Coordinates& coord);
	void notifyContracts(const VimInfo& info);
	void updateInfo();
	void unknowsInfo();
	void errorInfo();
};
}  // namespace cz::lastaapps::vimxel::vim

#endif
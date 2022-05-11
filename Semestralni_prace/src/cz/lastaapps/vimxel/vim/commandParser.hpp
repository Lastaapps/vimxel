#ifndef H_COMMAND_PARSER
#define H_COMMAND_PARSER
#include "absParser.hpp"
#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
using Res = vim::ParserResult;

class CommandParser final : public AbsParser {
   private:
	string mCommand = "";
	VimState* mState;

   public:
	CommandParser(VimState* state);
	ParserResult handleKey(Mode& outMode) override;
	pair<string, size_t> getTextAndPosition() override;

   private:
	Res handleCommand(Mode& outMode);
	Res tryQuitAndWrite(Mode& outMode);
	Res tryOpenFile(Mode& outMode);
	Res tryExportFile(Mode& outMode);
	Res tryJump(Mode& outMode);
};
}  // namespace cz::lastaapps::vimxel::vim

#endif
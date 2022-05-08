#include "insertParser.hpp"

#include <ncurses.h>

#include "../log.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

InsertParser::InsertParser(VimState* state)
    : mState(state) {}

ParserResult InsertParser::handleKey(Mode& outMode) {
	if (checkLoad()) return Res::UPDATE;

	int ch = getch();
	if (ch == ERR) return Res::NOPE;

	switch (ch) {
	case 27: {  // ESC
		mText = "";
		mCursor = (size_t)-1;
		outMode = Mode::NORMAL;
		return Res::UPDATE;
	}
	case KEY_ENTER:
	case '\n': {  // ENTER
		saveContent();
		mText = "";
		mCursor = (size_t)-1;
		outMode = Mode::NORMAL;
		return Res::UPDATE;
	}
	case KEY_BACKSPACE: {
		if (!mText.empty()) {
			if (mCursor != 0) {
				mText.erase(mText.begin() + mCursor - 1);
				mCursor--;
			} else
				mText.erase(mText.begin());
		}
		return Res::UPDATE;
	}
	case KEY_LEFT:{
		if (mCursor != 0) mCursor --;
		return Res::UPDATE;
	}
	case KEY_RIGHT:{
		if (mCursor < mText.length()) mCursor ++;
		return Res::UPDATE;
	}
	case KEY_UP:{
		mCursor = 0;
		return Res::UPDATE;
	}
	case KEY_DOWN:{
		mCursor = mText.length();
		return Res::UPDATE;
	}
	}
	if (' ' <= ch && ch <= '~') {
		mText.insert(mText.begin() + mCursor, ch);
		mCursor++;
		return Res::UPDATE;
	}
	return Res::NOPE;
}

void InsertParser::saveContent() {
	if (mText.empty())
		mState->mTable->updateCell(mPos, "");
	else
		mState->mTable->updateCell(mPos, mText);
}

bool InsertParser::checkLoad() {
	if (mCursor == (size_t)-1) {
		mPos = mState->mPos;
		mText = mState->mTable->getCell(mPos).getContent();
		mCursor = mText.length();
		return true;
	}
	return false;
}

pair<string, size_t> InsertParser::getTextAndPosition() {
	return make_pair(mText, mCursor);
}
}  // namespace cz::lastaapps::vimxel::vim

#ifndef H_PARSER_RESULT
#define H_PARSER_RESULT

namespace cz::lastaapps::vimxel::vim {
enum class ParserResult {
    UNKNOWN,
    ERROR,
    NOPE,
    UPDATE,
    ACCEPTED,
    QUIT,
};
}

#endif
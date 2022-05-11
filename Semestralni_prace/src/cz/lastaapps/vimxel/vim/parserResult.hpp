#ifndef H_PARSER_RESULT
#define H_PARSER_RESULT

namespace cz::lastaapps::vimxel::vim {
enum class ParserResult {
    UNKNOWN,
    NOPE,
    UPDATE,
    ACCEPTED,
    QUIT,
};
}

#endif
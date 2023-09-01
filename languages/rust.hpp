constexpr auto rust_block_comment = recursive([](auto rust_block_comment) {
	return sequence(
		"/*",
		repetition(choice(
			rust_block_comment,
			but("*/")
		)),
		optional("*/")
	);
});

constexpr auto rust_syntax = repetition(choice(
	// comments
	highlight(Style::COMMENT, choice(
		rust_block_comment,
		sequence("//", repetition(but('\n')))
	)),
	// literals
	highlight(Style::WORD, highlight(Style::LITERAL, c_keywords(
		"false",
		"true"
	))),
	// keywords
	highlight(Style::WORD, highlight(Style::KEYWORD, c_keywords(
		"let",
		"mut",
		"if",
		"else",
		"while",
		"for",
		"in",
		"loop",
		"match",
		"break",
		"continue",
		"return",
		"fn",
		"struct",
		"enum",
		"trait",
		"type",
		"impl",
		"where",
		"pub",
		"use",
		"mod"
	))),
	// types
	highlight(Style::WORD, highlight(Style::TYPE, c_keywords(
		"bool",
		"char",
		sequence(
			choice('u', 'i'),
			choice("8", "16", "32", "64", "128", "size")
		),
		sequence('f', choice("32", "64")),
		"str"
	))),
	// identifiers
	highlight(Style::WORD, c_identifier),
	any_char()
));

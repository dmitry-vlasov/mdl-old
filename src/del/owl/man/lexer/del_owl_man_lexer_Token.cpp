/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_lexer_Token.cpp                              */
/* Description:     manchester OWL tokens                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace del {
namespace owl {
namespace man {
namespace lexer {

	/********************************
	 *		Public static attributes
	 ********************************/

	const Token Token :: unknown_ (UNKNOWN, "unknown");
	const Token Token :: namespace_ (NAMESPACE, "Namespace:");
	const Token Token :: ontology_ (ONTOLOGY, "Ontology:");
	const Token Token :: annotations_ (ANNOTATIONS, "Annotations:");
	const Token Token :: object_property_ (OBJECT_PROPERTY, "ObjectProperty:");
	const Token Token :: label_ (LABEL, "label");
	const Token Token :: characteristics_ (CHARACTERISTICS, "Characteristics");

	const Token Token :: class_ (CLASS, "Class:");
	const Token Token :: subclass_of_ (SUBCLASS_OF, "SubClassOf:");
	const Token Token :: equivalent_to_ (EQUIVALENT_TO, "EquivalentTo:");
	const Token Token :: some_ (SOME, "some");
	const Token Token :: and_ (AND, "and");
	const Token Token :: owl_ (OWL, "owl");
	const Token Token :: thing_ (THING, "owl:Thing");

	const Token Token :: colon_ (COLON, ":");
	const Token Token :: comma_ (COMMA, ",");
	const Token Token :: quotation_ (QUOTATION, "\"");

	const Token Token :: leftAngle_ (LEFT_ANGLE, "<");
	const Token Token :: rightAngle_ (RIGHT_ANGLE, ">");
	const Token Token :: openBracket_ (OPEN_BRACKET, "(");
	const Token Token :: closeBracket_ (CLOSE_BRACKET, ")");

	const Token Token :: name_ (NAME, "<name>");
	const Token Token :: string_ (NAME, "<string>");
	const Token Token :: line_ (NAME, "<line>");

	const Token Token :: commentBegin_ (COMMENT_BEGIN, "/*");
	const Token Token :: commentEnd_ (COMMENT_END, "*/");
	const Token Token :: lineComment_ (LINE_COMMENT, "//");

	const Token Token :: toTheEndOfLine_ (TO_THE_END_OF_LINE,"to the end of line");
	const Token Token :: toTheEmptyLine_ (TO_THE_EMPTY_LINE,"to the empty line");
	const Token Token :: disjointWith_ (DISJOINT_WITH,"DisjointWith:");

	const Token Token :: eof_ (EOF_, "eof");

	const Token Token :: tokens_[NUMBER_OF_TOKENS] =
	{
		unknown_,         namespace_,       ontology_,
		annotations_,     object_property_, label_,
		characteristics_, class_,           subclass_of_,
		some_,            and_,             thing_,
		colon_,           comma_,           quotation_,
		leftAngle_,       rightAngle_,      equivalent_to_,
		closeBracket_,    openBracket_,     owl_,
		name_,            string_,          line_,
		commentBegin_,    commentEnd_,      lineComment_,
		toTheEndOfLine_,  toTheEmptyLine_,  disjointWith_,
		eof_
	};

	/****************************
	 *		Public members
	 ****************************/

	const char*
	Token :: getString (const Type type)
	{
		for (int i = 0 ; i < NUMBER_OF_TOKENS; i ++) {
			if (tokens_[i].getType() == type) {
				return tokens_[i].getString();
			}
		}
		return unknown_.getString();
	}

	// nstd :: Object implementation
	void
	Token :: commitSuicide() {
		delete this;
	}
	nstd :: Size_t
	Token :: getSizeOf() const {
		return sizeof (Token);
	}
	nstd :: Size_t
	Token :: getVolume() const {
		return 0;
	}
	void
	Token :: show (nstd :: String<>& string) const {
		string << getString();
	}
}
}
}
}



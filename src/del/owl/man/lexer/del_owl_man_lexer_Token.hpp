/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_lexer_Token.hpp                              */
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

class Token : public nstd :: Object {
public :
	// owl lexer token types.
	enum Type
	{
		UNKNOWN            = 0,  ///<  unknown token
		NAMESPACE          = 1,  ///< "Namespace"       *
		ONTOLOGY           = 2,  ///< "Ontology"        *
		ANNOTATIONS        = 3,  ///< "Annotations"     *
		OBJECT_PROPERTY    = 4,  ///< "ObjectProperty"  *
		LABEL              = 5,  ///< "label"           *
		CHARACTERISTICS    = 6,  ///< "Characteristics" *

		CLASS              = 7,  ///< "Class"           *
		SUBCLASS_OF        = 8,  ///< "SubClassOf"      *
		EQUIVALENT_TO      = 9,  ///< "EquivalentTo"    *
		SOME               = 10, ///< "some"            *
		AND                = 11, ///< "and"             *
		OWL                = 12, ///< "owl"             *
		THING              = 13, ///< "owl:Thing"       *

		COLON              = 14, ///< ":"               *
		COMMA              = 15, ///< ","               *
		QUOTATION          = 16, ///< "\""              *

		LEFT_ANGLE         = 17, ///< "<"               *
		RIGHT_ANGLE        = 18, ///< ">"               *
		OPEN_BRACKET       = 19, ///< "("               *
		CLOSE_BRACKET      = 20, ///< ")"               *

		NAME               = 21, ///<
		STRING             = 22, ///<
		LINE               = 23, ///<

		COMMENT_BEGIN      = 24, ///< "/*"              *
		COMMENT_END        = 25, ///< "*/"              *
		LINE_COMMENT       = 26, ///< "//"              *

		TO_THE_END_OF_LINE = 27,
		TO_THE_EMPTY_LINE  = 28,

		DISJOINT_WITH      = 29, ///< "DisjointWith:"

		EOF_               = 30  ///< end of file
	};

	enum {
		NUMBER_OF_TOKENS = EOF_ + 1
	};

	static const Token unknown_;
	static const Token namespace_;
	static const Token ontology_;
	static const Token annotations_;
	static const Token object_property_;
	static const Token label_;
	static const Token characteristics_;

	static const Token class_;
	static const Token subclass_of_;
	static const Token equivalent_to_;
	static const Token some_;
	static const Token and_;
	static const Token owl_;
	static const Token thing_;

	static const Token colon_;
	static const Token comma_;
	static const Token quotation_;

	static const Token leftAngle_;
	static const Token rightAngle_;
	static const Token openBracket_;
	static const Token closeBracket_;

	static const Token name_;
	static const Token string_;
	static const Token line_;

	static const Token commentBegin_;
	static const Token commentEnd_;
	static const Token lineComment_;

	static const Token toTheEndOfLine_;
	static const Token toTheEmptyLine_;
	static const Token disjointWith_;

	static const Token eof_;

	Token ();
	Token (const Type, const char* const);
	Token (const Token&);
	virtual ~ Token();

	static const char* getString (const Type);
	const char* getString() const;
	Type getType() const;
	nstd :: Size_t getLength() const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual nstd :: Size_t getSizeOf() const;
	virtual nstd :: Size_t getVolume() const;
	virtual void show (nstd :: String<>&) const;

private :
	static const Token tokens_[NUMBER_OF_TOKENS];

	const Type type__;
	const char* const token_;
};

	template<class A>
	nstd :: String<A>&
	operator << (nstd :: String<A>&, const Token&);
}
	using lexer :: Token;
}
}
}

#include "del/owl/man/lexer/del_owl_man_lexer_Token.ipp"
#include "del/owl/man/lexer/del_owl_man_lexer_Token.cpp"



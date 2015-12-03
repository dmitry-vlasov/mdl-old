/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_lexer_Scaner.ipp                             */
/* Description:     manchester OWL scaner                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_LEXER_SCANER_IPP_
#define DEL_OWL_MAN_LEXER_SCANER_IPP_

namespace del {
namespace owl {
namespace man {
namespace lexer {

	/****************************
	 *		Public members
	 ****************************/

	Token :: Type
	Scaner :: scan()
	{
		if (eofAtStart()) {
			return finalize (Token :: EOF_);
		}
		switch (source_.getChar().getValue()) {
		case ',' :
			++ source_;
			return finalize (Token :: COMMA);
		case '\"' :
			++ source_;
			return finalize (Token :: QUOTATION);
		case '<' :
			++ source_;
			return finalize (Token :: LEFT_ANGLE);
		case '>' :
			++ source_;
			return finalize (Token :: RIGHT_ANGLE);
		case '(' :
			++ source_;
			return finalize (Token :: OPEN_BRACKET);
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		case '/' :
			++ source_;
			if (source_.getChar().getValue() == '*' ||
				source_.getChar().getValue() == '/') {
				return finalize (Token :: COMMENT_BEGIN);
			} else {
				return finalize (nameScaner_.scan());
			}
		case '*' :
			++ source_;
			if (source_.getChar().getValue() == '/') {
				return finalize (Token :: COMMENT_END);
			} else {
				return finalize (nameScaner_.scan());
			}
		case 'N' :
			++ source_;
			return finalize (consume (Token :: namespace_, 1));
		case 'O' :
			++ source_;
			if (source_.getChar().getValue() == 'n') {
				return finalize (consume (Token :: ontology_, 1));
			} else if (source_.getChar().getValue() == 'b') {
				return finalize (consume (Token :: object_property_, 1));
			} else {
				return finalize (nameScaner_.scan());
			}
		case 'A' :
			++ source_;
			return finalize (consume (Token :: annotations_, 1));
		case 'C' :
			++ source_;
			if (source_.getChar().getValue() == 'h') {
				return finalize (consume (Token :: characteristics_, 1));
			} else if (source_.getChar().getValue() == 'l') {
				return finalize (consume (Token :: class_, 1));
			} else {
				return finalize (nameScaner_.scan());
			}
		case 'D' :
			++ source_;
			return finalize (consume (Token :: disjointWith_, 1));
		case 'S' :
			++ source_;
			return finalize (consume (Token :: subclass_of_, 1));
		case 'E' :
			++ source_;
			return finalize (consume (Token :: equivalent_to_, 1));
		case 's' :
			++ source_;
			return finalize (consume (Token :: some_, 1));
		case 'a' :
			++ source_;
			return finalize (consume (Token :: and_, 1));
		case 'o' :
			++ source_;
			return finalize (consume (Token :: thing_, 1));
		default :
			return finalize (nameScaner_.scan());
		}
	}
}
}
}
}

#endif /*DEL_OWL_MAN_LEXER_SCANER_IPP_*/

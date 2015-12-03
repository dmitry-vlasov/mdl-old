/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_lexer_Scaner.ipp                            */
/* Description:     functional OWL2 scaner                                   */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_LEXER_SCANER_IPP_
#define DEL_OWL_FUNC_LEXER_SCANER_IPP_

namespace del {
namespace owl {
namespace func {
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
		case '(' :
			++ source_;
			return finalize (Token :: OPEN_BRACKET);
		case ')' :
			++ source_;
			return finalize (Token :: CLOSE_BRACKET);
		case 'A' :
			++ source_;
			if (lookahead (Token :: annotationAssertion_, 1)) {
				return finalize (consume (Token :: annotationAssertion_, 1));
			} else if (lookahead (Token :: annotationProperty_, 1)) {
				return finalize (consume (Token :: annotationProperty_, 1));
			} else if (lookahead (Token :: annotation_, 1)) {
				return finalize (consume (Token :: annotation_, 1));
			} else {
				return finalize (stringScaner_.scan());
			}
		case 'C' :
			++ source_;
			return finalize (consume (Token :: class_, 1));
		case 'D' :
			++ source_;
			return finalize (consume (Token :: declaration_, 1));
		case 'E' :
			++ source_;
			if (source_.getChar().getValue() == 'q') {
				return finalize (consume (Token :: equivalentClasses_, 1));
			} else if (source_.getChar().getValue() == 'n') {
				return finalize (consume (Token :: entityAnnotation_, 1));
			} else {
				return finalize (stringScaner_.scan());
			}
		case 'L' :
			++ source_;
			return finalize (consume (Token :: label_, 1));
		case 'N' :
			++ source_;
			return finalize (consume (Token :: namespace_, 1));
		case 'O' :
			++ source_;
			if (source_.getChar().getValue() == 'n') {
				return finalize (consume (Token :: ontology_, 1));
			} else if (source_.getChar().getValue() == 'b') {
				++ source_;
				if (lookahead (Token :: objectSomeValuesFrom_, 2)) {
					return finalize (consume (Token :: objectSomeValuesFrom_, 2));
				} else if (lookahead (Token :: objectIntersectionOf_, 2)) {
					return finalize (consume (Token :: objectIntersectionOf_, 2));
				}
				return finalize (consume (Token :: objectProperty_, 2));
			} else {
				return finalize (stringScaner_.scan());
			}
		case 'o' :
			++ source_;
			return finalize (consume (Token :: owlThing_, 1));
		case 'P' :
			++ source_;
			return finalize (consume (Token :: prefix_, 1));
		case 'S' :
			++ source_;
			return finalize (consume (Token :: subclassOf_, 1));
		case 'T' :
			++ source_;
			return finalize (consume (Token :: transitiveObjectProperty_, 1));
		default :
			return finalize (stringScaner_.scan());
		}
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_LEXER_SCANER_IPP_*/

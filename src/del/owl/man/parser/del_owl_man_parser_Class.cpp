/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_man_parser_Class.cpp                             */
/* Description:     manchester OWL class parser                              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_MAN_PARSER_CLASS_CPP_
#define DEL_OWL_MAN_PARSER_CLASS_CPP_

#include "del/owl/man/lexer/del_owl_man_lexer.hpp"
#include "del/owl/man/source/del_owl_man_source.hpp"
#include "del/owl/man/parser/del_owl_man_parser.hpp"

namespace del {
namespace owl {
namespace man {
namespace parser {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Class :: Class() :
	location_ (),
	annotationsParser_ (new parser :: Annotations()),
	subclassParser_ (new parser :: Subclass()),
	equivalenceParser_ (new parser :: Equivalence()),
	disjointWithParser_ (new parser :: DisjointWith()) {
	}
	Class :: ~ Class()
	{
		deleteAggregateObject (annotationsParser_);
		deleteAggregateObject (subclassParser_);
		deleteAggregateObject (equivalenceParser_);
		deleteAggregateObject (disjointWithParser_);
	}

	const source :: Class*
	Class :: parse (Lexer* lexer)
	{
		location_ = lexer->getLocation();
		lexer->scan<Token :: NAME>();
		name_.copy (lexer->getToken());

		source :: Class*
			clas = new source :: Class (location_, name_);

		bool insideClass = true;
		while (insideClass) {
			switch (lexer->scan()) {
			case Token :: ANNOTATIONS : {
				const source :: Annotations*
					annotations = annotationsParser_->parse (lexer);
				clas->addAnnotations (annotations);
				break;
			}
			case Token :: SUBCLASS_OF : {
				const source :: Subclass*
					subclass = subclassParser_->parse (lexer, clas);
				clas->addSubclass (subclass);
				break;
			}
			case Token :: EQUIVALENT_TO : {
				const source :: Equivalence*
					equivalence =  equivalenceParser_->parse (lexer, clas);
				clas->addEquivalence (equivalence);
				break;
			}
			case Token :: DISJOINT_WITH : {
				disjointWithParser_->parse (lexer, clas);
				break;
			}
			default :
				lexer->setIdleScan();
				insideClass = false;
			}
		}
		return clas;
	}

	// object :: Object implementation
	void
	Class :: commitSuicide() {
		delete this;
	}
	Size_t
	Class :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		volume += getAggregateVolume (annotationsParser_);
		volume += getAggregateVolume (subclassParser_);
		volume += getAggregateVolume (equivalenceParser_);
		volume += getAggregateVolume (disjointWithParser_);
		return volume;
	}
	Size_t
	Class :: getSizeOf() const {
		return sizeof (Class);
	}
	void
	Class :: show (String&) const {
	}
}
}
}
}

#endif /*DEL_OWL_MAN_PARSER_CLASS_CPP_*/

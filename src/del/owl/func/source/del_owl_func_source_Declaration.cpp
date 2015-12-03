/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_owl_func_source_Declaration.cpp                      */
/* Description:     functional OWL2 declaration source                       */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_OWL_FUNC_SOURCE_DECLARATION_CPP_
#define DEL_OWL_FUNC_SOURCE_DECLARATION_CPP_

#include "del/owl/func/lexer/del_owl_func_lexer.hpp"
#include "del/owl/func/source/del_owl_func_source.hpp"

namespace del {
namespace owl {
namespace func {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Declaration :: Declaration
	(
		const Kind kind,
		const String& name
	) :
	location_ (),
	kind_ (kind),
	name_ (name) {
	}
	inline
	Declaration :: Declaration
	(
		const Location& location,
		const Kind kind,
		const String& name
	) :
	location_ (location),
	kind_ (kind),
	name_ (name) {
	}
	Declaration :: ~ Declaration() {
	}

	Declaration :: Kind
	Declaration :: getKind() const {
		return kind_;
	}
	const String&
	Declaration :: getName() const {
		return name_;
	}

using manipulator :: space;
using manipulator :: endLine;
using manipulator :: tab;

	// del :: Writable implementation
	void
	Declaration :: translate (String& string) const
	{
		/*if (!Config :: commentStuff()) {
			return;
		}
		string << location_.getIndent() << Token :: commentBegin_;
		string << name_ << space << contents_ << Token :: commentEnd_;*/
	}
	void
	Declaration :: replicate (String& string) const
	{
		string << location_.getIndent() << Token :: declaration_;
		string << Token :: openBracket_;
		switch (kind_) {
		case CLASS : {
			string << Token :: class_ << Token :: openBracket_;
			const value :: Variable
				concept = Table :: variables()->add (name_);
			const Symbol symbol (concept, false);
			string << symbol;
			break;
		}
		case OBJECT_PROPERTY : {
			string << Token :: objectProperty_<< Token :: openBracket_;
			const value :: Relation
				relation = Table :: relations()->add (name_);
			const Symbol symbol (relation, true);
			string << symbol;
			break;
		}
		case ANNOTATION_PROPERTY :
			string << Token :: annotationProperty_;
			string << Token :: openBracket_ << name_; break;
		default :
			string << "<...>"; break;
		}
		string << Token :: closeBracket_ << Token :: closeBracket_;
	}

	// object :: Object implementation
	void
	Declaration :: commitSuicide() {
		delete this;
	}
	Size_t
	Declaration :: getVolume() const
	{
		Size_t volume = 0;
		volume += name_.getVolume();
		return volume;
	}
	Size_t
	Declaration :: getSizeOf() const {
		return sizeof (Declaration);
	}
}
}
}
}

#endif /*DEL_OWL_FUNC_SOURCE_DECLARATION_CPP_*/

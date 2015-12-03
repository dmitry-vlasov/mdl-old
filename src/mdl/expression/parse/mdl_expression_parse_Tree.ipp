/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Tree.ipp                            */
/* Description:     tree of expression terms for parser (subexpression)      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_PARSE_TREE_IPP_
#define MDL_EXPRESSION_PARSE_TREE_IPP_

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace expression {
namespace parse {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Tree :: Tree
	(
		const Term_* term,
		const bool initial,
		const bool final,
		const Tree* next
	) :
	term_ (term),
	initial_ (initial),
	final_ (final),
	next_ (next) {
	}

	void
	Tree :: confirm() const
	{
		term_->addSelf (true);
		if (next_ != NULL) {
			next_->confirm();
		}
	}

	inline bool
	Tree :: isInitial() const {
		return initial_;
	}
	inline bool
	Tree :: isFinal() const {
		return final_;
	}
	inline bool
	Tree :: isTop() const {
		return (initial_ && final_);
	}

	inline const Term_*
	Tree :: getTerm() const {
		return term_;
	}

	void
	Tree :: show (String& string) const
	{
		string << tab << *term_;
		if (initial_ ) {
			string << "  <--- initial";
		}
		if (final_ ) {
			string << "  <--- final";
		}
		string << endLine;
		if (next_ != NULL) {
			next_->show (string);
		}
	}
}
}
}

#endif /*MDL_EXPRESSION_PARSE_TREE_IPP_*/

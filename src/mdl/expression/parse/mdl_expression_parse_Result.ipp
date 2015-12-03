/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Result.ipp                          */
/* Description:     parsing result class                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_PARSE_RESULT_IPP_
#define MDL_EXPRESSION_PARSE_RESULT_IPP_

namespace mdl {
namespace expression {
namespace parse {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Result :: Result () :
	list_(),
	final_ (false) {
	}
	inline
	Result :: Result (const Result& result) :
	list_ (result.list_),
	final_ (result.final_) {
	}
	inline
	Result :: Result (const Tree* tree, const bool final) :
	list_(),
	final_ (final) {
		list_.addLast (tree);
	}

	inline void
	Result :: operator = (const Result& result) {
		list_ = result.list_;
		final_ = result.final_;
	}
	inline bool
	Result :: isObtained() const {
		return !list_.isEmpty();
	}
	inline void
	Result :: join (const Result& result) {
		list_.join (result.list_);
	}

using manipulator :: endLine;
using manipulator :: tab;

	bool
	Result :: confirm() const
	{
		if (list_.isEmpty()) {
			return confirmEmpty();
		}
		if (list_.isSingleton()) {
			return confirmSingleton();
		} else {
			return confirmList();
		}
	}
	inline const typename Result :: List_&
	Result :: getList() const {
		return list_;
	}

	/****************************
	 *		Private members
	 ****************************/

	bool
	Result :: confirmEmpty() const
	{
		if (final_) {
			Error* error = new Error (Error :: SEMANTIC);
			error->message() << "expression fails parsing:" << endLine;
			error->message() << tab << "does not match grammar." << endLine;
			throw error;
		} else {
			return false;
		}
	}
	bool
	Result :: confirmSingleton() const
	{
		const Node_* node = list_.getFirst();
		const Tree* tree = node->getValue();
		if (!tree->isTop()) {
			if (final_) {
				Error* error = new Error (Error :: SEMANTIC);
				error->message() << "expression fails parsing:" << endLine;
				error->message() << tab << "does not match grammar." << endLine;
				throw error;
			} else {
				return false;
			}
		} else {
			tree->confirm();
			return true;
		}
	}
	bool
	Result :: confirmList() const
	{
		const Node_* node = list_.getFirst();
		const Tree* tree = NULL;
		while (node != NULL) {
			const Tree* otherTree = node->getValue();
			if (otherTree->isTop()) {
				if (tree == NULL) {
					tree = otherTree;
				} else {
					if (final_) {
						Error* error = new Error (Error :: SEMANTIC);
						error->message() << "expression fails parsing:" << endLine;
						error->message() << tab << "is ambiguous in grammar." << endLine;
						error->message() << tab << "obtained variants:" << endLine;
						tree->show (error->message());
						error->message() << endLine;
						otherTree->show (error->message());
						error->message() << endLine;
						throw error;
					} else {
						return false;
					}
				}
			}
			node = node->getNext();
		}
		tree->confirm();
		return true;
	}
}
}
}

#endif /*MDL_EXPRESSION_PARSE_RESULT_IPP_*/

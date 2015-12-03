/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_model_Predicate.cpp                        */
/* Description:     abstract interface for predicates in model trees         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_MODEL_PREDICATE_CPP_
#define DEL_INTERFACE_MODEL_PREDICATE_CPP_

namespace del {
namespace interface {
namespace model {

	/****************************
	 *		Public members
	 ****************************/

	inline bool
	Predicate :: isTrue (const Symbol symbol) const {
		return isTrue (symbol.getVariable());
	}
	bool
	Predicate :: isTrue (const value :: Variable concept) const
	{
		for (value :: Integer i = 0; i < getSize(); ++ i) {
			const Positive*
				node = getNode (i);
			if (node->getVariable().getVariable() == concept) {
				return true;
			}
		}
		return false;
	}
}
}
}

#endif /*DEL_INTERFACE_MODEL_PREDICATE_CPP_*/

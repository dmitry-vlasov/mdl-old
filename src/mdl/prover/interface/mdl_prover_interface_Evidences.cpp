/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Evidences.cpp                       */
/* Description:     interface for a collection of evidences                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_INTERFACE_EVIDENCES_CPP_
#define MDL_PROVER_INTERFACE_EVIDENCES_CPP_

namespace mdl {
namespace prover {
namespace interface {

	/****************************
	 *		Public members
	 ****************************/

using manipulator :: mode;
using manipulator :: endLine;
using manipulator :: tab;
using manipulator :: iterate;

	template<class A>
	void
	Evidences<A> :: showInfo (String& string, const int indent) const
	{
		for (value :: Integer i = 0; i < getSize(); ++ i) {
			const Evidence_* evidence = getValue (i);
			evidence->showInfo (string, indent);
		}
	}
}
}
}

#endif /*MDL_PROVER_INTERFACE_EVIDENCES_CPP_*/

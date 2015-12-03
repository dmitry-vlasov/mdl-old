/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_interface_object_Identifiable.cpp                    */
/* Description:     abstract interface for identifiable objects              */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_INTERFACE_OBJECT_IDENTIFIABLE_CPP_
#define MDL_INTERFACE_OBJECT_IDENTIFIABLE_CPP_

namespace mdl {
namespace interface {
namespace object {

	/****************************
	 *		Public members
	 ****************************/

	void
	Identifiable :: replicateReversedName (String& string) const
	{
		String name (64);
		replicateName (name);
		name.reverse();
		string << name;
	}
}
}
}

#endif /*MDL_INTERFACE_OBJECT_IDENTIFIABLE_CPP_*/

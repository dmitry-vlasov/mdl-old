/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_prover_Mode.cpp                                      */
/* Description:     class for the prover show mode                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mdl {
namespace prover {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Mode :: Mode () :
	mdl :: Mode () {
	}
	inline
	Mode :: Mode (const String& string) :
	mdl :: Mode (string) {
	}
	inline
	Mode :: Mode (const Mode& mode) :
	mdl :: Mode (mode) {
	}
}
}



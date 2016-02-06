/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Table.ipp                                   */
/* Description:     static class for metamath tables                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline Table :: Files_*
	Table :: files() {
		return files_;
	}
	inline Table :: Literals_*
	Table :: literals() {
		return literals_;
	}
	inline Table :: Identificators_*
	Table :: identificators() {
		return identificators_;
	}
	inline Table :: AssertionLabels_*
	Table :: assertionLabels() {
		return assertionLabels_;
	}
	inline Table :: HypothesisLabels_*
	Table :: hypothesisLabels() {
		return hypothesisLabels_;
	}
}
}



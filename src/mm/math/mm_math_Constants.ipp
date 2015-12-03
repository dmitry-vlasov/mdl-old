/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_math_Constants.ipp                                    */
/* Description:     global metamath constants container                      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_MATH_CONSTANTS_IPP_
#define MM_MATH_CONSTANTS_IPP_

namespace mm {
namespace math {

	/****************************
	 *		Public members
	 ****************************/

	inline value :: Literal
	Constants :: turnstile() const {
		return turnstile_;
	}
	inline value :: Literal
	Constants :: openBracket() const {
		return openBracket_;
	}
	inline value :: Literal
	Constants :: closeBracket() const {
		return closeBracket_;
	}
	inline value :: Literal
	Constants :: openBrace () const {
		return openBrace_;
	}
	inline value :: Literal
	Constants :: closeBrace() const {
		return closeBrace_;
	}
	inline value :: Literal
	Constants :: equality () const {
		return equality_;
	}
	inline value :: Literal
	Constants :: equivalence() const {
		return equivalence_;
	}

	inline value :: Literal
	Constants :: wff() const {
		return wff_;
	}
	inline value :: Literal
	Constants :: set() const {
		return set_;
	}
	inline value :: Literal
	Constants :: _class() const {
		return class_;
	}
}
}

#endif /*MM_MATH_CONSTANTS_IPP_*/

/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_math_Math.hpp                                        */
/* Description:     static container for global del structures               */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MATH_MATH_HPP_
#define DEL_MATH_MATH_HPP_

#include "del/math/del_math_Signatures.hpp"
#include "del/math/del_math_Theories.hpp"

namespace del {
namespace math {

class Math : public nstd :: Static<Math> {
public :
	static Theories* theories();
	static Signatures* signatures();
	static Source* source();
	static void release();

	// nstd :: Static interface
	static void initRaw();
	static void showRaw (String&);
	static Size_t getRawVolume();

private :
	static Theories* theories_;
	static Signatures* signatures_;
	static Source* source_;
};

}
}

#include "del/math/del_math_Math.ipp"

#endif /*DEL_MATH_MATH_HPP_*/

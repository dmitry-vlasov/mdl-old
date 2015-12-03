/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_math_Math.hpp                                         */
/* Description:     static container for global metamath structures          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_MATH_MATH_HPP_
#define MM_MATH_MATH_HPP_

#include "math/mm_math_Constants.hpp"
#include "math/mm_math_Assertions.hpp"

namespace mm {
namespace math {

class Math : public nstd :: Static<Math> {
public :
	static Assertions* assertions();
	static Constants* constants();
	static void release();

	static void show (std :: ostream&);

	// nstd :: Static interface
	static void initRaw();
	static void showRaw (String&);
	static Size_t getRawVolume();

private :
	static Assertions* assertions_;
	static Constants* constants_;
};

}
}

#include "math/mm_math_Math.ipp"

#endif /*MM_MATH_MATH_HPP_*/

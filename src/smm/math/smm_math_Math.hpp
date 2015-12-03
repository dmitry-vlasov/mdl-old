/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_math_Math.hpp                                        */
/* Description:     static container for global smm structures               */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_MATH_MATH_HPP_
#define SMM_MATH_MATH_HPP_

#include "smm/math/smm_math_Constants.hpp"
#include "smm/math/smm_math_Assertions.hpp"

namespace smm {
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

#include "smm/math/smm_math_Math.ipp"

#endif /*SMM_MATH_MATH_HPP_*/

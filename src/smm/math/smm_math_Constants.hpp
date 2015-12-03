/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_math_Constants.hpp                                   */
/* Description:     global smm constants container                           */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_MATH_CONSTANTS_HPP_
#define SMM_MATH_CONSTANTS_HPP_

#include "smm/interface/smm_interface.hpp"
#include "smm/math/smm_math.dpp"

namespace smm {
namespace math {

class Constants : public object :: Object, public Scalar<Constants> {
public :
	Constants();
	virtual ~ Constants();

	void add (const smm :: Constants* const);
	bool contain (const value :: Literal);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	vector :: Literal constantSet_;
	index :: Literal constantCount_;

	enum {
		INITIAL_CONSTANTS_CAPACITY = 4096
	};
};

}
}

#include "smm/math/smm_math_Constants.ipp"

#endif /*SMM_MATH_CONSTANTS_HPP_*/
